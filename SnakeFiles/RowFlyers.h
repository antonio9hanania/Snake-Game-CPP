#ifndef  _ROW_FLYERS
#define _ROW_FLYERS
#include "Creature.h"
#include "board.h"



class RowFlyer1 : public Creature {
	Point StartPoint;
public :

	RowFlyer1(bool _OnScreen, char _Symbol, Point _BeginningPoint, Direction _d_creature,bool _isPinball) : Creature(_OnScreen, _Symbol, _BeginningPoint, _d_creature,_isPinball) 
	{
		StartPoint.set(_BeginningPoint.getXCoord(),_BeginningPoint.getYCoord());
	}
	FlyHit eatingSomething(board& gameBoard,char eaten, Snake* p,int x,int y);
	FlyHit  move(board& gameBoard,Snake* p,Mission& mish);
	void rowFlayerEatBullet(board& gameBoard, Snake* p, int x, int y);
	//void UpdateRowFlyer1Location(board *gameBoard);
	void initialFlyerToBeginning(board& gameBoard) ;

	
};




#endif // ! _ROW_FLYERS
