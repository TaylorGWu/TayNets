#include "CacheRestrictionArea.h"

CacheRestrictionArea::CacheRestrictionArea(int capacity):capacity(capacity)
{
    this->restrictionAreaLockInit();
}

CacheRestrictionArea::~CacheRestrictionArea()
{
    //dtor
}

int CacheRestrictionArea::restrictionAreaLockInit()
{
    return pthread_rwlock_init(&(this->rwLock), NULL);
}

int CacheRestrictionArea::restrictionAreaRdLock()
{
    return pthread_rwlock_rdlock(&this->rwLock);
}

int CacheRestrictionArea::restrictionAreaWrLock()
{
    return pthread_rwlock_wrlock(&this->rwLock);
}

int CacheRestrictionArea::restrictionAreaLockDestroy()
{
    return pthread_rwlock_destroy(&this->rwLock);
}

int CacheRestrictionArea::RestrictionAreaUnlock()
{
    return pthread_rwlock_unlock(&this->rwLock);
}
HttpResource* CacheRestrictionArea::lookupCache(string url)
{
    //enter the restriction area
    this->restrictionAreaRdLock();
    map<string, HttpResource* >::iterator it;
    it = this->cacheMap.find(url);
    this->RestrictionAreaUnlock();
    //exit the restriction area

    if (cacheMap.end() == it)
    {
        cout<<"Cache Not Hit!"<<endl;
        return NULL;
    }
    else
    {
        cout<<"Cache Hit!"<<endl;
        return it->second;
    }
}

HttpResource* CacheRestrictionArea::addCache(string url, string fileName)
{
    // enter the restriction area
    this->restrictionAreaWrLock();

    //not enough capacity
    if ( this->cacheMap.size() >= this->capacity)
    {
        this->removeLRUHttpResourceFromMap();
    }
    HttpResource *httpResource = this->insertHttpResourceIntoMap(url, fileName);

    this->RestrictionAreaUnlock();
    // exit the restriction area

    return httpResource;
}

HttpResource* CacheRestrictionArea::insertHttpResourceIntoMap(string url, string fileName)
{
    unsigned long fileSize = FileTool::getFileSize(fileName);
    HttpResource *httpResource = new HttpResource(fileSize);
    char* content = httpResource->getResourceContent();
    FileTool::getWholeFile(fileName, content);
    this->cacheMap.insert(map<string, HttpResource*>::value_type(url, httpResource));
    return httpResource;
}

/*
    remove the latest recently using cache from cacheMap, as LRU we say
 */
void CacheRestrictionArea::removeLRUHttpResourceFromMap()
{
    map<string, HttpResource*>::iterator p;
    map<string, HttpResource*>::iterator temp = this->cacheMap.begin();

    for (p = this->cacheMap.begin(); p != cacheMap.end(); p++)
    {
        time_t lastModifyTime = p->second->getLastModifyTime();
        if (lastModifyTime < temp->second->getLastModifyTime())
        {
            temp = p;
        }
    }
    delete temp->second;
    this->cacheMap.erase(temp);
}

int CacheRestrictionArea::getMapSize()
{
    this->restrictionAreaRdLock();
    int mapSize = this->cacheMap.size();
    this->RestrictionAreaUnlock();
    return mapSize;
}


