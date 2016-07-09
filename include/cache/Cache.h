#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include "CacheRestrictionArea.h"

/*
 * singleton
 * cache using LRU
 */

class Cache
{
    public:
        static Cache* getInstance();
        HttpResource* getCache(string, string);
        int getCacheSize();
    protected:
    private:
        CacheRestrictionArea *cacheRestrictionArea;
        static Cache* instance;
        Cache();
        virtual ~Cache();
};

#endif // CACHE_H
