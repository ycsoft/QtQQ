#ifndef FILE_HISTORYS_H
#define FILE_HISTORYS_H
#include "python.h"
#include <string>
#include <list>
using namespace std;
class File_history
{
public:
    File_history(int argc,char** argv);
    ~File_history();
    list<string> f_history(const char* path);
    static File_history* instance;
    static void initInstance(int argc,char** argv)
    {
        if(NULL == instance)
            instance = new File_history(argc,argv);
    }
    static File_history* GetInstance()
    {
        return instance;
    }
};
#endif // FILE_HISTORYS_H
