#ifndef MYEVENTHANDLER_H
#define MYEVENTHANDLER_H

#include "event/EventHandler.h"
#include "web/handler/event/HttpHandler.h"

class MyEventHandler : public EventHandler
{
    public:
        MyEventHandler();
        void onMessageRead(int socketFd);
        void onConnectionClose(int socketFd);
        virtual ~MyEventHandler();
    protected:
    private:
};

#endif // MYEVENTHANDLER_H
