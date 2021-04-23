#include <iostream>

#include "kvs.h"
#include "useful.h"

uint32_t KVS::get_begin_address() const
{
	return begin_address;
}
uint32_t KVS::get_end_address() const
{
	return end_address;
}
uint32_t KVS::get_all_size() const
{
	return all_size;
}
uint32_t KVS::get_zero() const
{
	return zero;
}
void KVS::big_to_small()
{
	begin_address = CHANGE_SMALL(begin_address);
	end_address = CHANGE_SMALL(end_address);
	all_size = CHANGE_SMALL(all_size);
	zero = CHANGE_SMALL(zero);
}