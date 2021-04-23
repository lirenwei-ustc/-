#ifndef __INDEX_H
#define __INDEX_H

#include <iostream>

using namespace std;

class Index
{
private:
	int begin, size;
	static int counts;

public:
	Index(int b, int s)
	{
		begin = b;
		size = s;
	}

public:
	inline int get_begin_addres() { return begin; }
	inline int get_size() { return size; }

public:
	friend ostream& operator<<(ostream& output, const Index& index)
	{
		output << "Id : " << counts++ << " Address : " << reinterpret_cast<int*>(index.begin);
		output << "   , size " << reinterpret_cast<int*>(index.size) << endl;

		return output;
	}
};

#endif