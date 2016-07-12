#ifndef DISPATCHALGORITHM_H
#define DISPATCHALGORITHM_H


class DispatchAlgorithm
{
public:
    DispatchAlgorithm();
    virtual int dispatch(int socketNum) = 0;
    virtual int dispatch() = 0;
    virtual ~DispatchAlgorithm();
    int loopThread;
protected:
private:
};

#endif // DISPATCHALGORITHM_H
