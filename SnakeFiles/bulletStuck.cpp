#include "bulletStuck.h"



BulletStuck::BulletStuck(Direction d, char ch)
{
	logic_size = PHISE_SIZE;
	bulletDir = d; //need to set it by parameter
	
	BulletChar = ch;

	for (size_t i = 0; i < PHISE_SIZE; i++)
	{
		bulletArr[i].setDir(d); //setting the direction of the bullet to snake's direction
		bulletArr[i].setOnScreen(false);
	}

}


TypeOfBulletHit BulletStuck::checkAndMoveIfPossible(char keyPressed, char shootingKey, Point headOfSnake, Direction dir, bool isSTUCKByPressingReverseKey, board & gameBoard, char currentSnakeChar, BulletStuck& rivalStuck, int dieCouner, int &numCounter)
{
	int counter = 0;
	TypeOfBulletHit typeHit = NOT_RELEVENT;
	TypeOfBulletHit haseAccured;
	bool wasHere1 = false, wasHere2 = false;
	if (dieCouner == 0) {

		if (keyPressed == shootingKey && logic_size > 0) {
			changeBulletDataMembers(headOfSnake, dir, isSTUCKByPressingReverseKey);
			logic_size--;
			printVisualStuck(xCoordToPrintStuck, yCoordToPrintStuck, logic_size, clrOfMyBullets);
			Beep(311, 100);
			Beep(277, 80);
		}
	}

	for (int i = PHISE_SIZE - 1; i >= 0; i--) // we must do it backward to move the it without runnig over other bullet
	{
		{
			if (bulletArr[i].getOnScreen() == true)
			{
				for (int j = 0; j < 2 && bulletArr[i].getOnScreen() == true; j++)
				{

					TypeOfBulletHit temp = moveBulletOperation(gameBoard, bulletArr[i], currentSnakeChar, rivalStuck, numCounter);


					if (temp == ON_MY_SNAKE)
						typeHit = ON_MY_SNAKE;

					if (temp == ON_OTHER_SNAKE)
						typeHit = ON_OTHER_SNAKE;


					if (temp == ON_MY_SNAKE && wasHere1 == false) {
						counter++;
						wasHere1 = true;
					}
					if (wasHere1 == true && temp == ON_OTHER_SNAKE)
						counter++;

					if (temp == ON_OTHER_SNAKE && wasHere2 == false) {
						counter++;
						wasHere2 = true;
					}
					if (wasHere2 == true && temp == ON_MY_SNAKE)
						counter++;
					if (temp == ON_LINE_FLAYER_PIN || temp == ON_LINE_PLAYER_NPIN)
					{
						return temp;
					}

				}
			}

		}
	}
	if (counter > 1)
		return ON_BOTH_SNAKES;
	else
		return typeHit;
}

void BulletStuck::printVisualStuck(int x, int y, int numOfUnits, ColorOptions clr)
{
	char a = 177, b = 219;
	gotoxy(x, y);

	for (size_t i = 0; i < 5; i++)
	{
		cout << " ";
	}


	cout << Color(clr) << "\t\t\t\t";
	gotoxy(x, y);
	for (int i = 0; i < 5; i++)
		cout << Color(clr) << a;
	cout << Color(clr) << "\r";
	cout << Color(clr) << "\t\t\t\t";
	gotoxy(x, y);

	for (int i = 0; i < numOfUnits; i++)
	{
		cout << Color(clr) << b;
		Sleep(50);
	}
}

void BulletStuck::setColorOfBulletsAndXCoordsToPrintStuck(ColorOptions clrOfSnake, int x, int y)
{
	if (clrOfSnake == RED)
		clrOfMyBullets = LIGHTRED;
	if (clrOfSnake == GREEN)
		clrOfMyBullets = LIGHTGREEN;
	xCoordToPrintStuck = x;
	yCoordToPrintStuck = y;

	for (size_t i = 0; i < PHISE_SIZE; i++)
	{
		bulletArr[i].setBulletColor(clrOfMyBullets);
	}
}


void BulletStuck::changeBulletDataMembers(Point head, Direction dir, bool isSTUCKByPressingReverseKey) {
	bool found = false;
	for (int i = PHISE_SIZE - 1; i >= 0 && found == false; i--)
	{
		if (bulletArr[i].getLife() == true && bulletArr[i].getOnScreen() == false) {

			bulletArr[i].setOnScreen(true);

			if (isSTUCKByPressingReverseKey)
			{
				switch (dir) {
				case(DOWN):dir = UP;
					break;
				case(UP):dir = DOWN;
					break;
				case(LEFT):dir = RIGHT;
					break;
				case(RIGHT):dir = LEFT;
					break;

				}
			}
			bulletArr[i].setDir(dir);
			bulletArr[i].setcurrentPoint(head);
			found = true;
		}
	}
}

