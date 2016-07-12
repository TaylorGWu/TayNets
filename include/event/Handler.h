#ifndef HANDLER_H
#define HANDLER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include "base/BasicReadWrite.h"


class Handler
{
    public:
        Handler();
        void readOOBData(int socketFd);
        void echo(int socketFd);
        void sendFile(int socketFd,char *path);
        virtual ~Handler();
    protected:
    private:
        BasicReadWrite *myReadWrite;

};

#endif // HANDLER_H
