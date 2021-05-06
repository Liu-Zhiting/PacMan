#pragma once
#include "pch.h"

class DisjointSet
{
private:
	int* s = nullptr;
	int count;
public:
	DisjointSet(int count)
	{
		this->count = count;
		s = new int[count];
		for (int i = 0; i < count; i++)
			s[i] = -1;
	}

	~DisjointSet()
	{
		delete[] s;
	}

	int find(int x)
	{
		if (s[x] < 0)		
			return x;		
		else	
			return (s[x] = find(s[x]));
	}
	void unionSet(int a, int b)
	{
		if (s[b] < s[a])
			s[a] = b;
		else
		{
			if (s[a] == s[b])
				s[a]--;
			s[b] = a;
		}
	}

};

void getNewMap(int a, int b, int* data)
{
	
	
	//init


	//use disjoint set to generate map


}

