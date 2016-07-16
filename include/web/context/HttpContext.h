#ifndef HTTPCONTEXT_H
#define HTTPCONTEXT_H

#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include "web/protocol/HttpProtocol.h"

using namespace std;

class HttpContext
{
    public:
        HttpContext(int, char*, string, string, string, map<string, string>, map<string, string>, map<string, string>);
        virtual ~HttpContext();
        string getRequireMethod();
        string getRequireFile();
        string getRequireHttpVersion();
        string getHeaderFleldArgument(string);          // get the required headerfield
        string getPostArgument(string);       // get post argument
        string getGetArgument(string);        // get get argument

    protected:
    private:
        char requestMessage[MAX_REQUEST_SIZE];
        int socketFd;
        string requireMethod;          //record this request's method
        string requireFile;                 //record this request's requireFile
        string requireHttpVersion;    //record this request's httpVersion
        map<string, string> headerField;     //record this request's http headerFiled
        map<string, string> messageEntity;      //record this request's HttpMessageEntity
        map<string, string> queryParams;        // record this request's query params
        unsigned long contentLength;        //response must contain in http Mode
};

#endif // HTTPCONTEXT_H
