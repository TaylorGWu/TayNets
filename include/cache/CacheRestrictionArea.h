#ifndef CACHERESTRICTIONAREA_H
#define CACHERESTRICTIONAREA_H

#include <pthread.h>
#include <map>
#include "resource/HttpResource.h"
#include "base/FileTool.h"

using namespace std;

class CacheRestrictionArea
{
    public:
        CacheRestrictionArea(int capacity);
        virtual ~CacheRestrictionArea();
        int restrictionAreaLockInit();
        int restrictionAreaRdLock();
        int restrictionAreaWrLock();
        int RestrictionAreaUnlock();
        int restrictionAreaLockDestroy();
        int getMapSize();
        HttpResource* lookupCache(string);
        HttpResource* addCache(string, string);
        HttpResource* insertHttpResourceIntoMap(string, string);
        void removeLRUHttpResourceFromMap();



    protected:
    private:
        const int capacity;
        map<string, HttpResource* > cacheMap;
        pthread_rwlock_t rwLock;
};

#endif // CACHERESTRICTIONAREA_H
