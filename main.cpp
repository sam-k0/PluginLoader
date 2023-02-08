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
vector<Plugin*> plugins;

gmx IYYC_Callback* getImplementation() {
    return implementation;
}

gmx double getValue(double in)
{
    return implementation->getData();
}

gmx GMBOOL load_plugin(stringToDLL path)
{
    std::string pth = getCurrentDir() + "\\PluginLoader.dll"; // get the rel. loc of the loader
    
    std::cout <<pth<<std::endl;

    plugins.push_back( new Plugin(path, "call", gmu::string_to_constcharptr(pth)));
    return GMTRUE;
}

gmx GMBOOL call_plugins(double arg)
{
    for(Plugin* p : plugins)
    {
        p->call(arg);
    }
}

gmx GMBOOL get_plugin_data(stringToDLL pluginName)
{
    //Change mapstorage to dsmap and trigger event
    string sPluginName = gmu::constcharptr_to_string(pluginName);

    vector<string> allKeys;
    int dsmap = CreateDsMap(0);

    StringMapPair* pluginInfo = mapHolder.getByKey(pluginName); // Check if a plugin with this name is loaded
    if(pluginInfo == nullptr)
    {
        cout << "get_plugin_data: Could not find plugin with this name: " << pluginName << endl;
        return 0.0;
    }

    allKeys = pluginInfo->value->getAllKeys();

    for(string mkey : allKeys)
    {
        char* kk = gmu::string_to_charptr(pluginInfo->value->getByKey(mkey)->key);
        char* vv = gmu::string_to_charptr(pluginInfo->value->getByKey(mkey)->value);
        DsMapAddString(dsmap, kk, vv);
    }

    CreateAsynEventWithDSMap(dsmap, EVENT_OTHER_SOCIAL);

    return GMTRUE;
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

