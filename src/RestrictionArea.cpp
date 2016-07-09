#include "RestrictionArea.h"

int RestrictionArea::restrictionAreaLockInit()
{
    return pthread_mutex_init(&mutex, NULL);
}

int RestrictionArea::restrictionArealockDestroy()
{
    return pthread_mutex_destroy(&mutex);
}

int RestrictionArea::restrictionAreaLock()
{
    return pthread_mutex_lock(&mutex);
}

int RestrictionArea::restrictionAreaUnlock()
{
    return pthread_mutex_unlock(&mutex);
}

void RestrictionArea::addSocketFd(int socketFd)
{
    fds[fdNum].fd = socketFd;
    fds[fdNum].events = POLLIN | POLLRDHUP | POLLERR | POLLRDBAND;
    fds[fdNum].revents = 0;
    this->fdNum++;
    cout<<"this thread has : "<<this->fdNum<<" sockets."<<endl;
}

void RestrictionArea::removeSocket(int socketFdIndex)
{
    fds[socketFdIndex].fd = -1;
    this->fdNum--;
    close(fds[socketFdIndex].fd);
}

int RestrictionArea::getFdNum()
{
    return this->fdNum;
}

struct pollfd* RestrictionArea::getFds()
{
    return fds;
};

RestrictionArea::RestrictionArea()
{
    this->fdNum = 0;
    this->restrictionAreaLockInit();
}

void RestrictionArea::restrictionAreaDestroy()
{
    int i;
    for(i = 0;i < this->fdNum;i++)                  //close the fd by send a fin to peer
    {
        if(this->fds[i].fd != -1)
            close(this->fds[i].fd);
    }
    this->restrictionAreaDestroy();             //destroy the lock
    return;
}

RestrictionArea::~RestrictionArea()
{
    //dtor
}
