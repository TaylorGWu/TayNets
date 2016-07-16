#include "HttpContext.h"

HttpContext::HttpContext(int socketFd, char* requestMessage, string requireMethod, string requireFile, string requireHttpVersion, map<string, string> headerField, map<string, string> messageEntity,
                         map<string, string> queryParams):socketFd(socketFd),requireFile(requireFile), requireMethod(requireMethod), requireHttpVersion(requireHttpVersion), headerField(headerField), messageEntity(messageEntity), queryParams(queryParams)
{
    bzero(this->requestMessage, MAX_REQUEST_SIZE);
    memcpy(this->requestMessage, requestMessage, MAX_REQUEST_SIZE);
}

string HttpContext::getRequireMethod()
{
    return this->requireMethod;
}

string HttpContext::getRequireFile()
{
    return this->requireFile;
}

string HttpContext::getRequireHttpVersion()
{
    return this->requireHttpVersion;
}

/* get the required headerfield */
string HttpContext::getHeaderFleldArgument(string key)
{
    map <string, string>::iterator it;
    it = this->headerField.find(key);
    if (it == headerField.end())
    {
        return NULL;
    }
    return it->second;
}

/* get post argument */
string HttpContext::getPostArgument(string key)
{
    map <string, string>::iterator it;
    it = this->messageEntity.find(key);
    if (it == messageEntity.end())
    {
        return NULL;
    }
    return it->second;
}

/* get get argument */
string HttpContext::getGetArgument(string key)
{
    map <string, string>::iterator it;
    it = this->queryParams.find(key);
    if (it == queryParams.end())
    {
        return NULL;
    }
    return it->second;
}

HttpContext::~HttpContext()
{
    //dtor
}