void BulletStuck::initialBulletStackAndRemoveBullets(Point head, Direction dir, board & gameBoard) {
	removeBulletsOnScreenAndBoard(gameBoard);
	logic_size = 5;
	for (size_t i = 0; i < PHISE_SIZE; i++)
	{
		bulletArr[i].setDir(dir);
		bulletArr[i].setcurrentPoint(head);
		bulletArr[i].setOnScreen(false);
		bulletArr[i].setLife(true);
	}
}


void BulletStuck::removeBulletsOnScreenAndBoard(board& gameBoard) {
	for (size_t i = 0; i < PHISE_SIZE; i++)
	{
		if (bulletArr[i].getOnScreen() == true) {
			gameBoard.deleShootCharFromBoardAndScreen(bulletArr[i].getPrevPoint());
		}
	}

}



TypeOfBulletHit BulletStuck::moveBulletOperation(board& gameBoard, BULLET & bulletTomove, char currentSnakeChar, BulletStuck& rivalStuck, int & numCounter) {

	int xCoord = (bulletTomove.getPrevPoint().getXCoord() + bulletTomove.getPrevPoint().getDir_x() + ROWS) % ROWS;
	int yCoord = (bulletTomove.getPrevPoint().getYCoord() + bulletTomove.getPrevPoint().getDir_y() + LINES) % LINES;
	char nextCharOnBoard = gameBoard.charByCoordinate(xCoord, yCoord);


	if (nextCharOnBoard == ' ') {
		bulletTomove.moveBullet(gameBoard, currentSnakeChar);
		return ON_SPACE;
	}
	else
	{
		TypeOfBulletHit hitType = ckeckTypeOfHit(gameBoard, bulletTomove, nextCharOnBoard, xCoord, yCoord);
		int xCoordOfCurrentPoint = bulletTomove.getcurrentPoint().getXCoord();
		int yCoordOfCurrentPoint = bulletTomove.getcurrentPoint().getYCoord();
		bulletTomove.setLife(false);
		bulletTomove.setOnScreen(false);


		switch (hitType) {

		case(ON_OTHER_BULLET):
			//both bullets need remove from board and screen
			//both stacks need to increment

			gameBoard.deleShootCharFromBoardAndScreen(bulletTomove.getPrevBullet());

			for (int i = 0; i < PHISE_SIZE; i++)
			{
				if (rivalStuck.bulletArr[i].getPrevPoint().getXCoord() == xCoordOfCurrentPoint && rivalStuck.bulletArr[i].getPrevPoint().getYCoord() == yCoordOfCurrentPoint) {
					gameBoard.deleShootCharFromBoardAndScreen(rivalStuck.bulletArr[i].getPrevPoint());
					rivalStuck.bulletArr[i].setOnScreen(false);
					rivalStuck.bulletArr[i].setLife(false);
				}
			}
			incrementBulletStacks(rivalStuck, true);
			printVisualStuck(xCoordToPrintStuck, yCoordToPrintStuck,logic_size ,clrOfMyBullets);
			printVisualStuck(rivalStuck.xCoordToPrintStuck, rivalStuck.yCoordToPrintStuck,rivalStuck.logic_size ,rivalStuck.clrOfMyBullets); 

			break;
		case(ON_MY_BULLET):
			//both bullets need remove from board and screen

			gameBoard.deleShootCharFromBoardAndScreen(bulletTomove.getPrevBullet());

			for (int i = 0; i < PHISE_SIZE; i++)
			{
				if (bulletArr[i].getPrevPoint().getXCoord() == xCoordOfCurrentPoint &&  bulletArr[i].getPrevPoint().getYCoord() == yCoordOfCurrentPoint) // equal to my next position so the crossing each other
				{
					gameBoard.deleShootCharFromBoardAndScreen(bulletArr[i].getPrevPoint());
					bulletArr[i].setOnScreen(false);
					bulletArr[i].setLife(false);
				}
			}
			break;
		case(ON_MY_SNAKE):
			//remove from board and screen
			//will remove from board and screen for 5 steps and reborne in a random point 
			gameBoard.deleShootCharFromBoardAndScreen(bulletTomove.getPrevBullet());

			 
			break;
		case(ON_OTHER_SNAKE): 
			//remove from board and screen
			//other snake need to be removed from the game for 5 steps and born in new point
			//increment my bullet stack 

			gameBoard.deleShootCharFromBoardAndScreen(bulletTomove.getPrevBullet());

			incrementBulletStacks(rivalStuck, false);
			printVisualStuck(xCoordToPrintStuck, yCoordToPrintStuck, logic_size, clrOfMyBullets); // just my bullet stack will update

			break;
		case(ON_NUM):
			//delete from dataArr
			//delete from board
			gameBoard.getTheMSDigitCoordinate(&xCoordOfCurrentPoint, &yCoordOfCurrentPoint);
			gameBoard.setDeleteX(xCoordOfCurrentPoint);
			gameBoard.setDeleteY(yCoordOfCurrentPoint);
			gameBoard.deleteNumFromData();
			gameBoard.deleShootCharFromBoardAndScreen(bulletTomove.getPrevBullet());
			numCounter--;
			break;

		case(ON_ROW_FLAYER):
			//gameBoard.deleShootCharFromBoardAndScreen(bulletTomove.getPrevBullet());
			bulletTomove.setLife(false);
			bulletTomove.setOnScreen(false);
			gameBoard.deleShootCharFromBoardAndScreen(bulletTomove.getPrevBullet());
			break;
		case(ON_LINE_FLAYER_PIN):
			bulletTomove.setLife(false);
			bulletTomove.setOnScreen(false);
			gameBoard.deleShootCharFromBoardAndScreen(bulletTomove.getPrevBullet());
			//gameBoard.printBoard();
			break;
		case(ON_LINE_PLAYER_NPIN):
			bulletTomove.setLife(false);
			bulletTomove.setOnScreen(false);
			gameBoard.deleShootCharFromBoardAndScreen(bulletTomove.getPrevBullet());
			break;
			//gameBoard.printBoard();
		case(ON_NUM_EATER):
			{
			bulletTomove.setLife(false);
			bulletTomove.setOnScreen(false);
			gameBoard.deleShootCharFromBoardAndScreen(bulletTomove.getPrevBullet());
			break;
			}
		}


		
		return hitType;
	}

}


