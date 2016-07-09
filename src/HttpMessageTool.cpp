#include "HttpMessageTool.h"

HttpMessageTool::HttpMessageTool()
{

}

HttpMessageTool::HttpMessageTool(const string httpMessage)
{
    httpContent = explode(httpMessage, "\r\n");
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

map<string, string> HttpMessageTool::getMessageEntity()
{
    string entityStr =httpContent[httpContent.size() - 1];
    vector<string> entityVector = this->explode(entityStr, "&");
    map<string, string> messageEntity;

    for (vector<string>::iterator it = entityVector.begin(); it != entityVector.end(); it++)
    {
        vector<string> entityItem = this->explode(*it, "=");
        messageEntity.insert(map<string, string>::value_type(entityItem[0], entityItem[1]));
    }
    return messageEntity;
}
