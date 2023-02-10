#pragma once
#include "gms.h"
#include "PluginInterface.h"
#include "CppMap.h"
using namespace std;

PluginStorage plgStorage;

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

        plgStorage.updatePluginStorage(pn, k ,v);
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


