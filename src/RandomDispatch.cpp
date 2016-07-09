#include "RandomDispatch.h"

RandomDispatch::RandomDispatch(int loopThread)
{
    this->loopThread = loopThread;
}

RandomDispatch::~RandomDispatch()
{
    //dtor
}

int RandomDispatch::dispatch()
{
    srand((unsigned)time(NULL));
    int lowBound = 0;
    int highBound = this->loopThread;
    int index = lowBound + rand() % (highBound);
    return index;

}

int RandomDispatch::dispatch(int socketNum)
{
    return -1;
}
