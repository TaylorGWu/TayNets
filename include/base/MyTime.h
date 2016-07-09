#ifndef MYTIME_H
#define MYTIME_H

#include <time.h>
#include <string.h>
#include <iostream>
#include <sys/time.h>

class MyTime
{
    public:
        MyTime();
        static std::string getCurrentTimeInSecond();
        static unsigned long getCurrentTimeInMillisecond();
        static time_t getUnixTimeInSecond();
        static void accumulateTimeInMs(unsigned long);
        static unsigned long getAccumulateTimeInMs();
        //std::string getCurrentDate();
        virtual ~MyTime();
    protected:
    private:
        static unsigned long interval;
};

#endif // MYTIME_H
