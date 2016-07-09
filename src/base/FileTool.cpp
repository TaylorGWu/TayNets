#include "base/FileTool.h"

FileTool::FileTool()
{
    //ctor
}

FileTool::~FileTool()
{
    //dtor
}

string FileTool::getCwd()
{
    char cwd[MAX_PATH_LENGTH];
    bzero(cwd, MAX_PATH_LENGTH);
    getcwd(cwd, MAX_PATH_LENGTH);
    return string(cwd);
}

bool FileTool::isFileExist(string fileName)
{
    if (-1 == access(fileName.c_str(), 0))
    {
        if (ENOENT == errno)
            return false;
        return true;
    }

    return true;
}

unsigned long FileTool::getFileSize(string fileName)
{
    struct stat fileStat;
    if (0 > stat(fileName.c_str(), &fileStat))
        return -1;
    else
        return fileStat.st_size;
}

void FileTool::getWholeFile(string fileName, char* resourceContent)
{
        FILE *fp = NULL;
        if((fp = fopen(fileName.c_str(), "r")) == NULL)
        {
            perror("open file fail.");
            return;
        }

        size_t resourceSize = getFileSize(fileName);

        size_t readNum;
        readNum = fread(resourceContent, 1, resourceSize, fp);

        fclose(fp);

}

void FileTool::sendFile(int socketFd,string fileName)
{
    char buffer[MAXLINE];
    bzero(buffer,MAXLINE);

    size_t resourceSize = getFileSize(fileName);
    HttpResource *httpResource = new HttpResource(resourceSize);
    char* resourceContent = httpResource->getResourceContent();

    FILE *fp = NULL;
    if((fp = fopen(fileName.c_str(), "r")) == NULL)
    {
        perror("open file fail.");
        return;
    }

    size_t readNum;
    readNum = fread(resourceContent, 1, resourceSize, fp);
    write(socketFd, resourceContent, readNum);

    /*
    while((readNum = fread(buffer,1,MAXLINE,fp)) > 0)
    {
        write(socketFd, buffer, readNum);
    }

    /*check wheather occurs an error or just a eof when readNum is 0*/
    /*
    if(feof(fp))                                            //eof
        cout<<"read file eof."<<endl;
    else                                                    //error occurs
        perror("read file error.");
    */
    delete httpResource;
    fclose(fp);
}




