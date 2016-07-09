#include "Cache.h"
Cache* Cache::instance = NULL;

Cache::Cache()
{
    this->cacheRestrictionArea = new CacheRestrictionArea(500);
}

Cache::~Cache()
{
    //dtor
}

Cache* Cache::getInstance()
{
    if (NULL == instance)
    {
            instance = new Cache();
    }
    return instance;
}

HttpResource* Cache::getCache(string url, string fileName)
{
    HttpResource *httpResource = NULL;
    httpResource = this->cacheRestrictionArea->lookupCache(url);
    if (NULL == httpResource)
    {
        //Cache Not Hit
        httpResource = this->cacheRestrictionArea->addCache(url, fileName);
    }
    return httpResource;
}

int Cache::getCacheSize()
{
    return this->cacheRestrictionArea->getMapSize();
}
