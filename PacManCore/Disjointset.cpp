#include "pch.h"
#include "Disjointset.h"

DisjointSet::DisjointSet(int count)
{
    this->count = count;
	s = new int[count];
	for (int i = 0; i < count; i++)
		s[i] = -1;
}

DisjointSet::~DisjointSet()
{
	delete[] s;
}

int DisjointSet::find(int x)
{
	if (s[x] < 0)
		return x;
	else
		return (s[x] = find(s[x]));
}
void DisjointSet::unionSet(int a, int b)
{
	int roota = find(a), rootb = find(b);
	if (roota != rootb)
		s[rootb] = roota;

	return;
	if (s[rootb] < s[roota])
		s[roota] = rootb;
	else
	{
		if (s[roota] == s[rootb])
			s[roota]--;
		s[rootb] = roota;
	}
}

#ifdef _DEBUG
void DisjointSet::printSet()
{
	for (int i = 0; i < count; i++)
	{
		if (i != 0 && 0 == i % 9)
			cout << endl;
		cout << s[i] << " ";

	}
	cout << endl;
}
#endif //DEBUG