#include "event/Handler.h"



Handler::Handler()
{
    myReadWrite = new BasicReadWrite();
}

Handler::~Handler()
{
    //dtor
}


void Handler::echo(int socketFd)
{
    char bufferAddr[MAXLINE];
    bzero(bufferAddr,MAXLINE);
    ssize_t readNum = myReadWrite->readLine(socketFd,bufferAddr,MAXLINE);
    cout<<"recv "<<readNum<<" Bytes:"<<bufferAddr;
    myReadWrite->writeNBytes(socketFd,bufferAddr,strlen(bufferAddr));
    return ;
}

void Handler::sendFile(int socketFd,char *path)
{
    char buffer[MAXLINE];
    bzero(buffer,MAXLINE);
    myReadWrite->readLine(socketFd,buffer,MAXLINE);
    //char buffer[MAXLINE];
    bzero(buffer,MAXLINE);
    FILE *fp = NULL;
    if((fp = fopen(path,"r")) == NULL)
    {
        perror("open file fail.");
        return;
    }
    size_t readNum;
    while((readNum = fread(buffer,1,MAXLINE,fp)) > 0)
    {
        this->myReadWrite->writeNBytes(socketFd,buffer,readNum);
    }

    /*check wheather occurs an error or just a eof when readNum is 0*/
    if(feof(fp))                                            //eof
        cout<<"read file eof."<<endl;
    else                                                    //error occurs
        perror("read file error.");

    fclose(fp);


}

void Handler::readOOBData(int socketFd)
{
    char buffer[MAXLINE];
    bzero(buffer,MAXLINE);
    recv(socketFd,buffer,MAXLINE,MSG_OOB);
    cout<<"recv OOB data "<<strlen(buffer)<<" bytes:"<<buffer<<endl;
    return;
}



