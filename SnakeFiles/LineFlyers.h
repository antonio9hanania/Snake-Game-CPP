#ifndef _LINE_FLYERS
#define _LINE_FLYERS
#include "Creature.h"

class LineFlyers : public Creature {
	Point StartPoint;
public:

	LineFlyers(bool _OnScreen, char _Symbol, Point _BeginningPoint, Direction _d_creature, bool _isPinball) : Creature(_OnScreen, _Symbol, _BeginningPoint, _d_creature, _isPinball)
	{
		StartPoint.set(_BeginningPoint.getXCoord(), _BeginningPoint.getYCoord());
		if (_d_creature == UP)
			StartPoint.setDir_Y(-1);
		if (_d_creature == DOWN)
			StartPoint.setDir_Y(1);
	
	}
	FlyHit eatingSomething(board& gameBoard, char eaten, Snake* p, int x, int y);
	FlyHit  move(board& gameBoard, Snake* p, Mission& mish);
	void LineFlayerEatBullet(board& gameBoard, Snake* p, int x, int y);
	//void UpdateRowFlyer1Location(board *gameBoard);
	void initialFlyerToBeginning(board& gameBoard);


};



#endif _LINE_FLYERS