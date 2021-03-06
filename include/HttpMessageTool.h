#ifndef HTTPMESSAGETOOL_H
#define HTTPMESSAGETOOL_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
class HttpMessageTool
{
    public:
        HttpMessageTool();
        HttpMessageTool(const string httpMessage);
        virtual ~HttpMessageTool();
        vector<string> explode(const string str, const string delimiter);
        map<string, string> getMessageEntity();
        string getMethod();
        string getRequireFile();
        string getRequireHttpVersion();
        vector<string> getHeaderField();
    protected:
    private:
        vector<string> httpContent;
};

#endif // HTTPMESSAGETOOL_H
