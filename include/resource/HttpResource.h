#ifndef HTTPRESOURCE_H
#define HTTPRESOURCE_H

#include <stdlib.h>
#include "../base/MyTime.h"

using namespace std;

class HttpResource
{
    public:
        HttpResource(size_t resourceSize);
        size_t getResourceSize();
        time_t getLastModifyTime();
        char* getResourceContent();
        virtual ~HttpResource();
    protected:
    private:
        time_t lastModifyTime;
        size_t resourceSize;
        char *content;
};

#endif // HTTPRESOURCE_H
