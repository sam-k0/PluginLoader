#pragma once
#include <vector>
#include <string>
using namespace std;
// Switch this godforsaken Mini Map architecture to std::maps please oh my god

struct KeyValuePair {
	string key;
	string value;

	KeyValuePair(string k, string v)
	{
		key = k; value = v;
	}
};

class MiniMap {
private:
	vector<KeyValuePair*> data;

public:
	void addEntry(string k, string v)
	{
	    // Check if this value already exists
	    KeyValuePair* kvp = getByKey(k);
	    if(kvp == nullptr) // doesnt exist
        {
            data.push_back(new KeyValuePair(k, v));
        }
		else{
            // already exists
            kvp->value = v;
		}
	}

	void clear()
	{
		for(KeyValuePair* kvp : data)
        {
            if(kvp != nullptr)
            {
             delete kvp;
            }
        }
		data.clear();
	}

	void removeEntry(string k)
	{
		KeyValuePair* curr;
		for (int i = 0; i < data.size(); i++)
		{
			curr = data.at(i);
			if (curr->key == k)
			{
				data.erase(data.begin() + i);
				return;
			}
		}
		delete curr;
		curr = nullptr;
	}

	bool keyExists(string d)
	{
		KeyValuePair* curr;
		for (int i = 0; i < data.size(); i++)
		{
			curr = data.at(i);
			if (curr->key == d)
			{
				return true;
			}
		}
		return false;
	}

	bool valueExists(string d)
	{
		KeyValuePair* curr;
		for (int i = 0; i < data.size(); i++)
		{
			curr = data.at(i);
			if (curr->value == d)
			{
				return true;
			}
		}
		return false;
	}

	KeyValuePair* getByKey(string k)
	{
		KeyValuePair* curr;
		for (int i = 0; i < data.size(); i++)
		{
			curr = data.at(i);
			if (curr->key == k)
			{
				return curr;
			}
		}
		return nullptr;
	}

	vector<string> getAllKeys()
	{
		vector<string> keys;

		KeyValuePair* curr;
		for (int i = 0; i < data.size(); i++)
		{
			curr = data.at(i);
			keys.push_back(curr->key);
		}

		return keys;
	}

	int get_size()
	{
	    return data.size();
	}

	~MiniMap()
	{
        for(KeyValuePair* kvp : data)
        {
            if(kvp != nullptr)
            {
                delete kvp;
            }

        }

        data.clear();
	}
};

struct StringMapPair{
	string key;
	MiniMap* value;

	StringMapPair(string k, MiniMap* v)
	{
		key = k; value = v;
	}

	~StringMapPair()
	{
	    if(value != nullptr)
		delete value;
	}

};

class MiniMapHolder{

private:
    vector<StringMapPair*> maps;
public:
	void addEntry(string k, MiniMap* v)
	{
	    if(!keyExists(k))
        {
            maps.push_back(new StringMapPair(k, v));
        }
        else // already exists
        {
            StringMapPair* smp = getByKey(k); // get existing
            delete smp->value;                // delete value
            smp->value = v;
        }

	}

	void removeEntry(string k)
	{
		StringMapPair* curr;

		for (int i = 0; i < maps.size(); i++)
		{
			curr = maps.at(i);
			if (curr->key == k)
			{
				maps.erase(maps.begin() + i);
				return;
			}
		}
		delete curr->value;
		curr->value = nullptr;
		delete curr;
	}

	bool keyExists(string d)
	{
		StringMapPair* curr;
		for (int i = 0; i < maps.size(); i++)
		{
			curr = maps.at(i);
			if (curr->key == d)
			{
				return true;
			}
		}
		return false;
	}

	StringMapPair* getByKey(string k)
	{
		StringMapPair* curr;
		for (int i = 0; i < maps.size(); i++)
		{
			curr = maps.at(i);
			if (curr->key == k)
			{
				return curr;
			}
		}
		return nullptr;
	}

	vector<string> getAllKeys()
	{
		vector<string> keys;

		StringMapPair* curr;
		for (int i = 0; i < maps.size(); i++)
		{
			curr = maps.at(i);
			keys.push_back(curr->key);
		}

		return keys;
	}

	int get_size()
	{
	    return maps.size();
	}
};
