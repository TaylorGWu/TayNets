#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

/*
    this is the base class which handler the request
    application handler can extends with it and over writted with abstract methods
*/

class RequestHandler
{
    public:
        RequestHandler();
        virtual ~RequestHandler();
    protected:
    private:
};

#endif // REQUESTHANDLER_H
