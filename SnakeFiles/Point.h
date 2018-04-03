#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "Gotoxy.h"
#include "Direction.h"
#include "Color.h"

#define LINES 20
#define ROWS 80

using namespace std;

class Point
{
	int x;
	int y;
	int dir_x = 1;
	int dir_y = 0;
	void moveImpl() {
		x = (x + dir_x + ROWS) % ROWS;
		y = (y + dir_y + LINES) % LINES;
	}
public:
	int getDir_x()const { return dir_x; }
	int getDir_y()const { return dir_y; }
	void setDir_X(int new_X) { dir_x = new_X; }
	void setDir_Y(int new_Y) { dir_y = new_Y; }


	int getXCoord()const { return x; }
	int getYCoord() const { return y; }
	Point(int x1 = 1, int y1 = 1) {
		x = x1;
		y = y1;
	}
	void set(int x1 = 1, int y1 = 1) {
		x = x1;
		y = y1;
	}


	void draw(char c,ColorOptions clr  = WHITE) {
	gotoxy(x, y + 4);
	if (c == '#') {
		cout << Color(RED) << c << endl;
	}
	else if (c == '$') {
		cout << Color(GREEN) << c << endl;
	}
	else if (c == ' ')
		cout << Color(BLACK) << c << endl;
	else
		cout << Color(clr) << c<< endl;
	setTextColor(WHITE);

}



void changeDirWithoutTermsOfStuckSituation(Direction dir);
void changeDir(Direction dir);
	void move() {	
		int sameDir = rand() % 10;
		if (!sameDir) {
			int dir = rand() % 4;
			changeDir((Direction)dir);
		}
		moveImpl();
	}
	void move(Direction dir, bool stuckR, bool stuckL, bool stuckU, bool stuckD);
	bool isStuckequaldirection(Direction dir, bool stuckR, bool stuckL, bool stuckU, bool stuckD);
	

};

#endif
