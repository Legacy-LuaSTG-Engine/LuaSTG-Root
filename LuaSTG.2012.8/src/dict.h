#pragma once

#include <map>
#include <set>
#include <string>

struct charcmp{bool operator()(char * lhs,char * rhs)const{return strcmp(lhs,rhs)<0;}};

#define DICT_SUCCESS 0
#define DICT_MEM_FAIL 1
#define DICT_KEY_EXIST 2
#define DICT_KET_NOT_EXIST 3
#define DICT_VALUE_EXIST 4

template <class T>
class dict
{
private:
	std::map<char *,T *,charcmp> map;
	std::set<T *> set;
	typename std::map<char *,T *,charcmp>::iterator _it;
	T * begin();
	T * next();
	T * end();
public:
	int insert(const char * key,T * value);
	T * find(const char * key);
	int remove(const char * key);
	void clear();
	void print();
	~dict(){clear();};
	friend class BIF;
};