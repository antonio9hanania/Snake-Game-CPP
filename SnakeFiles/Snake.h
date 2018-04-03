#ifndef _SNAKE_H_
#define _SNAKE_H_
#include "bulletStuck.h"
#include "Point.h"
#include "board.h"
#include "Direction.h"
#include "Color.h"

#define SNAKE_MAX_SIZE 15

class Snake {
	bool stuckL = false ,stuckR=false,  stuckU =false, stuckD=false ;
	
	Point body[SNAKE_MAX_SIZE];
	Direction direction;
	
	Point bodyFromStartintPos[SNAKE_MAX_SIZE];
	Direction straringDir;
	

	Point savingRebornsPos[50] = {};
	int rebornsLogSize = 0;
	int indexToTravelReborn = 0;
	//bool OnBug = false;
	bool stuckByReverse = false;
	//bool fixBugStuck = false;
	char c;
	bool legalMove = true;
	bool isRandom = true;
	char Keys[5]; // the keys for the four possible directions
	int score = 0;
	int SnakeLogSize =  3;
	bool Stuck;
	ColorOptions snakeColor;
	int xToGoToPrintStuckOfBullets, yToGoToPrintStuckOfBullets;
	BulletStuck snakeBulletStuck{Direction::DOWN};


public:
	void setLegalMove(bool isLegal) { legalMove = isLegal; }
	bool getLegalMove() { return legalMove; } // to remove
	void setStuckByReverse() { stuckByReverse = true; }
	void resetStuckByReverse() { stuckByReverse = false; }
	void resetRebornsLogSize() { rebornsLogSize = 0; }
	bool getStuckByReverse() { return stuckByReverse; }
	void setSnakeStuck(bool newPosision) { Stuck = newPosision; }
	bool getSnakeStuck() { return Stuck; }
	void snakeLogicSize(int num) {
	SnakeLogSize += num;
	score = SnakeLogSize - 3;
	}
	Snake(int SnakeLogSize, const Point& head, char c1, Direction dir = Direction::DOWN );
	void printSnake();
	void printHead();
	void setKeys(char keyLeft, char keyRight, char keyUp, char keyDown, char shoot);
	void changeDir(char keyPressed);
	void revDir(); 
	Direction revDir(Direction dir);
	bool isReverse(Direction dir);
	Point getHeadOfSnake() const{ return body[0]; }
	bool move(char keyPressed , board &gameBoard,int SnakeLogSize);
	char getSnakeChar() { return c; }
	int getBodyXcoordByIndex(int i) {return body[i].getXCoord();}
	int getBodyYcoordByIndex(int i) { return body[i].getYCoord(); }
	Point* getBody() { return body; }
	Direction getDirection() { return direction; }
	void setDir(Direction d1) { direction = d1; }
	bool isLegalCoords (int x,int y,board gameBoard) ; //snake communicate with board
	void updateStuckTypeDir();
	void initialStucks();
	void updateDirxDiry();
	void updateScore(int sc) {SnakeLogSize = score + 3; score = sc;}
	int getScore() {	return score;}
	int getSnakeLogSize(){return SnakeLogSize;	}
	BulletStuck& getAndUpdateSnakeBulletStuck() {	return snakeBulletStuck;}
	BulletStuck  getSnakeBulletStuck()const {	return snakeBulletStuck;}
	char getShootingKey() const {	return Keys[4];}
	ColorOptions getSnakeColor() const {return snakeColor;	}
	int getXToGoToPrintStuckOfBullets() const {return xToGoToPrintStuckOfBullets;}
	int getYToGoToPrintStuckOfBullets() const {	return yToGoToPrintStuckOfBullets;}
	void setNewHeadForSnake(Point& newHead);
	void setRebornPoints(const Point & reb);
	void saveSnakeStartingPos();
	void setBodyToStartPos();
	Point getRebornInRebArr() {
		indexToTravelReborn++;
		return savingRebornsPos[indexToTravelReborn - 1];
	}
	void resetResetIndexToTravelReborn() {indexToTravelReborn = 0;	}
	void DeleteBulletInStuckOfSnake(int x, int y, board& gameBoard);


};


#endif
