#include "RoundRobinAlgorithm.h"

RoundRobinAlgorithm::RoundRobinAlgorithm(int loopThread)
{
    this->loopThread = loopThread;
}

RoundRobinAlgorithm::~RoundRobinAlgorithm()
{
    //dtor
}

int RoundRobinAlgorithm::dispatch(int socketNum)
{
    int index = (socketNum - 1) % loopThread;
    return index;
}

int RoundRobinAlgorithm::dispatch()
{
    return -1;
}
