#ifndef MYCACHE_H
#define MYCACHE_H

/*
 *  simple cache using Map
 *  using singleton mode
 */

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <map>
#include "resource/HttpResource.h"
#include "base/FileTool.h"

class MyCache
{
    public:
        static MyCache* getInstance();
        void setCache(string);
    protected:
    private:
        MyCache();
        virtual ~MyCache();
        static MyCache *instance;
        pthread_mutex_t mapMutex;
        map<string, HttpResource*> cacheMap;
};

#endif // MYCACHE_H
