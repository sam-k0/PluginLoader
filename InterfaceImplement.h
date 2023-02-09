#pragma once
#include "gms.h"
#include "PluginInterface.h"
#include "MiniMap.h"
using namespace std;

MiniMapHolder mapHolder;

const int EVENT_OTHER_SOCIAL = 70;

class Implementation : public IYYC_Callback
{
public:
    void setData(const char* pluginName,const char* key, const char* value) // add a new key value pair to storage
    {
        string k, v, pn;
        k = gmu::constcharptr_to_string(key);
        v = gmu::constcharptr_to_string(value);
        pn = gmu::constcharptr_to_string(pluginName);

        StringMapPair* pluginStorage = mapHolder.getByKey(pn); // try to get the String <--> Dsmap storage

        if(pluginStorage != nullptr) // the storage already exists
        {
            if(pluginStorage->value != nullptr)
            {
                pluginStorage->value->addEntry(k,v);
            }
        }
        else // First time calling the plugin storage
        {
            mapHolder.addEntry(gmu::constcharptr_to_string(pluginName), new MiniMap());

            pluginStorage = mapHolder.getByKey(gmu::constcharptr_to_string(pluginName));

            pluginStorage->value->addEntry(k,v);
        }
    }

    double getData() // not used
    {
        return 123.0;
    }

    void trigger() // not used
    {
        cout << "In trigger method "<<endl;
    }
};


