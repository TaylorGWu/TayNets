#ifndef URLREGEXPARSER_H
#define URLREGEXPARSER_H

#define MATCHLEN 10           /* 匹配子串的数量 */
#define EBUFLEN 128         /* 错误消息buffer长度 */
#define BUFLEN 1024         /* 匹配到的字符串buffer长度 */

#include <iostream>
#include <string.h>
#include <vector>
#include <regex.h>
#include <sys/types.h>

using namespace std;

class URLRegexParser
{
    public:
        URLRegexParser(string URL, string pattern);
        bool isMatch();
        void parseMatchingStr(vector<string> &);       //get matching sub string
        virtual ~URLRegexParser();
    protected:
    private:
        regex_t reg;
        string URL;
        string pattern;
        regmatch_t matches[MATCHLEN];
};

#endif // URLREGEXPARSER_H
