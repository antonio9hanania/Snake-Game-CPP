#ifndef  _CREATURE
#define _CREATURE
#include "Color.h"
#include "Point.h"
#include "Direction.h"
#include "board.h"
#include "Snake.h"
#include "Mission.h"

enum FlyHit { RowFlyHitSulamin, RowFlyEatDollar, DontCare,LineFlyerEatSulamit,LineFlyersEatDollar };

class Creature {
	bool OnScreen;
	char Symbol;
	Point BeginningPoint;
	ColorOptions cl;
	Direction d_creature;
	bool isPinball;
public:
	Creature(bool _OnScreen, char _Symbol, Point _BeginningPoint, Direction _d_creature, bool _isPinball)
	{
		OnScreen = _OnScreen;
		Symbol = _Symbol;
		BeginningPoint.set(_BeginningPoint.getXCoord(), _BeginningPoint.getYCoord());
		BeginningPoint.changeDir(_d_creature);
		isPinball = _isPinball;
	}
	bool getOnScreen(){ return OnScreen; }
	void setOnScreen(bool b) { OnScreen = b; }
	Direction getD_creature() { return d_creature; }
	bool getIsPinball(){ return isPinball;}
	Point&  getBeginningPoint() { return BeginningPoint; }

	void setBegginingPoint(Point* p) { 
		BeginningPoint.set(p->getXCoord(), p->getYCoord());
		BeginningPoint.setDir_X(p->getDir_x());
		BeginningPoint.setDir_Y(p->getDir_y());

	 }
	virtual FlyHit move(board& gameBoard,Snake* p, Mission& mish) = 0;
	void updateCreatureLocationInBoardAndScreen(board& gameBoard);
	void deleteCretureFromBoardAndScreen(board& gameBoard);
	void setD_creature(Direction d){d_creature =d;}
	virtual void initialFlyerToBeginning (board& gameBoard) =0;

};

#endif // ! _CREATURE
