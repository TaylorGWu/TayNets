#include "HttpContext.h"

HttpContext::HttpContext(int socketFd, char* requestMessage, string requireMethod, string requireFile, string requireHttpVersion, vector<string> headerFiled, map<string, string> messageEntity, unsigned long contentLength
):socketFd(socketFd),requireFile(requireFile), requireMethod(requireMethod), requireHttpVersion(requireHttpVersion), headerFiled(headerFiled), messageEntity(messageEntity), contentLength(contentLength)
{
    bzero(requestMessage, MAX_REQUEST_SIZE);
    memcpy(this->requestMessage, requestMessage, MAX_REQUEST_SIZE);
}



HttpContext::~HttpContext()
{
    //dtor
}
