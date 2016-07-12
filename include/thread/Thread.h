#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "event/EventHandler.h"
#include "RestrictionArea.h"
#include "protocol/definition.h"
#include "event/Handler.h"

#include <string.h>
#include <errno.h>
#include <error.h>
#include <sys/socket.h>
#include <sys/types.h>
class Thread
{
public:
    Thread();
    static void*startFunction(void* parameter);
    void* start();
    void* run();
    void threadDestroy();
    RestrictionArea* getRestrictionAreaPointer();
    void setEventHandler(EventHandler *eventHandler);
    virtual ~Thread();
protected:
private:

    const int LOOP_INTERVAL_TIME;
    pthread_t thread;
    RestrictionArea *restrictionArea;
    Handler *handler;
    EventHandler *eventHandler;

};

#endif // THREAD_H
