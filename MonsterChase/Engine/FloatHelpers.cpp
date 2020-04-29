#include "FloatHelpers.h"
#include <math.h>
#include <cfloat>

float FloatHelpers::maxRelativeDiff = FLT_EPSILON;

//Using Relative Epsilon Comparison
bool FloatHelpers::IsEqual(float i_lhs, float i_rhs)
{
	float difference = (float)fabs(i_lhs - i_rhs);
	float largest = (i_lhs > i_rhs) ? i_lhs : i_rhs;
	if (difference <= largest * maxRelativeDiff)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool FloatHelpers::IsNaN(float i_num)
{
	volatile float val = i_num;
	return val != val;
}

//Fast zero compare
bool FloatHelpers::IsZero(float i_num)
{
	return fabs(i_num - 0.0f) <= maxRelativeDiff;
}
