#ifndef HTTPPROTOCOL_H
#define HTTPPROTOCOL_H
#include <string>
using namespace std;

//-----------------constants------------------------//
#define MAX_REQUEST_SIZE 8192
//---------------------end---------------------------//
class HttpProtocol
{
    public:
        HttpProtocol();
        virtual ~HttpProtocol();
        static string METHOD_GET;
        static string METHOD_HEAD;
        static string METHOD_POST;
        static string CONTENT_TYPE_HTML;
        static string HEADER_FIELD_CONTENT_TYPE_HTML;
        static string CONTENT_TYPE_JSON;
        static string HEADER_FIELD_CONTENT_JSON_HTML;

    protected:
    private:
};

#endif // HTTPPROTOCOL_H
