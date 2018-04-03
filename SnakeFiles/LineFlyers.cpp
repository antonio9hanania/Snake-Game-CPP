#include "LineFlyers.h"


FlyHit LineFlyers::move(board& gameBoard, Snake* p, Mission& mish)
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
		y -= 4;
		y = (y + temp.getDir_y() + LINES) % LINES; // y= 23

		eaten = gameBoard.charByCoordinate(x, y );
		
		if (eaten != ' '&&eaten != '\0')
		{
			FlyHit HitOnSnake = eatingSomething(gameBoard, eaten, p, x, y );
			return HitOnSnake;
		}
		y += 4;
		temp.set(x, y);
		setBegginingPoint(&temp);
	}
	else	//Flyer moves as pinbal
	{
		y -= 4;
		if (y == 19 && temp.getDir_y() == 1)	         //End of Screen and Board -the right side
		{
			
			temp.changeDirWithoutTermsOfStuckSituation(UP);    //change the direction of the point
			setD_creature(UP);
		}

		else if (y == 0 && temp.getDir_y() == -1)
		{
			
			temp.changeDirWithoutTermsOfStuckSituation(DOWN);		//at the beggining og the screen/Board
			setD_creature(DOWN);
		}
		else
		{
			y = (y + temp.getDir_y() + LINES) % LINES;	// somewhere at the middle of the screen/Board
			eaten = gameBoard.charByCoordinate(x, y);
			if (eaten != ' '&&eaten != '\0')
			{
				FlyHit HitOnSnake = eatingSomething(gameBoard, eaten, p, x, y );
				return HitOnSnake;
			}
			if (eaten == '*')
				cout << "in";
			y += 4;
			temp.set(x, y);
		}
		setBegginingPoint(&temp);
	}
	return DontCare;

}
FlyHit LineFlyers::eatingSomething(board& gameBoard, char eaten, Snake* p, int x, int y)
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
		return LineFlyerEatSulamit;
	}//LineFlyerEatSulamit,LineFlyersEatDollar 
	else if (eaten == '$')
	{
		return LineFlyersEatDollar;
	}
	else if (eaten == '*')
	{
		//gameBoard.printBoard();
		LineFlayerEatBullet(gameBoard, p, x, y);
		//gameBoard.printBoard();
		return DontCare;
	}
}

void LineFlyers::LineFlayerEatBullet(board& gameBoard, Snake* p, int x, int y)
{


	setOnScreen(false);
	deleteCretureFromBoardAndScreen(gameBoard);
	gameBoard.deleShootCharFromBoardAndScreen(x, y);
	for (int i = 0; i < 2; i++)
	{
		p[i].DeleteBulletInStuckOfSnake(x, y, gameBoard);
		gameBoard.writeOnScreenBoardByCoordinate(x, y, ' ');
	}
}

void LineFlyers::initialFlyerToBeginning(board& gameBoard)
{
	deleteCretureFromBoardAndScreen(gameBoard);
	setBegginingPoint(&StartPoint);
	setOnScreen(true);
}
