#ifndef _GENERAL_FUNC
#define _GENERAL_FUNC
#include <iostream>
#include <windows.h> 
#include "Gotoxy.h"
#include <conio.h>
#include <cmath>
#include "Point.h"
#include <algorithm> 


using namespace std;

int findHowManyDigits(int n); //1000 has 4 digits
void winSong();
void looseSong();
void lowdingPress(int x, int y, int numOfUnits = 15);


double Distance(double dX0, double dY0, double dX1, double dY1);
int  DistanceTwoPoints(Point* p1, Point*p2, bool isBord = false);
int minBitweenFourNum(int comb1, int  comb2, int comb3, int comb4);

#endif