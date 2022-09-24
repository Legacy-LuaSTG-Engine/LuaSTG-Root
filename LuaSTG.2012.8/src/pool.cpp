#pragma once
#include "pool.h"

template <class T>
pool<T>::pool()
{
	used=0;
	data=0;
	index=0;
	_size=POOL_INIT_SIZE;
	_top=0;
}

template <class T>
int pool<T>::init(unsigned int init_size)
{
	_size=init_size;
	used=new bool[_size];
	data=new T[_size];
	index=new unsigned int[_size];
	if(used&&data&&index)
	{
		for(unsigned int i=0;i<_size;i++)
		{
			index[i]=i;
			used[i]=false;
		}
		return POOL_SUCCESS;
	}
	else
		return POOL_MEM_FAIL;
}

template <class T>
pool<T>::~pool()
{
	if(used) delete[] used;
	if(data) delete[] data;
	if(index) delete[] index;
}

template <class T>
unsigned int pool<T>::newid()
{
	if(_top!=_size)
	{
		used[index[_top]]=true;
		return index[_top++];
	}
	else
	{
		return -1;
	}
}

template <class T>
int pool<T>::freeid(unsigned int id)
{
	if(id<0||id>=_size||(!used[id])) return POOL_INVALID_ID;
	else
	{
		used[id]=false;
		index[--_top]=id;
		return POOL_SUCCESS;
	}
}

template <class T>
T * pool<T>::ptr(unsigned int id)
{
	if(id<0||id>=_size||(!used[id])) return 0;
	else return &data[id];
}

template <class T>
void pool<T>::reset()
{
	for(unsigned int i=0;i<_size;i++)
	{
		used[i]=false;
		index[i]=i;
	}
	_top=0;
}

template <class T>
void pool<T>::print()
{
	for(unsigned int i=0;i<_size;i++)
		printf("%d\t%d\t%d\n",used[i],index[i],data[i]);
	printf("\n");
}