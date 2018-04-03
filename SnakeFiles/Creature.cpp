#include "Creature.h"


void Creature:: updateCreatureLocationInBoardAndScreen(board& gameBoard)
{
	int x, y;
	//update creature Location in Board
	setTextColor(WHITE);
	x = BeginningPoint.getXCoord();
	y = BeginningPoint.getYCoord();
	
	gameBoard.updateCreatureInBoard(x,y-4, Symbol);

	//update Creature Location in screen

}

void  Creature::deleteCretureFromBoardAndScreen(board& gameBoard)
{
	int x, y;
	//update creature Location in Board

	x = BeginningPoint.getXCoord();
	y = BeginningPoint.getYCoord();

	gameBoard.updateCreatureInBoard(x, y-4, ' ' );
//	gameBoard.printBoard();
}
