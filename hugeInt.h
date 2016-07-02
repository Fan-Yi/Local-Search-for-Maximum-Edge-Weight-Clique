#ifndef HUGE_INT
#define HUGE_INT
#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;
typedef long long LL;

//base: LLONG_MAX/2+1
//high
//low

class HugeInt
{
private:
	LL high;
	LL low;
public:
	//constructor
	HugeInt()
	{
		//empty constructor
	}
	HugeInt(int n)
	{
		high = 0;
		low = LL(n);
	}
	// copy constructor
	HugeInt(const HugeInt& hugeNum)
	{
		high = hugeNum.high;
		low = hugeNum.low;
	}
	HugeInt(long long h, long long l)
	{
		if(h > (LLONG_MAX >> 1) || l > (LLONG_MAX >> 1))
		{
			cout << "constructor of HugeInt failed, using too large numbers in construction" << endl;
			exit(1);
		}
		high = h;
		low = l;
	}
	// visit data members
	LL get_high_part()
	{
		return high;
	}
	LL get_low_part()
	{
		return low;
	}
	//inc
	HugeInt &operator++(int x)
	{
		if(low != LLONG_MAX >> 1)
		{
			low++;
			return *this;
		}
		low = 0;
		high++;
		return *this;
	}
	HugeInt &operator++()
	{
		if(low != LLONG_MAX >> 1)
		{
			low++;
			return *this;
		}
		low = 0;
		high++;
		return *this;
	}
	//comparison, can be used to compare negative integers which are bigger than -LLONG_MAX/2
	int operator>(HugeInt &hugeNum)
	{
		if(high > hugeNum.high) return 1;
		else if(high == hugeNum.high) return low > hugeNum.low;
	}
	int operator<(HugeInt &hugeNum)
	{
		if(high < hugeNum.high) return 1;
		else if(high == hugeNum.high) return low < hugeNum.low;
	}
	int operator==(HugeInt &hugeNum)
	{
		if(high == hugeNum.high && low == hugeNum.low) return 1;
		else return 0;
	}
	int operator>(int n)
	{
		if(high > 0) return 1;
		if(low > n) return 1;
		return 0;
	}
	int operator<(int n)
	{
		if(high > 0) return 0;
		if(low < n) return 1;
		return 0;
	}
	int operator==(int n)
	{
		if(high != 0) return 0;
		if(low == n) return 1;
		return 0;
	}
	//assignment
	HugeInt &operator=(HugeInt hugeNum)
	{
		high = hugeNum.high;
		low = hugeNum.low;
		return *this;
	}
	HugeInt &operator=(int n)//can be assigned as a negative integer which is bigger than -LLONG_MAX/2
	{
		high = 0;
		low = LL(n);
		return *this;
	}
	HugeInt &operator=(long n)
	{
		high = 0;
		low = LL(n);
		return *this;
	}
	//plus
	HugeInt operator+(HugeInt hugeNum)
	{
		HugeInt tmpHugeNum(0);
		if(low + hugeNum.low > (LLONG_MAX >> 1))
		{
			tmpHugeNum.low = low + hugeNum.low - ((LLONG_MAX >> 1) + 1);
			tmpHugeNum.high = high + hugeNum.high + 1;
			return tmpHugeNum;
		}
		tmpHugeNum.low = low + hugeNum.low;
		tmpHugeNum.high = high + hugeNum.high;
		return tmpHugeNum;
	}
	HugeInt operator+(int n)
	{
		HugeInt tmpHugeNum(0);
		if(low + n > (LLONG_MAX >> 1))
		{
			tmpHugeNum.low = low + n - ((LLONG_MAX >> 1) + 1);
			tmpHugeNum.high = high + 1;
			return tmpHugeNum;
		}
		tmpHugeNum.low = low + n;
		tmpHugeNum.high = high;
		return tmpHugeNum;
	}
	//div
	long double operator/(long double ld_n)
	{
		LL h = high, l = low;
		while(h != 0)
		{
			ld_n /= 2;
			if(h % 2 == 0)
			{
				h >>= 1;
				l >>= 1;
			}
			else
			{
				h >>= 1;
				l = (((LLONG_MAX >> 1) + 1) + l) >> 1;
			}
		}
		return ((long double)l) / ld_n;			
	}
	//modal
	unsigned int operator%(int divisor)
	{
		return ((high * (((LLONG_MAX >> 1) + 1) % divisor) % divisor) + low % divisor) % divisor;
	}
	//friend functions
	//comparison
	friend int operator>=(HugeInt hugeNum1, HugeInt hugeNum2);
	friend int operator<=(HugeInt hugeNum1, HugeInt hugeNum2);
	friend int operator>=(HugeInt hugeNum, int n);
	friend int operator<=(HugeInt hugeNum, int n);
	//manipulation
	friend HugeInt operator+(int n, HugeInt hugeNum);
	friend long double operator*(HugeInt hugeNum, long double ld_n);
	friend long double operator/(long double ld_n, HugeInt hugeNum);
	//short hand
	friend HugeInt &operator+=(HugeInt &hugeNum1, HugeInt hugeNum2);
	friend HugeInt &operator+=(HugeInt &hugeNum, int n);
};
//friend functions
	int operator>=(HugeInt hugeNum1, HugeInt hugeNum2)
	{
		if(hugeNum1 > hugeNum2 || hugeNum1 == hugeNum2)
			return 1;
		return 0;
	}
	int operator<=(HugeInt hugeNum1, HugeInt hugeNum2)
	{
		if(hugeNum1 < hugeNum2 || hugeNum1 == hugeNum2)
			return 1;
		return 0;
	}
	int operator>=(HugeInt hugeNum, int n)
	{
		if(hugeNum > n || hugeNum == n) 
			return 1;
		return 0;
	}
	int operator<=(HugeInt hugeNum, int n)
	{
		if(hugeNum < n || hugeNum == n)
			return 1;
		return 0;
	}
	HugeInt operator+(int n, HugeInt hugeNum)
	{
		return hugeNum + n;
	}
	long double operator*(HugeInt hugeNum, long double ld_n)
	{
		return hugeNum / (1.0 / ld_n);
	}
	long double operator/(long double ld_n, HugeInt hugeNum)
	{
		while(hugeNum.high != 0)
		{
			ld_n /= 2;
			if(hugeNum.high % 2 == 0)
			{
				hugeNum.high >>= 1;
				hugeNum.low >>= 1;
			}
			else
			{
				hugeNum.high >>= 1;
				hugeNum.low = (((LLONG_MAX >> 1) + 1) + hugeNum.low) >> 1;
			}
		}
		return ld_n / ((long double)hugeNum.low);
	}
	HugeInt &operator+=(HugeInt &hugeNum1, HugeInt hugeNum2)
	{
		hugeNum1 = hugeNum1 + hugeNum2;
		return hugeNum1;
	}
	HugeInt &operator+=(HugeInt &hugeNum, int n)
	{
		hugeNum = hugeNum + n;
		return hugeNum;
	}
/////////////////////////////////////////////////////////////
	ostream &operator<<(ostream &stream, HugeInt &hugeNum)
	{
		stream << hugeNum.get_high_part() << " * " << ((LLONG_MAX >> 1) + 1) << " + " << hugeNum.get_low_part();
		return stream;
	}
#endif
