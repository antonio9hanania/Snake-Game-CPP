#pragma once

#include <Windows.h>
#include <iostream>

using namespace std;
enum ColorOptions {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGREY, DARKGREY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE, BOLD = FOREST_USER_RID_MAX
};

void setTextColor(ColorOptions clr);

class Color {
	int _foreground;
public:
	Color(int foreground)
		: _foreground(foreground){}
	
	friend ostream& operator<<(ostream& out, const Color& c) {
		setTextColor((ColorOptions)c._foreground);
		return out;
	}
};


//use: cout << Color(BLUE) << "BlaBlaBla";
//	   cout <<Color (WHITE) << "Back To White;
