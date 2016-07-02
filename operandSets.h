#ifndef OPERAND_SETS_H
#define OPERAND_SETS_H

#include "hugeInt.h"
#include "longDoubleComparison.h"

class ScoreAgePickSet : public Bijection
{
public:
	ScoreAgePickSet(int sz) : Bijection(sz)
	{
	}
	~ScoreAgePickSet()
	{
	}
	int best_element(long double* score, HugeInt* time_stamp)
	{
		if(!array_size) return 0;
		int best_e = at(begin());
		int i;
		for(i = begin() + 1; i != end(); i++)
		{
			int e = array[i];
			if(long_double_greater(score[e], score[best_e]) || (long_double_equals(score[e], score[best_e]) && time_stamp[e] < time_stamp[best_e]))
				best_e = e;
		}
		return best_e;
	}
};
class ConfchangedScoreAgePickSet : public Bijection
{
public:	
	ConfchangedScoreAgePickSet(int sz) : Bijection(sz)
	{
	}
	~ConfchangedScoreAgePickSet()
	{
	}

	int best_element(int* confChange, long double* score, HugeInt* time_stamp)
	{
		if(!array_size) return 0;
		int best_e = 0;
		int i;
		for(i = begin(); i != end(); i++)
		{
			int e = array[i]; 
			if(confChange[e])
			{
				best_e = e;
				i++;
				break;
			}
		}
		for(; i != end(); i++)
		{
			int e = array[i];
			if(!confChange[e]) continue;
			if(long_double_greater(score[e], score[best_e]) || (long_double_equals(score[e], score[best_e]) && time_stamp[e] < time_stamp[best_e]))
				best_e = e;
		}
		return best_e;
	}

	int best_element(int* swap_partner, int* confChange, long double* score, HugeInt* time_stamp)
	{
		if(!array_size) return 0;
		int best_e = 0;
		int i;
		for(i = begin(); i != end(); i++)
		{
			int e = array[i]; 
			if(confChange[e])
			{
				best_e = e;
				i++;
				break;
			}
		}
		for(; i != end(); i++)
		{
			int e = array[i];
			if(!confChange[e]) continue;
			if(long_double_greater(score[e] + score[swap_partner[e]], score[best_e] + score[swap_partner[e]]) || (long_double_equals(score[e] + score[swap_partner[e]], score[best_e] + score[swap_partner[e]]) && time_stamp[e] < time_stamp[best_e]))
				best_e = e;
		}
		return best_e;
	}
};
#endif
