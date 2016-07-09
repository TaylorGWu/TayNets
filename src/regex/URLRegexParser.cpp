#include "regex/URLRegexParser.h"

map<string, regex_t> URLRegexParser::regMap;

URLRegexParser::URLRegexParser(string URL):URL(URL)
{

}

URLRegexParser::~URLRegexParser()
{

}

void URLRegexParser::init(map<string, RequestHandler* (*)()>* handlerMap)
{
    map<string, RequestHandler* (*)()>::iterator it;
    for (it = handlerMap->begin(); it != handlerMap->end(); it++)
    {
            regex_t reg;
            string URL = it->first;
            regcomp(&reg, URL.c_str(), REG_EXTENDED);
            regMap.insert(map<string, regex_t>::value_type(URL, reg));
    }
}

bool URLRegexParser::isMatch()
{
    map<string,  regex_t>::iterator it;
    for (it = regMap.begin(); it != regMap.end(); it++)
    {
        int result = regexec(&it->second, this->URL.c_str(), MATCHLEN, matches, 0);
        if (REG_NOMATCH == result)      //not match
        {
            continue;
        }
        else if (result)
        {
            continue;       //others error occurs
        }
        else
        {
            this->reg = &it->second;
            return true;        //match
        }
    }
    return false;
}

void URLRegexParser::parseMatchingStr(vector<string> &matchingStr)
{
    for (int i = 1; i <= this->reg->re_nsub; i++)
    {
        int len = this->matches[i].rm_eo - this->matches[i].rm_so;
        char match[BUFLEN];
        bzero(match, BUFLEN);
        memcpy(match, URL.c_str() + matches[i].rm_so, len);
        cout<<match<<endl;
        matchingStr.push_back(string(match));
    }
}
