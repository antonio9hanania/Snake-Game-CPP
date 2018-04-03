#ifndef _MENUS
#define _MENUS
#include <conio.h>
#include <iostream>
#include "startNewGame.h"
#include "SnakesGame.h"
#include "bulletStuck.h"
#include "MissionsContainer.h"

using namespace std;

int printMainMenu(); //will start game outside this fanc when the returned value is 2
int printSubMenu(Mission & mish, MissionsContainer & mishContainer, board& gameBoard, int scoreS1, int  scoreS2);


#endif // !_MENUS
