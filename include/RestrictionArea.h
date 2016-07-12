#ifndef RESTRICTIONAREA_H
#define RESTRICTIONAREA_H

#include "protocol/definition.h"
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <poll.h>
using namespace std;

class RestrictionArea
{
public:
    RestrictionArea();
    void restrictionAreaDestroy();
    int restrictionAreaLockInit();
    int restrictionArealockDestroy();

    int restrictionAreaLock();
    int restrictionAreaUnlock();
    void addSocketFd(int socketFd);
    void removeSocket(int socketFdIndex);


    struct pollfd* getFds();
    int getFdNum();

    virtual ~RestrictionArea();
protected:
private:
    pthread_mutex_t mutex;
    struct pollfd fds[OPENMAX];
    int fdNum;

};

#endif // RESTRICTIONAREA_H
