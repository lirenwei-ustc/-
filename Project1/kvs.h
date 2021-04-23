#ifndef __KVS_H
#define __KVS_H

#include <iostream>
#include <fstream>

using namespace std;

class KVS
{
private:
	uint32_t begin_address, end_address, all_size, zero;

public:
	KVS()
	{
		begin_address = end_address = all_size = zero = 0;
	}
	KVS(uint32_t b, uint32_t e, uint32_t a)
	{
		begin_address = b;
		end_address = e;
		all_size = a;
		zero = 0;
	}
	KVS(const KVS& small_wav)
	{
		begin_address = small_wav.begin_address;
		end_address = small_wav.end_address;
		all_size = small_wav.all_size;
		zero = small_wav.zero;
	}

public:
	friend ifstream& operator >>(ifstream& fin, KVS& kvs)
	{
		fin.read((char*)&kvs.begin_address, 4);
		fin.read((char*)&kvs.end_address, 4);
		fin.read((char*)&kvs.all_size, 4);
		fin.read((char*)&kvs.zero, 4);

		return fin;
	}
	friend ostream& operator <<(ostream& output, const KVS& kvs)
	{
		output << reinterpret_cast<void*>(kvs.begin_address) << " , " << reinterpret_cast<void*>(kvs.end_address) << " , ";
		output << reinterpret_cast<void*>(kvs.all_size) << " , " << reinterpret_cast<void*>(kvs.zero) << endl;

		return output;
	}

public:
	uint32_t get_begin_address() const;
	uint32_t get_end_address() const;
	uint32_t get_all_size() const;
	uint32_t get_zero() const;
	
	void big_to_small();
};

#endif