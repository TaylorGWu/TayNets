#ifndef NETSENDTOOL_H
#define NETSENDTOOL_H

#include <string.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>

using namespace std;

class NetSendTool
{
    public:
        NetSendTool();
        virtual ~NetSendTool();
        static void sendFile(int socketFd, char* file, unsigned long);
    protected:
    private:
};

#endif // NETSENDTOOL_H
