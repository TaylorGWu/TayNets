#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include "Handler.h"

using namespace std;
class EventHandler
{
    public:
        EventHandler();
        virtual void onMessageRead(int socketFd);
        virtual void onMessageWrite(int socketFd);
        virtual void onConnectionClose(int socketFd);
        virtual void onExceptionOccurs(int socketFd);
        virtual ~EventHandler();
    protected:
    private:
};

#endif // EVENTHANDLER_H
