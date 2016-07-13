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
        map<string, string> getMessageEntity();          // get post parameter
        map<string, string> getQueryParams();      //  get get parameter
        string getMethod();
        string getRequireFile();
        string getRequireHttpVersion();
        map<string, string> getHeaderField();       // get header field
    protected:
    private:
        vector<string> httpContent;
};

#endif // HTTPMESSAGETOOL_H
