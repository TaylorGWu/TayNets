#ifndef BASICREADWRITE_H
#define BASICREADWRITE_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "protocol/definition.h"
using namespace std;
class BasicReadWrite
{
    public:
        BasicReadWrite();
        ssize_t readNBytes(int socketFd,char *bufferAddr,size_t length);
        ssize_t writeNBytes(int socketFd,char *bufferAddr,size_t length);
        ssize_t myRead(int socketFd,char* c);                                               //this is a function which used as bridge between readLine and read
        ssize_t readLine(int socketFd,char *arrayPtr,size_t maxlen);

        virtual ~BasicReadWrite();
    protected:
    private:
        static int readCount;
        static char *ptr;
        static char readBuffer[MAXLINE];
};

#endif // BASICREADWRITE_H
