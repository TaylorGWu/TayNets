#include "web/tool/HttpMessageTool.h"

HttpMessageTool::HttpMessageTool()
{

}

HttpMessageTool::HttpMessageTool(const string httpMessage)
{
    this->httpContent = explode(httpMessage, "\r\n");
}

HttpMessageTool::~HttpMessageTool()
{
    //dtor
}

vector<string> HttpMessageTool::explode(const string str, const string delimiter)
{
    vector<string> arr;
    int delimeterLen = delimiter.length();
    int strLen = str.length();

    if (0 == delimeterLen)
    {
        return arr;
    }

    if (-1 == str.find(delimiter))      // not contains delimiter,and return the whole string stored in vector
    {
        arr.push_back(str);
        return arr;
    }

    int i = 0;
    int k = 0;
    while (i < strLen)
    {
        int j = 0;
        while (i + j < strLen && j < delimeterLen && str[i + j] == delimiter[j])
            j++;

        if (j == delimeterLen)
        {
            arr.push_back(str.substr(k, i - k));
            i += delimeterLen;
            k = i;
        }

        else
            i++;
}

    arr.push_back(str.substr(k, i - k));
}

string HttpMessageTool::getMethod()
{
    //httpContent[0] means requireLine
    vector<string> requireLineContent = explode(httpContent[0], " ");
    return requireLineContent[0];
}

string HttpMessageTool::getRequireResource()
{
    //httpContent[0] means requireLine
    vector<string> requireLineContent = explode(httpContent[0], " ");
    return requireLineContent[1];
}

string HttpMessageTool::getRequireFile()
{
    string requireResource = this->getRequireResource();
    vector<string> requireResourceVector = this->explode(requireResource, "?");     // XXX?aaa=bbb&ccc=ddd

    /* judge whether requireResource is XXX?aaa=bbb or XXX*/
    if (0 < requireResourceVector.size())
    {
        return requireResourceVector[0];
    }
    return requireResource;
}

string HttpMessageTool::getRequireHttpVersion()
{
    vector<string> requireLineContent = explode(httpContent[0], " ");
    return requireLineContent[2];
}

map<string, string> HttpMessageTool::getHeaderField()
{
    vector<string> httpContentTemp = httpContent;
    map<string, string> headerFieldMap;

    /* remove message entity and require line */
    httpContentTemp.pop_back();     // pop back message entity
    httpContentTemp.pop_back();     // pop back header field's eof

    vector<string>::iterator it = httpContentTemp.begin();
    httpContentTemp.erase(it);

    for (it = httpContentTemp.begin(); it != httpContentTemp.end(); it++)
    {
        vector<string> headerFieldItem = this->explode(*it, ":");
        headerFieldMap.insert(map<string, string>::value_type(headerFieldItem[0], headerFieldItem[1]));
    }
    return headerFieldMap;
}

/* parse and return entity */
map<string, string> HttpMessageTool::getMessageEntity()
{
    string entityStr = httpContent[httpContent.size() - 1];
    vector<string> entityVector = this->explode(entityStr, "&");
    map<string, string> messageEntity;

    for (vector<string>::iterator it = entityVector.begin(); it != entityVector.end(); it++)
    {
        vector<string> entityItem = this->explode(*it, "=");
        if (2 == entityItem.size())     // "aaa=bbb" or only blank space after "header field"
        {
            messageEntity.insert(map<string, string>::value_type(entityItem[0], entityItem[1]));
        }
    }
    return messageEntity;
}

/* parse and return query params */
map<string, string> HttpMessageTool::getQueryParams()
{
    string requireResource = this->getRequireResource();
    vector<string> requireResourceVector = this->explode(requireResource, "?");     // XXX?aaa=bbb&ccc=ddd

    map<string, string> queryParams;
    if (1 < requireResourceVector.size())
    {
        vector<string> queryParamsVector = this->explode(requireResourceVector[1], "&");

        for (vector<string>::iterator it = queryParamsVector.begin(); it != queryParamsVector.end(); it++)
        {
            vector<string> paramItem = this->explode(*it, "=");     // "aaa=bbb" or only blank space after "?"
            if (2 == paramItem.size())
            {
                queryParams.insert(map<string, string>::value_type(paramItem[0], paramItem[1]));
            }
        }
    }
    return queryParams;
}
