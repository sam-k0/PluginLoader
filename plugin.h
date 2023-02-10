#pragma once
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "gms.h"
using namespace std;

typedef double (*func)(double arg);
typedef double (*initfunc)(const char* loaderpath, const char* pluginName);

typedef struct Plugin
{
	func loadedFunction = NULL;
	HMODULE hModule = NULL;
    initfunc initFunc = NULL;
    stringToDLL pluginName;

	Plugin(stringToDLL dllpath, stringToDLL funcname, stringToDLL loaderpath, stringToDLL pName)
	{
	    pluginName = pName;
	    hModule = LoadLibraryA(dllpath);
		if(hModule)
		{
			loadedFunction = (func)GetProcAddress(hModule, "call");
			if (loadedFunction == NULL)
			{
				cout << "Error while getProcAddress: "<<GetLastError() << endl;
			}

            initFunc = (initfunc)GetProcAddress(hModule, "init");

            if(initFunc(loaderpath, pluginName) == GMTRUE)
            {
                // Successfully initialized
                cout << "[PluginLoader] Successfully initialized plugin " << pluginName << endl;
            }

			CloseHandle(hModule);
		}
	}

	double call(double arg)
	{
		return loadedFunction(arg);
	}

	void unload()
	{
		//FreeLibrary(hModule);
		//CloseHandle(hModule);
	}
};

