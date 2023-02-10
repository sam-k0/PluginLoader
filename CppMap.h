#ifndef CPPMAP_H_INCLUDED
#define CPPMAP_H_INCLUDED
#include <string>
#include <map>

using namespace std;

class PluginStorage
{
private:
    map<string, map<string, string>> dataStorage;

public:
    void updatePluginStorage(string pluginName, string key, string value)
    {
        if(dataStorage.find(pluginName) == dataStorage.end()) // Does the plugin have a map yet?
        {
            // not found
            // The plugin does not have a dedicated map yet
            map<string, string> newMap = map<string, string>();
            newMap.insert(pair<string, string>(key, value));

            dataStorage.insert(pair<string, map<string, string>>(pluginName, newMap));
        }
        else
        {
            // found
            if(dataStorage.at(pluginName).find(key) == dataStorage.at(pluginName).end()) // Does the entry exist already?
            {
                // not found
                dataStorage.at(pluginName).insert(pair<string, string>(key, value));
            }
            else
            {
                // found
                map<string, string>::iterator it = dataStorage.at(pluginName).find(key);
                it->second = value;
            }
        }

    }

    map<string, string> getPluginMap(string pName)
    {
        map<string, map<string, string>>::iterator it = dataStorage.find(pName);

        if (it != dataStorage.end())
        {
            return it->second;
        }
        return map<string, string>();
    }

    string getPluginStorage(string pluginName, string key)
    {
        if(dataStorage.find(pluginName) != dataStorage.end()) // Does the plugin have a map yet?
        {
            // found the plugin, but does a key in there exist?
            if(dataStorage.at(pluginName).find(key) != dataStorage.at(pluginName).end()) // Does the entry exist already?
            {
                map<string, string>::iterator it = dataStorage.at(pluginName).find(key);
                return it->second;
            }
        }
        return "";
    }

};


#endif // CPPMAP_H_INCLUDED
