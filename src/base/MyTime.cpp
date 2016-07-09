#include "base/MyTime.h"
#include <iostream>

unsigned long MyTime::interval = 0;

MyTime::MyTime()
{
    //ctor
}


MyTime::~MyTime()
{
    //dtor
}


std::string MyTime::getCurrentTimeInSecond()
{
    time_t t = time(0);
    char currentTime[64];
    bzero(currentTime,sizeof(currentTime));
    strftime(currentTime,sizeof(currentTime),"%Y-%m-%d--%X",localtime(&t));
    return std::string(currentTime);
}

//get the interval second from 1970-01-01
time_t MyTime::getUnixTimeInSecond()
{
        time_t currentTime;
        time(&currentTime);
        return currentTime;
}

unsigned long MyTime::getCurrentTimeInMillisecond()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void MyTime::accumulateTimeInMs(unsigned long interval)
{
    MyTime::interval += interval;
}

unsigned long MyTime::getAccumulateTimeInMs()
{
    return MyTime::interval;
}

