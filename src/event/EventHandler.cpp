#include "event/EventHandler.h"

EventHandler::EventHandler()
{
    //ctor
}

void EventHandler::onMessageRead(int socketFd)
{
    Handler handler;
    handler.echo(socketFd);
}

void EventHandler::onMessageWrite(int socketFd)
{
    cout<<"onMessageWrite!"<<endl;
}

void EventHandler::onConnectionClose(int socketFd)
{
    cout<<"socket:"<<socketFd<<" disconnected!"<<endl;
}

void EventHandler::onExceptionOccurs(int socketFd)
{
    cout<<"socket:"<<socketFd<<" occurs error!"<<endl;
}

EventHandler::~EventHandler()
{
    //dtor
}


