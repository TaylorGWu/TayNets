#ifndef SERVER_H
#define SERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "algorithm/dispatch/base/DispatchAlgorithm.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "thread/Thread.h"
#include "base/MyLog.h"
#include "base/MyTime.h"

class Server
{
public:
    Server(int port,int loopThread,DispatchAlgorithm *algorithm);
    int init();
    int start();
    void  destroy();
    void getEnvironment();
    void setEnvironment(char *path);
    void setEventHandler(EventHandler *eventHandler);
    virtual ~Server();
protected:

private:
    const int port;                                     //server's port
    const int loopThread;                         //thread num
    const int listenQueue;
    int socketNum;                         //all TCP connect socket's number
    int socketFd;                                   //server socket
    struct sockaddr_in serverAddr;
    EventHandler *eventHandler;
    Thread *threadPointer;
    DispatchAlgorithm *algorithm;
    MyTime myTime;





};

#endif // SERVER_H
