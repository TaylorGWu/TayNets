#ifndef RANDOMDISPATCH_H
#define RANDOMDISPATCH_H
#include <time.h>
#include <stdlib.h>
#include "algorithm/dispatch/base/DispatchAlgorithm.h"
class RandomDispatch : public DispatchAlgorithm
{
public:
    RandomDispatch(int loopThread);
    int dispatch();
    int dispatch(int socketNum);
    virtual ~RandomDispatch();
protected:
private:
};

#endif // RANDOMDISPATCH_H
