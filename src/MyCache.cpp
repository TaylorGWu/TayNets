#include "MyCache.h"

MyCache* MyCache::instance = NULL;

MyCache* MyCache::getInstance()
{
    if (NULL == instance)
        instance = new MyCache();
    return instance;
}

MyCache::MyCache()
{
    pthread_mutex_init(&(this->mapMutex), NULL);    //init the lock
}

void MyCache::setCache(string resourceName)
{
    unsigned long resourceSize = FileTool::getFileSize(resourceName);
    HttpResource *httpResource = new HttpResource(resourceSize);
    FileTool::getWholeFile(resourceName, httpResource->getResourceContent());
    this->cacheMap.insert(map<string, HttpResource*>::value_type(resourceName, httpResource));
}

MyCache::~MyCache()
{
    map<string, HttpResource*>::iterator it;
    for (it = this->cacheMap.begin(); it != this->cacheMap.end(); it++)
    {
        delete (&it);       //be careful, maybe bug here
    }
}
