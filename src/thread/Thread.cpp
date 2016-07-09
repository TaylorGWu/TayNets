#include "Thread.h"

Thread::Thread() : LOOP_INTERVAL_TIME(2)
{
    this->thread = NULL;
    this->restrictionArea = new RestrictionArea();
    this->handler = new Handler();

}

void* Thread::start()
{
    pthread_create(&thread,NULL,startFunction,(void*)this);
}

void* Thread::startFunction(void* parameter)
{

    Thread* ptr = (Thread*)parameter;
    ptr->run();
}

void* Thread::run()
{
    while(true)
    {

        struct pollfd* fds = restrictionArea->getFds();
        //enter the restriction area
        restrictionArea->restrictionAreaLock();

        //to find out which socket has the pollin request
        //cout<<"here has "<<restrictionArea->getFdNum()<<endl;
        if(poll(restrictionArea->getFds(),restrictionArea->getFdNum(),LOOP_INTERVAL_TIME) < 0)
        {
            perror("error poll");
            return NULL;
        }

        else
        {
            int i;
            for(i = 0; i < restrictionArea->getFdNum(); i++)
            {
                if(fds[i].revents & POLLRDBAND)                     //带外数据
                {
                    cout<<"OOB message arrive."<<endl;
                    handler->readOOBData(fds[i].fd);
                }

                else if(fds[i].revents & POLLRDHUP)              //连接挂起
                {
                    //cout<<"tcp connection close!"<<endl;
                    this->eventHandler->onConnectionClose(fds[i].fd);
                    restrictionArea->removeSocket(i);

                }

                 else if(fds[i].revents & POLLERR)          //连接出错
                {
                    cout<<"error occurs"<<endl;
                    this->eventHandler->onExceptionOccurs(fds[i].fd);
                    //fds[i].fd = -1;
                }

                else if(fds[i].revents & POLLIN)            //连接有数据读入
                {
                    cout<<"message arrive!"<<endl;
                    eventHandler->onMessageRead(fds[i].fd);
                    //handler->echo(fds[i].fd);
                    //handler->sendFile(fds[i].fd,"test1");
                }



            }

        }

        restrictionArea->restrictionAreaUnlock();
        //exit the restriction area
    }

}

void Thread::setEventHandler(EventHandler *eventHandler)
{
    this->eventHandler = eventHandler;
}

RestrictionArea* Thread::getRestrictionAreaPointer()
{
    return this->restrictionArea;

}

void Thread::threadDestroy()
{
    int status = 1;             //stands for normal exit
    restrictionArea->restrictionAreaDestroy();
    pthread_exit(&status);
}

Thread::~Thread()
{
    //dtor
}
