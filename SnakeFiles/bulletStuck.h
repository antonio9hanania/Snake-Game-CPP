#ifndef _BULLET_STUCK
#define _BULLET_STUCK
#include "Direction.h"
#include "Point.h"
#include "Color.h"
#include "board.h"
#include "Bullet.h"


enum TypeOfBulletHit { ON_NUM, ON_MY_BULLET, ON_OTHER_BULLET, ON_MY_SNAKE, ON_OTHER_SNAKE, ON_SPACE, NOT_RELEVENT, ON_BOTH_SNAKES, ON_ROW_FLAYER, ON_LINE_FLAYER_PIN, ON_LINE_PLAYER_NPIN,ON_NUM_EATER };

class BulletStuck {
	
#define PHISE_SIZE 5

	int numOfBullets;
	Direction bulletDir;
	char BulletChar;

	BULLET bulletArr[PHISE_SIZE];

	int logic_size;

	ColorOptions clrOfMyBullets;
	int xCoordToPrintStuck, yCoordToPrintStuck;

	

public:
	BulletStuck(Direction d, char ch = '*');
	void changeBulletDataMembers(Point head, Direction dir, bool isSTUCK);
	void initialBulletStackAndRemoveBullets(Point head, Direction dir,board& gameBoard);
	TypeOfBulletHit checkAndMoveIfPossible(char keyPressed, char shootingChar, Point headOfSnake, Direction dir, bool isSTUCKByPressingReverseKey, board & gameBoard, char currentSnakeChar,BulletStuck& rivalStuck,int dieCouner, int & numCounter);
	void printVisualStuck(int x, int y, int numOFUnits = 5, ColorOptions clr = WHITE);
	void setColorOfBulletsAndXCoordsToPrintStuck(ColorOptions clrOfSnake, int x, int y);
	int getLogicSizeOfBulletStuck() const {	return logic_size;}
	ColorOptions getStackColor() {	return clrOfMyBullets;}
	void removeBulletsOnScreenAndBoard(board& gameBoard);
	TypeOfBulletHit moveBulletOperation(board & gameBoard, BULLET & bulletTomove, char currentSnakeChar,BulletStuck& rivalStuck, int & numCounter);
	TypeOfBulletHit ckeckTypeOfHit(board & gameBoard, BULLET & bulletToCheck, char nextCharOnBoard, int xCoord, int yCoord);
	void incrementBulletStacks(BulletStuck & rivelStuck, bool incRival);
	BULLET * getBulletArr() {return bulletArr;}
	void DeleteBulletInStuckOfSnake(int x, int y, board& gameBoard);

};

#endif // !1
