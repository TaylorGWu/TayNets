#ifndef ROUNDROBINALGORITHM_H
#define ROUNDROBINALGORITHM_H

#include "DispatchAlgorithm.h"

class RoundRobinAlgorithm : public DispatchAlgorithm
{
public:
    RoundRobinAlgorithm(int loopThread);
    int dispatch(int socketNum);
    int dispatch();
    virtual ~RoundRobinAlgorithm();
protected:
private:
};

#endif // ROUNDROBINALGORITHM_H
