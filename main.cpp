#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>

#include "RoundRobinAlgorithm.h"
#include "RandomDispatch.h"
#include "Server.h"
#include "Handler.h"
#include "EventHandler.h"
#include "MyEventHandler.h"
using namespace std;


/**
 *@author Taylor
 *@date 2015 summer
 */
void readTest(int socketFd)
{
    Handler *handler = new Handler();
    handler->echo(socketFd);
}

int main(int argc,char *argv[])
{
    if(argc != 3 )
    {
        perror("parameter error!");
        return -1;
    }


    int port = atoi(argv[1]);         //get port
    int threadNum = atoi(argv[2]);
    //int port = 9999;         //get port
    //int threadNum = 5;
    DispatchAlgorithm *algorithm = new RoundRobinAlgorithm(threadNum);   //策略模式-轮转算法
    DispatchAlgorithm *algorithm1 = new RandomDispatch(threadNum);          //策略模式-随机调度算法
    Server server(port,threadNum,algorithm);

    EventHandler *eventHandler = new MyEventHandler();
    server.setEventHandler(eventHandler);

    server.init();
    server.start();


    //cout << "Hello world!" << endl;
    return 0;
}
