#ifndef URLREGEXPARSER_H
#define URLREGEXPARSER_H

#define MATCHLEN 10           /* 匹配子串的数量 */
#define EBUFLEN 128         /* 错误消息buffer长度 */
#define BUFLEN 1024         /* 匹配到的字符串buffer长度 */

#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <regex.h>
#include <sys/types.h>

using namespace std;
class RequestHandler
{
    public:
        virtual void echo()
        {
            cout<<"base"<<endl;
        }
};

class URLRegexParser
{
    public:
        URLRegexParser(string URL);
        static void init(map<string, RequestHandler* (*)()>* );
        bool isMatch();
        void parseMatchingStr(vector<string> &);       //get matching sub string
        virtual ~URLRegexParser();
    protected:
    private:
        static map<string, regex_t> regMap;
        regex_t* reg;
        string URL;
        regmatch_t matches[MATCHLEN];
};

#endif // URLREGEXPARSER_H
