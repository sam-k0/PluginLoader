// dllmain.cpp : Defines the entry point for the DLL application.
#include "InterfaceImplement.h"
#include "plugin.h"
//#include "gms.h"
#include <unistd.h>

std::string getCurrentDir() // Returns EXE directory
{
    char cCurrentPath[FILENAME_MAX]; // get working directory into buffer
    if (!getcwd(cCurrentPath, sizeof(cCurrentPath)))
        exit(-1);
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; // not really required

    char* s = cCurrentPath; // save path from buffer into currentpath chararr

    return std::string(s);
}

gmx double check(double i)
{
    int dsmap = CreateDsMap(0);
    DsMapAddDouble(dsmap, "AM", 293.0);
    CreateAsynEventWithDSMap(dsmap, 70);
    return 1.0;
}


Implementation* implementation = new Implementation();
Plugin* pplugin = NULL;

gmx IYYC_Callback* getImplementation() {
    return implementation;
}

gmx double getValue(double in)
{
    return implementation->getData();
}

gmx GMBOOL load_plugin(stringToDLL path)
{
    pplugin = new Plugin(path, "call");
    std::string pth = getCurrentDir() + "\\PluginLoader.dll";
    std::cout <<pth<<std::endl;

    pplugin->call(969.0, gmu::string_to_constcharptr(pth));

    return GMTRUE;
}

gmx GMBOOL call_plugins(double arg, stringToDLL loaderpath)
{
    return pplugin->call(arg,loaderpath);
}

gmx GMBOOL get_plugin_data()
{
    //Change mapstorage to dsmap and trigger event

    cout << "getPluginData" << endl;
    vector<string> allkeys = mapStorage.getAllKeys();
    KeyValuePair* currpair;
    int dsmap = CreateDsMap(0);

    string tempk, tempv;

    /*for (string k : allkeys)
    {
        currpair = mapStorage.getByKey(k);
        tempk = currpair->key;
        tempv = currpair->value;
        DsMapAddString(dsmap, gmu::string_to_charptr(tempk), gmu::string_to_charptr(tempv));
    }*/
    DsMapAddString(dsmap, "sus", "sus");

    CreateAsynEventWithDSMap(dsmap, EVENT_OTHER_SOCIAL);
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

