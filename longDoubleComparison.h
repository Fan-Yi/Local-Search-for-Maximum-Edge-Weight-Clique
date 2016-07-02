#ifndef LONG_DOUBLE_COMPARISON_H
#define LONG_DOUBLE_COMPARISON_H
#include <cmath>
#include "constants.h"

inline int long_double_equals(long double a, long double b, long double epsilon = EPS)
{
	return fabs(a - b) < epsilon;
}

inline int long_double_greater(long double a, long double b, long double epsilon = EPS)
{
	return a - b >= epsilon;
}

inline int long_double_smaller(long double a, long double b, long double epsilon = EPS)
{
	return b - a >= epsilon;
}
#endif
