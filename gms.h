#pragma once
typedef const char* stringToDLL;    // String passed GM --> DLL
typedef char* stringFromDLL;        // String passed DLL -- > GM
typedef double GMBOOL;
typedef double GMINT;


#define GMTRUE 1.0
#define GMFALSE 0.0

#define gmx extern "C" __declspec(dllexport)

/* Regular includes */
#include <string>
#include <string.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std; // Fight me

vector<char*> disposableStrings;

void (*CreateAsynEventWithDSMap)(int, int) = NULL;
int (*CreateDsMap)(int _num, ...) = NULL;
bool (*DsMapAddDouble)(int _index, char* _pKey, double value) = NULL;
bool (*DsMapAddString)(int _index, char* _pKey, char* pVal) = NULL;


gmx void RegisterCallbacks(char* arg1, char* arg2, char* arg3, char* arg4)
{
    void (*CreateAsynEventWithDSMapPtr)(int, int) = (void (*)(int, int))(arg1);
    int(*CreateDsMapPtr)(int _num, ...) = (int(*)(int _num, ...)) (arg2);
    CreateAsynEventWithDSMap = CreateAsynEventWithDSMapPtr;
    CreateDsMap = CreateDsMapPtr;

    bool (*DsMapAddDoublePtr)(int _index, char* _pKey, double value) = (bool(*)(int, char*, double))(arg3);
    bool (*DsMapAddStringPtr)(int _index, char* _pKey, char* pVal) = (bool(*)(int, char*, char*))(arg4);

    DsMapAddDouble = DsMapAddDoublePtr;
    DsMapAddString = DsMapAddStringPtr;
}

/**
* @brief This is the static helper class.
*        Access is namespace-like: gmu::function
*/
namespace gmu {

    /**
    * @param s String to convert to char*
    * @brief Convert string to char*
    */
    static char* string_to_charptr(string s)
    {
        char* c = _strdup(s.c_str());

        if(std::find(disposableStrings.begin(), disposableStrings.end(), c) == disposableStrings.end())
        {
            disposableStrings.push_back(c);
        }

        return c;
    }

    gmx GMBOOL cleanStrings()
    {
        for(char* e : disposableStrings)
        {
            free(e);
        }

        cout << "Freed " << disposableStrings.size() << " strings." << endl;
        disposableStrings.clear();
        return GMTRUE;
    }

    /**
    * @param s String to convert to const char*
    * @brief Convert string to const char*
    */
    static const char* string_to_constcharptr(string s)
    {
        return s.c_str();
    }

    /**
    * @param p const char* to convert
    * @brief Convert const char* to string
    */
    static string constcharptr_to_string(const char* p)
    {
        return string(p);
    }

    /**
    * @param s String to print
    * @brief Prints a string to GMS debug console
    */
    static void debugmessage(string s)
    {
        std::cout << s << std::endl;
    }


};

