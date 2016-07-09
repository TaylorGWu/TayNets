#include "regex/URLRegexParser.h"

URLRegexParser::URLRegexParser(string URL, string pattern):URL(URL), pattern(pattern)
{
    regcomp(&this->reg, this->pattern.c_str(), REG_EXTENDED);
}

URLRegexParser::~URLRegexParser()
{
    regfree(&this->reg);
}

bool URLRegexParser::isMatch()
{
    int result = regexec(&this->reg, URL.c_str(), MATCHLEN, matches, 0);
    if (REG_NOMATCH == result)      //not match
    {
        return false;
    }
    else if (result)
    {
        return false;       //others error occurs
    }
    else
    {
        return true;        //match
    }
}

void URLRegexParser::parseMatchingStr(vector<string> &matchingStr)
{
    for (int i = 1; i <= this->reg.re_nsub; i++)
    {
        int len = this->matches[i].rm_eo - this->matches[i].rm_so;
        char match[BUFLEN];
        bzero(match, BUFLEN);
        memcpy(match, URL.c_str() + matches[i].rm_so, len);
        matchingStr.push_back(string(match));
    }
}
