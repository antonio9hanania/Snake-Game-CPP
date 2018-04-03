#include "GeneralFunc.h"

int findHowManyDigits(int n)
{
	int res = 0;
	if (n == 0)
		return 1;

	while (n != 0)
	{
		n /= 10;
		res++;
	}
	return res;
}

void winSong()
{
	


	Beep(261, 100);
	Beep(293, 100);
	Beep(329, 100);
	Beep(392, 200);
	Sleep(150);
	Beep(329, 100);
	Beep(392, 500);
}


void looseSong()
{
	Beep(784, 200);
	Beep(261, 500);
}



void lowdingPress(int x, int y, int numOFUnits)
{
	char a = 177, b = 219;
	cout << "\t\t\t\t";
	gotoxy(x, y);
	for (int i = 0; i <= numOFUnits; i++)
		cout << a;
	cout << "\r";
	cout << "\t\t\t\t";
	gotoxy(x, y);
	
	for (int i = 0; i <= numOFUnits && !_kbhit(); i++)
	{
		cout << b;
		Sleep(500);

		if (i == 15) {
			cout << "\t\t\t\t";
			gotoxy(x, y);
			for (int i = 0; i <= numOFUnits; i++)
				cout << a;
			cout << "\r";
			cout << "\t\t\t\t";
			gotoxy(x, y);
			i = 0;
		}
	}
}



double Distance(double dX0, double dY0, double dX1, double dY1)
{
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

int DistanceTwoPoints(Point* p1, Point*p2, bool isBord)
{
	int Ysize = 20;
	int Xsize = 80;
	int x1, y1, x2, y2;
	int comb1, comb2, comb3, comb4;
	int minimum;
	x1 = abs(p1->getXCoord() - p2->getXCoord());
	if (!isBord)
		y1 = abs(p1->getYCoord() - 4 - p2->getYCoord()); //change :  y1 = abs(p1->getYCoord()-4 - p2->getYCoord());
	else
		y1 = abs(p1->getYCoord() - p2->getYCoord());

	x2 = abs(Xsize - x1);
	y2 = abs(Ysize - y1);
	//Combinations :
	comb1 = x1 + y1;
	comb2 = x2 + y2;
	comb3 = x1 + y2;
	comb4 = x2 + y1;
	minimum = minBitweenFourNum(comb1, comb2, comb3, comb4);
	return minimum;
}
int minBitweenFourNum(int comb1, int  comb2, int comb3, int comb4)
{
	return min(min(comb1, comb2), min(comb3, comb4));
}