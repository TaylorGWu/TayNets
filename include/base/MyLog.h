#ifndef MYLOG_H
#define MYLOG_H
#include <stdio.h>
#include <string.h>
#include <pthread.h>
class MyLog
{
    public:
        void initMyLog();
        void writeConnectLog(const char *logItem);
        void writeErrorLog(const char *logItem);
        void closeMyLog();
        virtual ~MyLog();
        static MyLog* getInstance();
    protected:
    private:
        MyLog();
        FILE *fpErrorLog;
        FILE *fpConnectLog;
        pthread_mutex_t errorLogLock;
        pthread_mutex_t connectLogLock;
        static MyLog *instance;

};

#endif // MYLOG_H
