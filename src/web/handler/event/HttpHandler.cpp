#include "web/handler/event/HttpHandler.h"

string HttpHandler::cwd = "";

HttpHandler::HttpHandler(int socketFd):MAXREQUEST_SIZE(8192),socketFd(socketFd)
{
    char requestMessageArray[MAXREQUEST_SIZE];
    this->requestMessage = requestMessageArray;
    bzero(this->requestMessage,MAXREQUEST_SIZE);
}

HttpHandler::~HttpHandler()
{
    //delete []requestMessage;
}

void HttpHandler::getRequestMessage()
{
    int nbytes;
    int index = 0;
    nbytes = read(socketFd, (void*)this->requestMessage, MAXREQUEST_SIZE);
}

void HttpHandler::parseRequestMessage()
{
    //cout<<"content:"<<requestMessage;
    //cout<<"after explode:"<<endl;
    HttpMessageTool httpMessageTool(requestMessage);
    this->requireMethod = httpMessageTool.getMethod();
    this->requireFile = httpMessageTool.getRequireFile();
    this->requireHttpVersion = httpMessageTool.getRequireHttpVersion();
    this->headerField = httpMessageTool.getHeaderField();
    this->messageEntity = httpMessageTool.getMessageEntity();
    /*
    cout<<"Method:"<<requireMethod<<"------"<<"requireFile:"<<requireFile<<"-----"<<requireHttpVersion<<endl;
    cout<<"header filed;"<<endl;
    */
    for (map<string, string>::iterator it = headerField.begin(); it != headerField.end(); it++)
        cout<<it->first<<":"<<it->second<<endl;

    this->methodHandler();
}

void HttpHandler::methodHandler()
{
    if (HttpProtocol::METHOD_GET == this->requireMethod || HttpProtocol::METHOD_HEAD == this->requireMethod)
    {
        string fileName = this->parseRequestFile();
        if (FileTool::isFileExist(fileName))
        {
            unsigned long start = MyTime::getCurrentTimeInMillisecond();

            Cache* instance = Cache::getInstance();
            cout<<"cache size:"<<instance->getCacheSize()<<endl;
            HttpResource *httpResource = instance->getCache(this->requireFile, fileName);
            this->contentLength = httpResource->getResourceSize();
            this->send200Message(HttpProtocol::CONTENT_TYPE_HTML);

            if (HttpProtocol::METHOD_GET == this->requireMethod)
            {
                char* content = httpResource->getResourceContent();
                NetSendTool::sendFile(this->socketFd, content, this->contentLength);
            }

            unsigned long finish = MyTime::getCurrentTimeInMillisecond();
            //cout<<"finish:"<<finish<<"ms -- start:"<<start<<"ms -- cost:"<<finish - start<<" Ms!"<<endl;
            MyTime::accumulateTimeInMs(finish-start);
            cout<<"accumulate time:"<<MyTime::getAccumulateTimeInMs()<<" ms."<<endl;
        }
        else
            this->send404Message();


    }
    else if (HttpProtocol::METHOD_POST == this->requireMethod)
    {
        for (map<string, string>::iterator it = messageEntity.begin(); it != messageEntity.end(); it++)
        {
            cout<<it->first<<":"<<it->second<<endl;
        }
        string postResult = "{'result':'success'}";
        this->contentLength  = postResult.length();
        this->send200Message(HttpProtocol::CONTENT_TYPE_JSON);
        const char *result = postResult.data();
        write(socketFd, result, contentLength);
    }
    else
        this->send501Message();
}

//using factory method of factory mode
void HttpHandler::send200Message(string contentType)
{
    cout<<"send 200 message"<<endl;
    string message200String = "";
    message200String  +=   "HTTP/1.1 200 OK \r\n";
    message200String  +=    "Date: Sat, 31 Dec 2005 23:59:59 GMT \r\n" ;
    /*
    if (HttpProtocol::CONTENT_TYPE_HTML == contentType)
        message200String  +=    HttpProtocol::HEADER_FIELD_CONTENT_TYPE_HTML ;
    else if (HttpProtocol::CONTENT_TYPE_JSON == contentType)
        message200String  +=    HttpProtocol::HEADER_FIELD_CONTENT_JSON_HTML ;
    */
    stringstream contentLengthStr;
    contentLengthStr<<contentLength;
    string contentLengthHeaderFiled = "Content-Length:" + contentLengthStr.str() + "\r\n\r\n" ;
    message200String += contentLengthHeaderFiled;

    const char *message = message200String.data();
    write(socketFd, message, strlen(message));
}

void HttpHandler::send404Message()
{
    cout<<"send 404 message"<<endl;
    string message404String = "";
    message404String  +=    "HTTP/1.1 404 Not Found \r\n";
    message404String  +=    "Date: Sat, 31 Dec 2005 23:59:59 GMT \r\n" ;
    message404String  +=    "Content-Length:50\r\n\r\n";
    message404String  +=    "<html>";
    message404String  +=        "<body>";
    message404String  +=            "<h1>File Not Found!</h1>";
    message404String  +=        "</body>";
    message404String  +=    "</html>";
    const char *message = message404String.data();
    write(socketFd, message, strlen(message));
}

void HttpHandler::send501Message()
{
    cout<<"send 501 message"<<endl;
    string message501String = "";
    message501String += "HTTP/1.1 501 Not Implemented \r\n";
    message501String += "Date: Sat, 31 Dec 2005 23:59:59 GMT \r\n";
    message501String  +=    "Content-Length:23\r\n\r\n";
    message501String  +=    "Method Not Implemented!";
    const char *message = message501String.data();
    write(socketFd, message, strlen(message));
}

string HttpHandler::parseRequestFile()
{
    if ("" == cwd)
        cwd = FileTool::getCwd();

    if ("/" == requireFile)
        return cwd + "/welcome.html";
    else
        return cwd + requireFile;


}
