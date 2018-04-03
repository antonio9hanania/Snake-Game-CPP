#include "Bullet.h"




void BULLET::moveBullet(board & gameBoard, char currentSnakeChar) {
	ColorOptions clr = WHITE;

	if (currentSnakeChar == '#') clr = LIGHTRED;
	if (currentSnakeChar == '$') clr = LIGHTGREEN;

	gameBoard.deleShootCharFromBoardAndScreen(prevPoint);

	currentPoint.draw('*', clr);

	gameBoard.updateBulletInBoard(currentPoint.getXCoord(), currentPoint.getYCoord());
	
	updateCurrentPointToNext();

}


void BULLET::setcurrentPoint(Point _p) {
	prevPoint = _p;
	prevPoint.changeDirWithoutTermsOfStuckSituation(dir);
	currentPoint = prevPoint;
	currentPoint.set(((_p.getXCoord() + prevPoint.getDir_x() + ROWS) % ROWS), ((_p.getYCoord() + prevPoint.getDir_y() + LINES) % LINES));
}


bool BULLET:: validMove(board & gameBoard, Point p)
{
	int x = (currentPoint.getXCoord() + currentPoint.getDir_x()) % ROWS;
	int y = (currentPoint.getYCoord() + currentPoint.getDir_y()) % LINES;
	if (gameBoard.charByCoordinate(x, y) == ' ')
		return true;
	else
		return false;
}


void BULLET:: updateCurrentPointToNext() {
	int xCoord = (currentPoint.getXCoord() + currentPoint.getDir_x() + ROWS) % ROWS;
	int yCoord = (currentPoint.getYCoord() + currentPoint.getDir_y() + LINES) % LINES;

	prevPoint = currentPoint;
	currentPoint.set(xCoord, yCoord); //with the same dir becouse of equal
}