#pragma once

class DisjointSet
{
private:
	int* s = nullptr;
	int count;


public:
	DisjointSet(int count);

	~DisjointSet();

	int find(int x);

	void unionSet(int a, int b);
#ifdef _DEBUG
	void printSet();
#endif //DEBUG
	

};