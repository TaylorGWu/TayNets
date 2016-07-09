#include "Server.h"

Server::Server(int port,int loopThread,DispatchAlgorithm *algorithm):port(port),loopThread(loopThread),listenQueue(1500),algorithm(algorithm)
{

}

int Server::init()
{
    this->setEnvironment("./HttpResource");           //change the new working directory
    this->threadPointer = new Thread[loopThread];
    for (int i = 0; i < loopThread; i++)
    {
        threadPointer[i].setEventHandler(this->eventHandler);
    }
    this->socketNum = 0;
    /*init the server*/
    if((this->socketFd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("socket error!");
        return -1;
    }

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(this->port);
    this->serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /*set AddrReuse which prevents the TIME-OUT Stage*/
    int setAddrReuse = 1;
    if(setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&setAddrReuse,sizeof(int)) < 0)
    {
        perror("setAddrReuse error");
    }


    if(bind(socketFd,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0)
    {
        perror("bind error!");
        return -1;
    }
    cout<<"server inits successfully!"<<endl;
    return 0;
}

int Server::start()
{
    cout<<"server starts!"<<endl;
    getEnvironment();
    int i;
    for(i = 0; i < this->loopThread; i++)
    {
        threadPointer[i].start();
    }

    if(listen(this->socketFd,listenQueue) < 0)
    {
        perror("listen error!");
        return -1;
    }

    struct sockaddr_in clientAddr;                          //record the client information
    char clientIP[16];
    socklen_t len = sizeof(clientAddr);
    while(true)
    {
        bzero(&clientAddr,sizeof(clientAddr));
        bzero(clientIP,sizeof(clientIP));
        int newTcpConn;
        if((newTcpConn = accept(this->socketFd,(struct sockaddr*)&clientAddr,&len)) < 0)
        {
            perror("error accept!");
            return -1;
        }
        this->socketNum++;
        inet_ntop(AF_INET,&(clientAddr.sin_addr),clientIP,sizeof(clientAddr));

        cout<<"new TCP connect!:"<<"file descriptor-"<<newTcpConn<<" from "<<clientIP<<":"<<ntohs(clientAddr.sin_port)<<endl;
        string logItem = myTime.getCurrentTimeInSecond() + "-----new TCP connect!\n";
        MyLog::getInstance()->writeConnectLog(logItem.c_str());
        /*
        char logItem[MAXLINE];
        bzero(logItem,MAXLINE);
        */
        /*轮转算法为每个线程的poll loop添加socket*/
        //enter the restriction area
        int index = this->algorithm->dispatch(socketNum);
        /*随机调度算法为每个线程的poll loop添加socket*/
        //int index = this->algorithm->dispatch();
        threadPointer[index].getRestrictionAreaPointer()->restrictionAreaLock();
        threadPointer[index].getRestrictionAreaPointer()->addSocketFd(newTcpConn);
        threadPointer[index].getRestrictionAreaPointer()->restrictionAreaUnlock();
        //exit the restriction area

    }

}

void Server::setEventHandler(EventHandler *eventHandler)
{
    this->eventHandler = eventHandler;
}



void Server::getEnvironment()
{
    cout<<"--------------------------------------------------"<<endl;
    cout<<"this process:"<<getpid()<<endl;
    cout<<"--------------------------------------------------"<<endl;
    union
    {
        short value;
        char  valueArray[2];
    }byteOrderUnion;

    byteOrderUnion.value = 0x0102;
    if(byteOrderUnion.valueArray[0] == 0x01 && byteOrderUnion.valueArray[1] == 0x02 )
    {
        cout<<"big end byte order"<<endl;
    }

    else
    {
        cout<<"small end byte order"<<endl;
    }


    int sendBufferSize;
    int recvBufferSize;
    int sendBufferLowSize;
    int recvBufferLowSize;
    socklen_t valueResult = sizeof(int);
    getsockopt(this->socketFd,SOL_SOCKET,SO_SNDBUF,(void*)&sendBufferSize,&(valueResult));
    getsockopt(this->socketFd,SOL_SOCKET,SO_RCVBUF,(void*)&recvBufferSize,&(valueResult));
    getsockopt(this->socketFd,SOL_SOCKET,SO_SNDLOWAT,(void*)&sendBufferLowSize,&(valueResult));
    getsockopt(this->socketFd,SOL_SOCKET,SO_RCVLOWAT,(void*)&recvBufferLowSize,&(valueResult));
    cout<<"tcp send buffer:"<<sendBufferSize<<" KB-----"<<"tcp recv buffer:"<<recvBufferSize<<"KB"<<endl;
    cout<<"--------------------------------------------------"<<endl;

}

void Server::setEnvironment(char *path)
{
    if(chdir(path) < 0)                            //change the current working directory
        perror("change working fail");
}

void Server::destroy()                                  //destroy the Server
{
    int i;
    for(i = 0;i < loopThread;i++)
        threadPointer[i].threadDestroy();
    return;
}


Server::~Server()
{
    //dtor
}
