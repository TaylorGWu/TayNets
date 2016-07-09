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
#include "regex/URLRegexParser.h"

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


class Handler1: public RequestHandler
{
    public:
        Handler1()
        {
            cout<<"construct Handler1"<<endl;
        }

        void echo()
        {
            cout<<"testing"<<endl;
        }
};

class Handler2: public RequestHandler
{
    public:
        Handler2()
        {
            cout<<"construct Handler2"<<endl;
        }

        void echo()
        {
            cout<<"testing"<<endl;
        }
};

class HandlerConstructor
{
    public:
        static RequestHandler* getHandler1()
        {
            return new Handler1();
        }

        static RequestHandler* getHandler2()
        {
            return new Handler2();
        }
};

int main(int argc,char *argv[])
{
    map<string, RequestHandler* (*)()> myMap;
    myMap.insert(map<string, RequestHandler* (*)()>::value_type("/MainHandler/([a-zA-z0-9]+)/([a-zA-z0-9]+)", &HandlerConstructor::getHandler1));
    myMap.insert(map<string, RequestHandler* (*)()>::value_type("/TopicHandler/(.*)/(.*)/(.*)", &HandlerConstructor::getHandler2));
    URLRegexParser::init(&myMap);
    URLRegexParser regexHandler("/MainHandler/book/today/sss");
    if (regexHandler.isMatch())
    {
        cout<<"match"<<endl;
        vector<string> myVector;
        regexHandler.parseMatchingStr(myVector);
    }
    else
    {
        cout<<"not match"<<endl;
    }

    URLRegexParser regexHandler1("/MainHandler/cd/yesterday");
    if (regexHandler1.isMatch())
    {
        cout<<"match"<<endl;
        vector<string> myVector;
        regexHandler1.parseMatchingStr(myVector);
    }
    else
    {
        cout<<"not match"<<endl;
    }


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