TypeOfBulletHit BulletStuck::ckeckTypeOfHit(board & gameBoard, BULLET & bulletToCheck, char nextCharOnBoard, int xCoord, int yCoord) {


	if (nextCharOnBoard >= '0' && nextCharOnBoard <= '9')
		return ON_NUM;
	else if (nextCharOnBoard == '!')
		return ON_ROW_FLAYER;
	else if (nextCharOnBoard == '%')
		return ON_NUM_EATER;
	else if (nextCharOnBoard == '@')
	{
		if (xCoord == 45)
			return ON_LINE_FLAYER_PIN;
		else //xCoord==55
			return ON_LINE_PLAYER_NPIN;
	}
	else if (nextCharOnBoard == '*') { /// we need to check all the points of my stack if its my bullet or other one .
		for (size_t i = 0; i < PHISE_SIZE; i++)
		{
			if (bulletArr[i].getPrevPoint().getXCoord() == xCoord && bulletArr[i].getPrevPoint().getYCoord() == yCoord)
				return ON_MY_BULLET;
		}

		return ON_OTHER_BULLET; //need to check if it is my same type of bullet
	}
	else if ((nextCharOnBoard == '#' && bulletToCheck.getClrOfMyBullet() == LIGHTRED) || nextCharOnBoard == '$' && (bulletToCheck.getClrOfMyBullet() == LIGHTGREEN))
		return ON_MY_SNAKE;
	else
		return ON_OTHER_SNAKE;
}


void BulletStuck::incrementBulletStacks(BulletStuck & rivelStuck, bool incRival) {
	bool found = false;

	if (incRival) {
		for (int i = PHISE_SIZE - 1; i >= 0 && found == false; i--)
		{
			if (rivelStuck.bulletArr[i].getLife() == false && rivelStuck.bulletArr[i].getOnScreen() == false) {
				rivelStuck.bulletArr[i].setLife(true);
				rivelStuck.logic_size++;
				found = true;
			}
		}
	}
	found = false;
	for (int i = PHISE_SIZE - 1; i >= 0 && found == false; i--) {
		if (this->bulletArr[i].getLife() == false && this->bulletArr[i].getOnScreen() == false) {
			this->bulletArr[i].setLife(true);
			this->logic_size++;
			found = true;
		}
	}
}



void BulletStuck::DeleteBulletInStuckOfSnake(int x, int y, board& gameBoard) {



	for (int i = 0; i < PHISE_SIZE; i++)
	{



		if (x == bulletArr[i].getPrevPoint().getXCoord() && y == bulletArr[i].getPrevPoint().getYCoord())
		{

			bulletArr[i].setLife(false);
			bulletArr[i].setOnScreen(false);

			gameBoard.deleShootCharFromBoardAndScreen(bulletArr[i].getPrevBullet());

		}
	}

}