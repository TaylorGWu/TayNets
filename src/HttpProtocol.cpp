#include "HttpProtocol.h"
string HttpProtocol::METHOD_GET = "GET";
string HttpProtocol::METHOD_HEAD = "HEAD";
string HttpProtocol::METHOD_POST = "POST";
string HttpProtocol::CONTENT_TYPE_HTML = "html";
string HttpProtocol::HEADER_FIELD_CONTENT_TYPE_HTML ="Content-Type: text/html \r\n";
string HttpProtocol::CONTENT_TYPE_JSON = "json";
string HttpProtocol::HEADER_FIELD_CONTENT_JSON_HTML ="Content-Type: application/x-www-form-urlencoded \r\n";


HttpProtocol::HttpProtocol()
{
    //ctor
}

HttpProtocol::~HttpProtocol()
{
    //dtor
}
