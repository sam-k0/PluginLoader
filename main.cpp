// dllmain.cpp : Defines the entry point for the DLL application.
#include "InterfaceImplement.h"
#include "plugin.h"
//#include "gms.h"
#include <unistd.h>
#include "CppMap.h"
#include <vector>

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

gmx GMBOOL load_plugin(stringToDLL path, stringToDLL pluginName)
{
    std::string pth = getCurrentDir() + "\\PluginLoader.dll"; // get the rel. loc of the loader

    plugins.push_back( new Plugin(path, "call", gmu::string_to_constcharptr(pth), pluginName));
    return GMTRUE;
}

gmx GMBOOL call_plugins(double arg)
{
    for(Plugin* p : plugins)
    {
        p->call(arg);
    }
    return GMTRUE;
}

gmx GMBOOL get_plugin_data(stringToDLL pluginName)
{
    //Change mapstorage to dsmap and trigger event

    map<string, string> pmap = plgStorage.getPluginMap(gmu::constcharptr_to_string(pluginName));
    if(pmap.size() == 0)
    {
        return GMFALSE;
    }

    int dsmap = CreateDsMap(0);

    map<string, string>::iterator it;
    for(it = pmap.begin(); it != pmap.end(); it++)
    {
        DsMapAddString(dsmap, gmu::string_to_charptr(it->first), gmu::string_to_charptr(it->second));
    }

    CreateAsynEventWithDSMap(dsmap, EVENT_OTHER_SOCIAL);

    return GMTRUE;
}

gmx GMINT get_plugin_data_map(stringToDLL pluginName, int dsmap)
{
    map<string, string> pmap = plgStorage.getPluginMap(gmu::constcharptr_to_string(pluginName));
    if(pmap.size() == 0)
    {
        return GMFALSE;
    }

    map<string, string>::iterator it;
    for(it = pmap.begin(); it != pmap.end(); it++)
    {
        DsMapAddString(dsmap, gmu::string_to_charptr(it->first), gmu::string_to_charptr(it->second));
    }

    return dsmap;
}

gmx stringFromDLL get_plugin_data_by_key(stringToDLL pn, stringToDLL key)
{
    map<string, string> pmap = plgStorage.getPluginMap(gmu::constcharptr_to_string(pn));
    if(pmap.size() == 0)
    {
        return gmu::string_to_charptr(string(""));
    }

    if(pmap.find(key) == pmap.end())
    {
        return gmu::string_to_charptr(string(""));
    }

    return gmu::string_to_charptr(pmap.find(key)->second);
}

gmx GMBOOL print_info(stringToDLL pluginName)
{
   /* StringMapPair* pluginInfo = mapHolder.getByKey(pluginName);

    if(pluginInfo)
    {
        cout << "Loaded plugin storage: " << pluginInfo->value->get_size() << endl;
        cout << "Total plugin entries: " << mapHolder.get_size() << endl;
    }
    else
    {
        cout << "There is no space allocated for this plugin." << endl;
        cout << "Total plugin entries: " << mapHolder.get_size() << endl;
    }*/
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

