#include "Snake.h"
#include "board.h"
#include "SnakesGame.h"


Snake::Snake(int snakeLogSize,const Point& head, char c1, Direction dir) {
	c = c1;
	direction = dir;
	body[0] = head;
	body[0].draw(c);
	bodyFromStartintPos[0] = body[0];
	for (int i = 1; i < snakeLogSize; ++i) {
		body[i] = body[i - 1];
		bodyFromStartintPos[i] = body[i];
		body[i].move();
		bodyFromStartintPos[i]=body[i];
		body[i].draw(c);
	}
	straringDir = direction;
	if (c == '#') {
		snakeColor = RED;
		xToGoToPrintStuckOfBullets = 0; yToGoToPrintStuckOfBullets = 1;
	}
	if (c1 == '$') {
		snakeColor = GREEN;
		xToGoToPrintStuckOfBullets = 75; yToGoToPrintStuckOfBullets = 1;
	}


}

void Snake::printSnake() {

		for (int i = 0; i < SnakeLogSize; ++i) {
			body[i].draw(c);
		}

}
void Snake::printHead() {
	body[0].draw(c);
}

void Snake::setKeys(char keyLeft, char keyRight, char keyUp, char keyDown, char shoot) {
	Keys[Direction::LEFT] = keyLeft;
	Keys[Direction::RIGHT] = keyRight;
	Keys[Direction::UP] = keyUp;
	Keys[Direction::DOWN] = keyDown;
	Keys[4] = shoot;

	isRandom = false;
}
void Snake::changeDir(char keyPressed) {
	if (stuckByReverse)
	{
		stuckByReverse = false;
		legalMove = true;
		revDir();
	}
	else {
		for (size_t i = 0; i < 4; i++)
		{
			const auto& key = Keys[i];
			if (key == keyPressed) {
				if (isReverse((Direction)(i))) {
					stuckByReverse = true;
					legalMove = true;

				}
				else
					direction = (Direction)(i);
			}
		}
	}
}
	

void Snake::revDir() {
	switch (direction) {
	case(DOWN):direction = UP;
		break;
	case(UP):direction = DOWN;
		break;
	case(LEFT):direction = RIGHT;
		break;
	case(RIGHT):direction = LEFT;
		break;
	}
}

Direction Snake::revDir(Direction dir) {
	switch (dir) {
	case(DOWN):return UP;
	case(UP):return DOWN;
	case(LEFT):return RIGHT;
	case(RIGHT):return  LEFT;
	}
}

bool Snake::isReverse(Direction dir) {
	Direction rev = revDir(dir);
	if (rev == direction)
		return true;
	else
		return false;
}

bool Snake::move(char keyPressed, board& gameBoard, int SnakeLogSize) { // ���� �� keypressed ��� �� �� ���� �� ���� !!

	//gotoxy(0, 2);
	//cout << keyPressed;
	
	if (legalMove !=false)
	{
		body[SnakeLogSize].draw(' ');

		for (int i = SnakeLogSize ; i > 0; --i) {
			body[i] = body[i - 1];
		}
		body[0].draw(c);
		

		
	}
	if (isRandom) {
		body[0].move();
	}
	else {
		changeDir(keyPressed);
		updateDirxDiry();
		legalMove = isLegalCoords(body[0].getXCoord(), body[0].getYCoord(), gameBoard);
		if (legalMove == false){
			
			int numCoordX= body[0].getXCoord() + body[0].getDir_x();
	
					
			int numCoordY= body[0].getYCoord() + body[0].getDir_y();
			if (numCoordY == -1)
				numCoordY = LINES-1;
			if (numCoordY == LINES)
				numCoordY = 0;
		
			char RelevantChar = gameBoard.charByCoordinate(numCoordX, numCoordY);
			if (RelevantChar>='0'&&RelevantChar<='9')
			{
				gameBoard.getTheMSDigitCoordinate(&numCoordX,&numCoordY);
				gameBoard.setDeleteX(numCoordX);
				gameBoard.setDeleteY(numCoordY);
				body[0].move(direction, stuckR, stuckL, stuckU, stuckD);
				return true;

			}
			
			updateStuckTypeDir();
			setSnakeStuck(TRUE);
			}

	}
	body[0].move(direction, stuckR, stuckL, stuckU, stuckD);
	//printSnake(10);

	initialStucks();

	return false;


}



bool Snake::isLegalCoords(int x, int y, board gameBoard)
//snake communicate with board
{
	if (gameBoard.charByCoordinate((x + body[0].getDir_x() + 80) % 80, (y + body[0].getDir_y()+LINES)%LINES) == ' ')
	{
		return true;
	}
	
	else 

	
	{
		return false;
	}
}


void Snake::updateStuckTypeDir()
{
	switch (direction)
	{
	case (RIGHT):
	{
		stuckR = true;
		break;
	}
	case (LEFT):
	{
		stuckL = true;
		break;
	}
	case (UP):
	{
		stuckU = true;
		break;
	}
	case (DOWN):
	{
		stuckD = true;
		break;
	}
	default: break;
	}
}

void Snake::initialStucks()
{
	stuckD = stuckL = stuckR = stuckU = false;
}

void Snake::updateDirxDiry()
{
	switch (direction)
	{
	case UP:
		body[0].setDir_X(0);
		body[0].setDir_Y(-1);
		break;
	case DOWN:
		body[0].setDir_X(0);
		body[0].setDir_Y(1);
		break;
	case RIGHT:
		body[0].setDir_X(1);
		body[0].setDir_Y(0);
		break;
	case LEFT:
		body[0].setDir_X(-1);
		body[0].setDir_Y(0);
		break;
	default: break;
	}
}

void Snake::setNewHeadForSnake(Point& newHead)
{
	for (int i = 0;i <SnakeLogSize ;i++)
	{
		body[i] = newHead;
	}
}




void Snake::setRebornPoints(const Point & reb)
{
	savingRebornsPos[rebornsLogSize].set(reb.getXCoord(), reb.getYCoord());
	rebornsLogSize++;
}

void Snake::saveSnakeStartingPos() {
	 
	for (size_t i = 0; i < SNAKE_MAX_SIZE; i++)
	{
		bodyFromStartintPos[i] = body[i];
	}
	straringDir = direction;
}
void Snake::setBodyToStartPos() {

	for (size_t i = 0; i < SNAKE_MAX_SIZE; i++)
	{
		body[i] = bodyFromStartintPos[i];
	}
	direction = straringDir;
}



void Snake::DeleteBulletInStuckOfSnake(int x, int y, board& gameBoard)
{
	snakeBulletStuck.DeleteBulletInStuckOfSnake(x, y, gameBoard);

}