#pragma once

class Color;

class Box
{
public:
	VECTOR Pos;
	float Hight;
	float Width;
	Box();
	Box(const VECTOR& pos, float hight, float hidth);
	void Draw(const Color& color, bool isfill = TRUE);
private:
};
