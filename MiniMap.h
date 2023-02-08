#pragma once
#include <vector>
#include <string>
using namespace std;

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
		data.push_back(new KeyValuePair(k, v));
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
		delete value;
	}	
	
};

class MiniMapHolder{

private:
    vector<StringMapPair*> maps;
public:
	void addEntry(string k, MiniMap* v)
	{
		maps.push_back(new StringMapPair(k, v));
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
  
};
