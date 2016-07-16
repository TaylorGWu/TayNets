#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

/*
    this is the base class which handler the request
    application handler can extends with it and over writted with abstract methods
*/

#include "web/context/HttpContext.h"

class RequestHandler
{
    public:
        RequestHandler(HttpContext* httpContext);
        void response();
        virtual void get() = 0;
        virtual void post() = 0;
        string getGetArgument(string);    // get Get Argument
        string getPostArgument(string);   // get Post Argument
        string getHeaderFieldArument(string);  // get Header Field Argument
        virtual ~RequestHandler();
    protected:
    private:
        HttpContext* httpContext;

};

#endif // REQUESTHANDLER_H
