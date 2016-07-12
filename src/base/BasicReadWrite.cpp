#include "base/BasicReadWrite.h"

int BasicReadWrite::readCount = 0;
char* BasicReadWrite::ptr = NULL;
char BasicReadWrite::readBuffer[1024] = {0};

BasicReadWrite::BasicReadWrite()
{
    bzero(readBuffer,1024);
}

BasicReadWrite::~BasicReadWrite()
{
    //dtor
}

ssize_t BasicReadWrite::readNBytes(int socketFd,char *bufferAddr,size_t length)
{
    size_t readLeft = length;
    char* ptr;
    ptr = bufferAddr;
    while(readLeft > 0)
    {
        size_t readNum = read(socketFd,ptr,readLeft);
        if(readNum < 0)
        {
            if(errno == EINTR)
            {
                continue;
            }
            else
            {
                perror("read error!");
                return -1;                          //add a return value identifies that is a error return
            }
        }

        else if(readNum == 0)
        {
            break;
        }

        else
        {
            readLeft = readLeft - readNum;
            ptr = ptr + readNum;
        }
    }

    return length - readLeft;

}


ssize_t BasicReadWrite::writeNBytes(int socketFd,char *bufferAddr,size_t length)
{
    size_t nleft = length;
    ssize_t nwrite = 0;
    while(nleft > 0)
    {
        if((nwrite = write(socketFd,bufferAddr,nleft)) <= 0)
        {
            if(nwrite < 0)
            {
                if(errno == EINTR)
                {
                    nwrite = 0;
                }
                return -1;
            }
        }
        nleft = nleft - nwrite;
        bufferAddr = bufferAddr + nwrite;

    }
    return length;
}

ssize_t BasicReadWrite::myRead(int socketFd,char *c)
{
    if(readCount <= 0)
    {
        readAgain:
        if((readCount = read(socketFd,readBuffer,1024)) <= 0)
        {
            if(readCount < 0)            //return values less than 0 means occures error or interupted by a signal.
            {
                if(errno == EINTR)      //read interupted by signal should read again
                    goto readAgain;

                else return -1;
            }

            else return 0 ;  //nothing has read because of disconnect
        }
        ptr = readBuffer;

    }


    readCount--;
    *c = *ptr++;
    return 1;

}


ssize_t BasicReadWrite::readLine(int socketFd,char *arrayPtr,size_t maxlen)
{
    int i;
    size_t readOnce;
    char c,*ptr;
    for(i = 1;i < maxlen;i++)
    {
        if((readOnce = myRead(socketFd,&c)) == 1)
        {
            *arrayPtr++ = c;
            if(c == '\n')
                break;
        }

        else if (readOnce == 0)
        {
            *arrayPtr = 0;
            return i - 1;
        }

        else return -1;
    }

    *arrayPtr = 0;
    return  i;
}
