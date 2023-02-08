#pragma once
#include "gms.h"
#include "PluginInterface.h"
#include "MiniMap.h"
using namespace std;

MiniMap mapStorage;

const int EVENT_OTHER_SOCIAL = 70;

class Implementation : public IYYC_Callback
{
public:
    void setData(const char* key, const char* value) // add a new key value pair to storage
    {
        cout << "In set data"<< endl;
        string k, v;
        k = gmu::constcharptr_to_string(key);
        v = gmu::constcharptr_to_string(value);
        mapStorage.addEntry(k, v);
    }

    double getData()
    {
        cout << mapStorage.getByKey("0")->value << endl; 
        return 123.0;
    }

    void trigger()
    {
        cout << "In trigger method "<<endl;

        // Callen geht nur die Async scheisse nicht

        // Change mapstorage to dsmap and trigger event
        //int dsmap = CreateDsMap(0);
        //DsMapAddDouble(dsmap, "AM", 293.0);
        //CreateAsynEventWithDSMap(dsmap, 70);

        /*cout << "in trigger method" << endl;
        vector<string> allkeys = mapStorage.getAllKeys();
        KeyValuePair* currpair;
        int dsmap = CreateDsMap(0);
        cout << "in trigger method 2" << endl;
        string tempk, tempv;

        for (string k : allkeys)
        {
            currpair = mapStorage.getByKey(k);
            tempk = currpair->key;
            tempv = currpair->value;
            DsMapAddString(dsmap, gmu::string_to_charptr(tempk), gmu::string_to_charptr(tempv));
        }



        CreateAsynEventWithDSMap(dsmap, EVENT_OTHER_SOCIAL);

        cout << "post async" << endl;*/
    }
};


