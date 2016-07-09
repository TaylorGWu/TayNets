#include "base/MyLog.h"
#include <iostream>
 MyLog* MyLog::instance = NULL;

MyLog::MyLog()
{
    this->fpConnectLog = NULL;
    this->fpErrorLog = NULL;
    pthread_mutex_init(&connectLogLock,NULL);
    pthread_mutex_init(&errorLogLock,NULL);
    initMyLog();
}

MyLog::~MyLog()
{
    //dtor
}

void MyLog::initMyLog()
{
    if((fpConnectLog = fopen("./ConnectLog","a+")) == NULL)
        perror("open Connect Log fail!");
    if((fpErrorLog = fopen("./ErrorLog","a+")) == NULL)
        perror("open Error Log fail!");
}

MyLog* MyLog::getInstance()
{
    if(instance == NULL)
        instance = new MyLog();
    return instance;
}

void MyLog::closeMyLog()
{
    fclose(this->fpConnectLog);
    fclose(this->fpErrorLog);
}

void MyLog::writeConnectLog(const char *logItem)
{

    pthread_mutex_lock(&connectLogLock);
    fwrite(logItem,1,strlen(logItem),this->fpConnectLog);
    fflush(fpConnectLog);
    pthread_mutex_unlock(&connectLogLock);
}

void MyLog::writeErrorLog(const char *logItem)
{
    pthread_mutex_lock(&errorLogLock);

    fwrite(logItem,1,strlen(logItem),this->fpErrorLog);
    fflush(fpConnectLog);
    pthread_mutex_unlock(&errorLogLock);

}

