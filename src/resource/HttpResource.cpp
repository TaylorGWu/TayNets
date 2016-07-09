#include "resource/HttpResource.h"

HttpResource::HttpResource(size_t resourceSize):resourceSize(resourceSize)
{
    this->content = (char *)malloc(this->resourceSize);
    bzero(this->content, this->resourceSize);
    this->lastModifyTime = MyTime::getUnixTimeInSecond();
}

size_t HttpResource::getResourceSize()
{
        return this->resourceSize;
}

time_t HttpResource::getLastModifyTime()
{
        return this->lastModifyTime;
}

char* HttpResource::getResourceContent()
{
    return this->content;
}

HttpResource::~HttpResource()
{
    //free the memory in ram
    free(this->content);
}


