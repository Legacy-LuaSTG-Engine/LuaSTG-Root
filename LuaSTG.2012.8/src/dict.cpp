#pragma once
#include "dict.h"

template <class T>
int dict<T>::insert(const char * key, T * value)
{
	if(map.find((char *)key)==map.end())
	{
		if(set.find(value)!=set.end()) return DICT_VALUE_EXIST;
		size_t sz=strlen(key);
		char * tmpkey=new char[sz+1];
		if(!tmpkey) return DICT_MEM_FAIL;
		strcpy_s(tmpkey,sz+1,key);
		tmpkey[sz]='\0';
		map[tmpkey]=value;
		set.insert(value);
		return DICT_SUCCESS;
	}
	else return DICT_KEY_EXIST;
}

template <class T>
void dict<T>::print()
{
	std::map<char *,T *,charcmp>::iterator it;
	for(it=map.begin();it!=map.end();it++)
		printf("%s\t%d\n",it->first,it->second);
}

template <class T>
T * dict<T>::find(const char * key)
{
	std::map<char *,T *,charcmp>::iterator it;
	it=map.find((char *)key);
	if(it==map.end())
		return 0;
	else
		return it->second;
}

template <class T>
int dict<T>::remove(const char * key)
{
	std::map<char *,T *,charcmp>::iterator it;
	it=map.find((char *)key);
	if(it==map.end())
		return DICT_KET_NOT_EXIST;
	else
	{
		delete it->second;
		delete[] it->first;
		map.erase(it);
		set.erase(it->second);
		return DICT_SUCCESS;
	}
}

template <class T>
void dict<T>::clear()
{
	std::map<char *,T *,charcmp>::iterator it=map.begin();
	while(it!=map.end())
	{
		delete it->second;
		delete[] it->first;
		map.erase(it++);
	}
	set.clear();
}

template <class T>
T * dict<T>::begin()
{
	_it=map.begin();
	if(_it!=map.end())
		return _it->second;
	else return 0;
}

template <class T>
T * dict<T>::next()
{
	_it++;
	if(_it!=map.end())
		return _it->second;
	else return 0;
}

template <class T>
T * dict<T>::end()
{
	return 0;
}