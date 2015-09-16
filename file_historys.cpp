#include "file_historys.h"
#include <map>
#include <set>
#include <QMessageBox>
using namespace std;

File_history* File_history::instance = NULL;
File_history::File_history(int argc,char** argv)
{
    Py_NoSiteFlag = 1;
    Py_Initialize();
    if(!Py_IsInitialized())
    {
        printf("the init is failed");
        exit(0);
    }
    PyRun_SimpleString("print 'start clone'");
    PyRun_SimpleString("import sys");
    PySys_SetArgv(argc, argv);
    PyRun_SimpleString("sys.path.remove('C:\\Windows\\SYSTEM32\\python27.zip')");
    PyRun_SimpleString("sys.path.remove('C:\\Python27\\Lib')");
    PyRun_SimpleString("sys.path.remove('C:\\Python27\\Lib\\lib-tk')");
    PyRun_SimpleString("sys.path.remove('C:\\Python27\\DLLs')");
    PyRun_SimpleString("sys.path.append('../')");
    PyRun_SimpleString("sys.path.append('../py/python27_lib.zip')");
    PyRun_SimpleString("sys.path.append('../py/gittle.zip')");
    PyRun_SimpleString("sys.path.append('../py/dulwich.zip')");
    PyRun_SimpleString("sys.path.append('../py/funky.zip')");
    PyRun_SimpleString("sys.path.append('../libs')");
    PyRun_SimpleString("print sys.path");
}

File_history::~File_history()
{
    Py_Finalize();
}

list<string> File_history::f_history(const char *path)
{
    multimap<string,string> file_history_map;
    PyObject *Ret = NULL;
    PyObject *pModule = NULL;
    PyObject *pArg = NULL;
    PyObject *pFile_history = NULL;

    Py_IncRef(Ret);
    list<string> fh_list;
    set<string> fname;
    pModule = PyImport_ImportModule((char*)"dulwich_client");
    if(!pModule)
    {
        printf("import the module failed!\n");
        return fh_list;
    }
    pFile_history = PyObject_GetAttrString(pModule,"file_history");
    if(NULL == pFile_history)
    {
        QMessageBox::information(NULL,"info","the function does not loaded!",0);
    }
    pArg = Py_BuildValue("(s)",path);
    if(NULL == pArg)
    {
        QMessageBox::information(NULL,"info","the arg is NULL");
    }
    if(!PyCallable_Check(pFile_history))
    {
        QMessageBox::information(NULL,"info","the function is bad!");
    }
    while(Ret == NULL)
    {
        Ret = PyEval_CallObject(pFile_history,pArg);
        if(PyErr_Occurred())
        {
            PyRun_SimpleString("fd = open('err.txt','a')");
            PyRun_SimpleString("sys.stderr = fd");
            PyRun_SimpleString("sys.stdout = fd");
            PyErr_Print();
            QMessageBox::information(NULL,"info","the function is bad!");
        }
    }

    int len = PyList_Size(Ret);
    PyObject *pyvalue;
    printf("the length is %d\n",len);
    for(int i = 0;i<len;++i)
    {
        pyvalue = PyList_GetItem(Ret,i);
        char *value = NULL;
        PyArg_Parse(pyvalue,"s",&value);
        printf("%s",value);
        string s(value);
        string::size_type pos;
        pos = s.find(',',0);
        string head = s.substr(0,pos);
        for(int i = pos+1;pos+1<s.length();i = pos + 1)
        {
            pos = s.find(',',i);
            string file_name = s.substr(i,pos - i);
            fname.insert(file_name);
            file_history_map.insert(pair<string,string>(file_name,head));
        }
    }
    set<string>::iterator tt = fname.begin();
    typedef multimap<string,string>::iterator Multi;
    for(;tt != fname.end();++tt)
    {
        string str;
        string key(*tt);
        str = *tt;
        pair<Multi,Multi> pos = file_history_map.equal_range(key);
        while(pos.first != pos.second)
        {
            str = str + "," + pos.first->second;
            ++pos.first;
        }
        fh_list.push_back(str);
    }

    printf("get the file_history finished\n");
    Py_DecRef(Ret);
    return fh_list;
}
