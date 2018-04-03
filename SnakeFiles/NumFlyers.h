#ifndef _NUM_FLYERS
#define _NUM_FLYERS
#include "Creature.h"
#include "board.h"
#include "GeneralFunc.h"

class NumFlyers : public Creature {
	double min_distance=80;
	Point Pnow/*={10,19-4}*/;
	Point Pnearest;
	Point Pcheck;
	Point StartPoint = {10,19};
	
public:
	NumFlyers(bool _OnScreen, char _Symbol, Point _BeginningPoint, Direction _d_creature, bool _isPinball) : Creature(_OnScreen, _Symbol, _BeginningPoint, _d_creature, _isPinball) {
		Pnow.set(_BeginningPoint.getXCoord(), _BeginningPoint.getYCoord());
		StartPoint.set(_BeginningPoint.getXCoord(), _BeginningPoint.getYCoord());
	}
	FlyHit move(board& gameBoard, Snake* p, Mission& mish);
	void NumFlyers::findTheNearestSolutionNumberXYCoordinates(board& gameBoard,Mission& mish);
	void initialFlyerToBeginning(board& gameBoard);
	void NumFlyers::goToPNearest(board& gameBoard);
	void NumFlyers::findNextPositionByNearestAndMove(board& gameBoard);
	void NumFlyers::HandleWithNotSpace(board& gameBoard, int x, int y);
	void NumFlyers::updateNumEatersLocationInBoardAndScreen(board& gameBoard);
};



#endif _NUM_FLYERS