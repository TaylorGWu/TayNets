#include "RequestHandler.h"

RequestHandler::RequestHandler(HttpContext* httpContext):httpContext(httpContext)
{

}

RequestHandler::~RequestHandler()
{

}

void RequestHandler::response()
{

}

/* get Get Argument. If not exist, return NULL */
string RequestHandler::getGetArgument(string key)
{
    return this->httpContext->getGetArgument(key);
}

/* get Post Argument. If not exist, return NULL */
string RequestHandler::getPostArgument(string key)
{
    return this->httpContext->getPostArgument(key);
}

string RequestHandler::getHeaderFieldArument(string key)
{
    return this->httpContext->getHeaderFleldArgument(key);
}
