#ifndef FILETOOL_H
#define FILETOOL_H
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "resource/HttpResource.h"

#define MAX_PATH_LENGTH 256
#define MAXLINE 1024

using namespace std;

class FileTool
{
    public:
        FileTool();
        virtual ~FileTool();
        static bool isFileExist(string fileName);
        static void getWholeFile(string fileName, char* resourceContent);
        static string getCwd();
        static unsigned long getFileSize(string fileName);
        static void sendFile(int socketFd, string fileName);

    protected:
    private:

};

#endif // FILETOOL_H
