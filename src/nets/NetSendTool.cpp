#include "nets/NetSendTool.h"

NetSendTool::NetSendTool()
{
    //ctor
}

NetSendTool::~NetSendTool()
{
    //dtor
}

void NetSendTool::sendFile(int socketFd, char* file, unsigned long fileSize)
{
    try
    {
        write(socketFd, file, fileSize);
    }
    catch (exception &e)
    {
        cout<<e.what()<<endl;
    }
}
