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
        return arr;

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

string HttpMessageTool::getRequireFile()
{
    //httpContent[0] means requireLine
    vector<string> requireLineContent = explode(httpContent[0], " ");
    return requireLineContent[1];
}

string HttpMessageTool::getRequireHttpVersion()
{
    vector<string> requireLineContent = explode(httpContent[0], " ");
    return requireLineContent[2];
}

vector<string> HttpMessageTool::getHeaderField()
{
    vector<string> httpContentTemp = httpContent;
    vector<string>::iterator it = httpContentTemp.begin();
    httpContentTemp.erase(it);
    return httpContentTemp;
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
        messageEntity.insert(map<string, string>::value_type(entityItem[0], entityItem[1]));
    }
    return messageEntity;
}

/* parse and return query params */
map<string, string> HttpMessageTool::getQueryParams()
{
    string requireFile = this->getRequireFile();
    vector<string> requireFileVector = this->explode(requireFile, "?");     // XXX?aaa=bbb&ccc=ddd
    vector<string> queryParamsVector = this->explode(requireFileVector[1], "&");
    map<string, string> queryParams;

    for (vector<string>::iterator it = queryParamsVector.begin(); it != queryParamsVector.end(); it++)
    {
        vector<string> paramItem = this->explode(*it, "=");     // aaa=bbb
        queryParams.insert(map<string, string>::value_type(paramItem[0], paramItem[1]));
    }
    return queryParams;
}
