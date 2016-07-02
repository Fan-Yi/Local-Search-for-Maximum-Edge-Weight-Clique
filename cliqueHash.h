#ifndef CLIQUE_HASH
#define CLIQUE_HASH

#include "constants.h"

//hash(C)= (\sum_{v_i \in C}2^i) mod p, where p = PRIME_NUM

class CliqueHash{
private:
	int* two_power_mod_p;
	char* hash_entries;
	int curr_hash_entry;
	int hash_bound;
public:
	CliqueHash(int v_num)
	{
		two_power_mod_p = new int[v_num + 2];
		two_power_mod_p[0] = 1;
		for(int v = 1; v <= v_num; v++)
		{
			two_power_mod_p[v] = (two_power_mod_p[v-1] * 2) % PRIME_NUM;
		}
///////////////////////////////////////////////
		hash_entries = new char[PRIME_NUM];
		memset(hash_entries, 0, sizeof(char) * PRIME_NUM);
///////////////////////////////////////////////
		curr_hash_entry = 0;
		hash_bound = 1;
	}
	~CliqueHash()
	{
		delete[] two_power_mod_p;
		delete[] hash_entries;
	}
	void reset_hash_entry()
	{
		curr_hash_entry = 0;
	}
	void update_hash_wrt_add(int v)
	{
		curr_hash_entry = (curr_hash_entry + two_power_mod_p[v]) % PRIME_NUM;
	}
	void update_hash_wrt_drop(int v)
	{
		curr_hash_entry = (curr_hash_entry + PRIME_NUM - two_power_mod_p[v]) % PRIME_NUM;
	}
	void mark_hash_entry()
	{
		hash_entries[curr_hash_entry]++;
	}
	int curr_hash_entry_marked_too_frequently()
	{
		if(hash_entries[curr_hash_entry] > hash_bound) return 1;
			return 0;
	}
};

#endif
