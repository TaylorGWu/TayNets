#include "MyEventHandler.h"

MyEventHandler::MyEventHandler()
{
    //ctor
}

MyEventHandler::~MyEventHandler()
{
    //dtor
}

void MyEventHandler::onConnectionClose(int socketFd)
{
    cout<<"here is myEventHandler's onConnectionMethod!"<<endl;
}

void MyEventHandler::onMessageRead(int socketFd)
{
    /* HTTP Mode */
    HttpHandler httpHandler(socketFd);
    httpHandler.getRequestMessage();
    httpHandler.parseRequestMessage();

    /* TCP Mode */
    //Handler handler;
    //handler.echo(socketFd);

}


