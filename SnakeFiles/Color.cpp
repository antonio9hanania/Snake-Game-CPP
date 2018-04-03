#include "Color.h"

void setTextColor(ColorOptions clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(int)clr);
}
