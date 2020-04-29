#pragma once
class FloatHelpers
{
public:
	static bool IsEqual(float i_lhs, float i_rhs);
	static bool IsNaN(float i_num);
	static bool IsZero(float i_num);
private:
	static float maxRelativeDiff;
};

