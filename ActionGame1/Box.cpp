#include"DxLib.h"
#include"Color.h"
#include"Box.h"
Box::Box()
{
}
Box::Box(const VECTOR& pos, float hight, float width)
{
    Pos = pos;
    Hight = hight;
    Width = width;
}

void Box::Draw(const Color& color, bool isfill)
{
    const auto sizex = Width / 2;
    const auto sizey = Hight / 2;
    DrawBoxAA(Pos.x - sizex, Pos.y - sizey, Pos.x + sizex, Pos.y + sizey, color.GetHandle(), isfill);
}