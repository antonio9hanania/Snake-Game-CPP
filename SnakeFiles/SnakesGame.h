#ifndef _SNAKES_GAME_H_
#define _SNAKES_GAME_H_

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Snake.h"
#include "board.h"
#include "Point.h"
#include "Color.h"
#include "Menus.h"
#include "MissionsContainer.h"
#include "Creature.h"
#include "RowFlyers.h"
#include "Direction.h"
#include "NumFlyers.h"
#include "LineFlyers.h"

#define SIXTY 60

using namespace std;

enum KEYS { ESC = 27 };

class SnakesGame {
	enum { size = 2 }; // a constant
	// data member: array of snakes
	Snake p[size] = {
		{ 3,{ 10, 10 }, '#' }, // snake 1
		{ 3,{ 15, 15 }, '$' }  // snake 2
	//{ { 15, 70 }, '@' }  // snake 3
	};
	Creature* flyers[5] = {
		new RowFlyer1{ true, '!', Point(30, 23),RIGHT ,false },
		new RowFlyer1{ true, '!', Point(50, 15), LEFT ,true },
		new NumFlyers{ true,'%', Point(10,19),LEFT, false },
		new LineFlyers{ true , '@',Point(45,23),UP,true },
		new LineFlyers{ true,'@',Point(55,15),DOWN,false }
	};

	board gameBoard{ 3,3,{ 10,10 },{ 15, 15 },'#', '$' };
	MissionsContainer MishCont{};
	Mission mish;

	char keyPressedSaver[500];
	int logsSizeKeyPressed = 0;

public:
	SnakesGame() {
		p[0].setKeys('a', 'd', 'w', 'x', 'z');
		p[1].setKeys('j', 'l', 'i', 'm', 'n');

	}

	void run();
	int whoWonTheBattle(int i, bool WinOrLoose);
	void updatingScoreWinLose(int & scoreS1, int & scoreS2, int whoWon);
	void updateDieCounterArr(int dieCounters[2],int i);
	void DeleteSnakeFromScreenAndBoard_ByIndex(int i);
	void hittenSnake(int i, TypeOfBulletHit hit, int dieCounters[2], FlyHit FlyerHitSnake,bool isRecord = false);
	void bringDiedSnakesToLife(int dieCounters[2]);
	void handleKeyPressed(char & keyPressed, int & scoreS1, int & scoreS2, int & numCounter, int dieCouners[2]);
	void runReplay();

};

#endif


