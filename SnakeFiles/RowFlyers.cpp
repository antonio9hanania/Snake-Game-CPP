#include "RowFlyers.h"


FlyHit RowFlyer1::move(board& gameBoard, Snake* p, Mission& mish)
{
	// flag==1 the Flyer moves as same as Snake 
	// flag==0 the Flyer moves as a pinball
	char eaten;
	Point temp = getBeginningPoint();
	int x = temp.getXCoord();
	int y = temp.getYCoord();
	if (getIsPinball() == false)
	{
		int k = x;
		x = (x + temp.getDir_x() + ROWS) % ROWS; // y= 23
		eaten = gameBoard.charByCoordinate(x, y - 4);
		if (eaten != ' '&&eaten != '\0')
		{
			FlyHit HitOnSnake = eatingSomething(gameBoard, eaten, p, x, y - 4);
			return HitOnSnake;
		}
		temp.set(x, y);
		setBegginingPoint(&temp);
	}
	else	//Flyer moves as pinbal
	{

		if (x == ROWS - 1 && temp.getDir_x() == 1)	         //End of Screen and Board -the right side
		{
			temp.changeDirWithoutTermsOfStuckSituation(LEFT);    //change the direction of the point
			setD_creature(LEFT);
		}

		else if (x == 0 && temp.getDir_x() == -1)
		{
			temp.changeDirWithoutTermsOfStuckSituation(RIGHT);		//at the beggining og the screen/Board
			setD_creature(RIGHT);
		}
		else
		{
			x = (x + temp.getDir_x() + ROWS) % ROWS;	// somewhere at the middle of the screen/Board
			eaten = gameBoard.charByCoordinate(x, y - 4);
			if (eaten != ' '&&eaten != '\0')
			{
				FlyHit HitOnSnake = eatingSomething(gameBoard, eaten, p, x, y - 4);
				return HitOnSnake;
			}
			temp.set(x, y);
		}
		setBegginingPoint(&temp);
	}
	return DontCare;

}
	FlyHit RowFlyer1::eatingSomething(board& gameBoard, char eaten, Snake* p, int x, int y)
	{
		if (eaten >= '0'&&eaten <= '9')
		{
			gameBoard.getTheMSDigitCoordinate(&x, &y);
			gameBoard.setDeleteY(y);
			gameBoard.setDeleteX(x);
			gameBoard.deleteNumFromData();
			return DontCare;
		}
		else if (eaten == '#')
		{
			return RowFlyHitSulamin;
		}
		else if (eaten == '$')
		{
			return RowFlyEatDollar;
		}
		else if (eaten == '*')
		{
			rowFlayerEatBullet(gameBoard, p, x, y);
			return DontCare;
		}
	}

	void RowFlyer1::rowFlayerEatBullet(board& gameBoard, Snake* p, int x, int y)
	{



		for (int i = 0; i < 2; i++)
		{
			p[i].DeleteBulletInStuckOfSnake(x, y,gameBoard);
			gameBoard.writeOnScreenBoardByCoordinate(x, y - 4, ' ');
		}
	}

void RowFlyer1:: initialFlyerToBeginning(board& gameBoard)
{
	deleteCretureFromBoardAndScreen( gameBoard);
	setBegginingPoint(&StartPoint);
}
