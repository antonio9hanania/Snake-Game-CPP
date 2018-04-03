#ifndef _BULLET
#define _BULLET

#include "Point.h"
#include "Direction.h"
#include "board.h"

class BULLET {

	
	Point currentPoint;
	Point prevPoint;
	bool onScreen ;
	Direction dir;
	bool life = true;
	ColorOptions clrOfMyBullet;

public:

	Point getcurrentPoint() const {return currentPoint;}
	bool getOnScreen() const {return onScreen;}
	Direction getDir() const {return dir;}
	void setcurrentPoint(Point _p);
	void setOnScreen(bool _On) {onScreen = _On;}
	void setDir(Direction _dir) {dir = _dir;}
	void moveBullet(board & gameBoard, char currentSnakeChar);
	bool validMove(board & gameBoard, Point p);
	void updateCurrentPointToNext();
	void setLife(bool isLife) { life = isLife; }
	Point getPrevPoint() const { return prevPoint; }
	void setBulletColor(ColorOptions color){ clrOfMyBullet = color; }
	Point getPrevBullet() const{return prevPoint;}
	ColorOptions getClrOfMyBullet() const{ return clrOfMyBullet; }
	bool getLife() const { return life; }
};
#endif