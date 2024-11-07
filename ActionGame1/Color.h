#pragma once
#include"DxLib.h"
class  Color
{
public:
	constexpr Color()
		: R{ 0 }
		, G{ 0 }
		, B{ 0 } {}

	constexpr Color(int R, int G, int B)
		: R{ R }
		, G{ G }
		, B{ B } {}

	int GetHandle() const;

private:
	int R;
	int G;
	int B;
};