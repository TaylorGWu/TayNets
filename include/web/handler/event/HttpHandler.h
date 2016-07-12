#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include <string.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include "resource/HttpResource.h"
#include "base/MyTime.h"
#include "web/tool/HttpMessageTool.h"
#include "web/protocol/HttpProtocol.h"
#include "base/FileTool.h"
#include "nets/NetSendTool.h"
#include "cache/Cache.h"


using namespace std;
class HttpHandler
{
    public:
        HttpHandler(int socketFd);
        void getRequestMessage();
        void parseRequestMessage();
        string parseRequestFile();
        void methodHandler();
        void send200Message(string contentType);
        void send404Message();
        void send501Message();      //method not implemented
        static string  cwd;
        virtual ~HttpHandler();
    protected:
    private:
        const int MAXREQUEST_SIZE;
        char *requestMessage;
        int socketFd;
        string requireMethod;          //record this request's method
        string requireFile;     //record this request's requireFile
        string requireHttpVersion;    //record this request's httpVersion
        vector<string> headerFiled;     //record this request's http headerFiled
        map<string, string> messageEntity;      //record this request's HttpMessageEntity
        unsigned long contentLength;        //response must contain in http Mode

};

#endif // HTTPHANDLER_H
