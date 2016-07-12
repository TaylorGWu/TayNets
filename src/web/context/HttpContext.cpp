#include "HttpContext.h"

HttpContext::HttpContext(int socketFd, char* requestMessage, string requireMethod, string requireFile, string requireHttpVersion, vector<string> headerFiled, map<string, string> messageEntity, unsigned long contentLength
):socketFd(socketFd),requireFile(requireFile), requireMethod(requireMethod), requireHttpVersion(requireHttpVersion), headerField(headerField), messageEntity(messageEntity), contentLength(contentLength)
{
    bzero(requestMessage, MAX_REQUEST_SIZE);
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
    /*
    vector<string>::iterator it;
    it = this->headerField.find(key);
    if (it == headerField.end())
    {
        return NULL;
    }
    return *it;
    */
}

/* get post argument */
string HttpContext::getPostArgument(string)
{

}

/* get get argument */
string HttpContext::getGetArgument(string)
{

}

HttpContext::~HttpContext()
{
    //dtor
}
