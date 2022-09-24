#pragma once

#define POOL_INIT_SIZE 65536
#define POOL_SUCCESS 0
#define POOL_MEM_FAIL 0xffffffff
#define POOL_INVALID_ID 1

template <class T>
class pool
{
private:
	bool * used;
	T * data;
	unsigned int * index;
	unsigned int _size,_top;
public:
	pool();
	int init(unsigned int init_size=POOL_INIT_SIZE);
	unsigned int newid();
	int freeid(unsigned int id);
	T * ptr(unsigned int id);
	void reset();
	void print();
	unsigned int size(){return _size;}
	unsigned int getn(){return _top;}
	~pool();
};