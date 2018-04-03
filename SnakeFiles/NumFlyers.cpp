#include "NumFlyers.h"

FlyHit NumFlyers::move(board& gameBoard, Snake* p, Mission& mish)
{
	//gotoxy(0, 54);
	//cout << " %.x   =   " << getBeginningPoint().getXCoord();
//	cout << " %.y   =   " << getBeginningPoint().getYCoord();


		findTheNearestSolutionNumberXYCoordinates(gameBoard, mish);
		if (Pnearest.getXCoord() == Pnow.getXCoord() && Pnearest.getYCoord() == Pnow.getYCoord()-4)
		{
			int x = Pnow.getXCoord();
			int y = Pnow.getYCoord()-4;
			gameBoard.getTheMSDigitCoordinate(&x, &y);
			gameBoard.setDeleteY(y);
			gameBoard.setDeleteX(x);
			gameBoard.deleteNumFromData();
			return DontCare;
		}
		else
		{
			goToPNearest(gameBoard);
			//gameBoard.printBoard();
			//gotoxy(0, 51);
			//cout << endl << "min_distance is : " << min_distance;
		}
		

	return DontCare; //temporary
}


void NumFlyers::goToPNearest(board & gameBoard)
{
	//gotoxy(0, 51);
	//cout << endl << "min_distance is : " << min_distance;
	if (min_distance != 80)
		findNextPositionByNearestAndMove(gameBoard);


}

void NumFlyers::findNextPositionByNearestAndMove(board& gameBoard)
{
	bool stop = false;
	int tempDist;
	Point Left, Right, Up, Down;
	if (Pnow.getYCoord() >= 20)
	{
		//cout << "dsafsd";
	}
	if (getBeginningPoint().getYCoord() > 24)
	{
		//cout << "ERROR";
	}
	if (((Pnow.getYCoord() - 1 + LINES) % LINES) == 0 || ((Pnow.getYCoord() - 1 + LINES) % LINES) == 19)
	{
		//gotoxy(0, 52);
		//cout << "MOVINGUP";
	}
	//Points on Board
	Left.set((Pnow.getXCoord() - 1+ROWS)%ROWS,( Pnow.getYCoord() -4+ 0+LINES)%LINES);
	Right.set((Pnow.getXCoord() + 1+ROWS)%ROWS, (Pnow.getYCoord() -4+ 0+LINES)%LINES);
	Up.set((Pnow.getXCoord() + 0+ROWS)%ROWS, (Pnow.getYCoord() - 4-1 +LINES)%LINES);
	Down.set((Pnow.getXCoord() + 0+ROWS)%ROWS, (Pnow.getYCoord()-4 +1+LINES)%LINES);
	

	//////all of Those points are of board
	///////////////////////////////{
	int L = DistanceTwoPoints(&Left, &Pnearest,true);
	int R  = DistanceTwoPoints(&Right, &Pnearest, true);
	int U = DistanceTwoPoints(&Up, &Pnearest,true);
	int D = DistanceTwoPoints(&Down, &Pnearest,true);
	/////////////////////////////////////}

	int res=min(min(L, R), min(U, D));
	
	if (res == L)
	{
		if (gameBoard.charByCoordinate(Left.getXCoord(), Left.getYCoord() ) == ' ')
		{
		
			Pnow.set(Left.getXCoord(), Left.getYCoord() + 4);

			Point temp;
			temp.set(Left.getXCoord(), (Left.getYCoord() + 4) % 25);
			setBegginingPoint(&temp);

			//Update Now
								//min_distance = DistanceTwoPoints(&Left, &Pnearest);
			if (getBeginningPoint().getXCoord() == Pnow.getXCoord() && getBeginningPoint().getYCoord() == Pnow.getYCoord())
			{
				//the case that the num eater is stuck though he has some unswer to eat!!
				//need to check why is he stuck?!
			
				updateNumEatersLocationInBoardAndScreen(gameBoard);

			}
			
			updateNumEatersLocationInBoardAndScreen(gameBoard);
			stop = true;

		}
		else
			HandleWithNotSpace(gameBoard, Left.getXCoord(), Left.getYCoord() );
	}
	else if (res == R)
	{
		if (gameBoard.charByCoordinate(Right.getXCoord(), Right.getYCoord() ) == ' ')
		{
	
			//min_distance = DistanceTwoPoints(&Right, &Pnearest);
			Pnow.set(Right.getXCoord(), Right.getYCoord() + 4);

			Point temp;
			temp.set(Right.getXCoord(), (Right.getYCoord() + 4) % 25);
			setBegginingPoint(&temp);
			//Update Now
			if (getBeginningPoint().getXCoord() == Pnow.getXCoord() && getBeginningPoint().getYCoord() == Pnow.getYCoord())
			{
				//the case that the num eater is stuck though he has some unswer to eat!!
				//need to check why is he stuck?!
				
				updateNumEatersLocationInBoardAndScreen(gameBoard);

			}
			 //update BeginningPoint
			updateNumEatersLocationInBoardAndScreen(gameBoard);
			stop = true;

		}
		else
			HandleWithNotSpace(gameBoard, Right.getXCoord(), Right.getYCoord() );
	}
	else if (res == U)
	{
		if (gameBoard.charByCoordinate(Up.getXCoord(), Up.getYCoord() ) == ' ')
		{
	
			//min_distance = DistanceTwoPoints(&Up, &Pnearest);
			Pnow.set(Up.getXCoord(), Up.getYCoord() + 4);
			Point temp;
			temp.set(Up.getXCoord(), (Up.getYCoord() + 4) % 25);
			setBegginingPoint(&temp);
			//Update Now
			if (getBeginningPoint().getXCoord() == Pnow.getXCoord() && getBeginningPoint().getYCoord() == Pnow.getYCoord())
			{
				
				//the case that the num eater is stuck though he has some unswer to eat!!
				//need to check why is he stuck?!
				
				updateNumEatersLocationInBoardAndScreen(gameBoard);
				
			}
			 //update BeginningPoint
			updateNumEatersLocationInBoardAndScreen(gameBoard);
			stop = true;


		}
		else
			HandleWithNotSpace(gameBoard, Up.getXCoord(), Up.getYCoord() );
	}
	else if (res == D)
	{
		if (gameBoard.charByCoordinate(Down.getXCoord(), Down.getYCoord() ) == ' ')
		{
		
			//min_distance = DistanceTwoPoints(&Down, &Pnearest);
			Pnow.set(Down.getXCoord(), Down.getYCoord() + 4);
			Point temp;
			temp.set(Down.getXCoord(), (Down.getYCoord() + 4) % 25);
			setBegginingPoint(&temp);
			//Update Now
			if (getBeginningPoint().getXCoord() == Pnow.getXCoord() && getBeginningPoint().getYCoord() == Pnow.getYCoord())
			{
				//the case that the num eater is stuck though he has some unswer to eat!!
				//need to check why is he stuck?!
			
				updateNumEatersLocationInBoardAndScreen(gameBoard);

			}
			//update BeginningPoint
			updateNumEatersLocationInBoardAndScreen(gameBoard);
			stop = true;

		}
		else
			HandleWithNotSpace(gameBoard, Down.getXCoord(), Down.getYCoord() );
	}
	else
		;
	/*
	if (DistanceTwoPoints(&Left, &Pnearest) <= min_distance&&!stop)
	{
		if (gameBoard.charByCoordinate(Left.getXCoord(), Left.getYCoord() - 4) == ' ')
		{

			Pnow = Left;		//Update Now
			//min_distance = DistanceTwoPoints(&Left, &Pnearest);
			setBegginingPoint(&Left); //update BeginningPoint
			updateCreatureLocationInBoardAndScreen(gameBoard);
			stop = true;

		}
		else
			HandleWithNotSpace(gameBoard, Left.getXCoord(), Left.getYCoord() - 4);

	}
	 if (DistanceTwoPoints(&Right, &Pnearest) <= min_distance && !stop)
	{
		 if (gameBoard.charByCoordinate(Right.getXCoord(), Right.getYCoord() - 4) == ' ')
		 {
			 //min_distance = DistanceTwoPoints(&Right, &Pnearest);
			 Pnow = Right;		//Update Now
			 setBegginingPoint(&Right); //update BeginningPoint
			 updateCreatureLocationInBoardAndScreen(gameBoard);
			 stop = true;

		 }
		 else
			 HandleWithNotSpace(gameBoard, Right.getXCoord(), Right.getYCoord() - 4);
		
	}
	 if (DistanceTwoPoints(&Up, &Pnearest) <= min_distance && !stop)
	{
		if (gameBoard.charByCoordinate(Up.getXCoord(), Up.getYCoord() - 4) == ' ')
		{
		
			//min_distance = DistanceTwoPoints(&Up, &Pnearest);
			Pnow = Up;		//Update Now
			setBegginingPoint(&Up); //update BeginningPoint
			updateCreatureLocationInBoardAndScreen(gameBoard);
			stop = true;
			
		
		}
		else
			HandleWithNotSpace(gameBoard, Up.getXCoord(), Up.getYCoord() - 4);

	}
	 if (DistanceTwoPoints(&Down, &Pnearest) <= min_distance&& !stop)
	{
		if (gameBoard.charByCoordinate(Down.getXCoord(), Down.getYCoord() - 4) == ' ')
		{
			//min_distance = DistanceTwoPoints(&Down, &Pnearest);
			Pnow = Down;		//Update Now
			setBegginingPoint(&Down); //update BeginningPoint
			updateCreatureLocationInBoardAndScreen(gameBoard);
			stop = true;

		}
		else
			HandleWithNotSpace(gameBoard, Down.getXCoord(), Down.getYCoord() - 4);

	}
	*/
}


void NumFlyers::findTheNearestSolutionNumberXYCoordinates(board& gameBoard,Mission&  mish)
{
	min_distance = 80;
	int numOfDigits = 0;
	int dist1=0,dist2=0,dist3=0;
	int SizeArr = gameBoard.getLogSizeArr();


	for (int i = 0; i < SizeArr; i++)
	{
		if (mish.winNumber(gameBoard.getDataArr()[i]->num))
		{


			numOfDigits = gameBoard.getDataArr()[i]->numOfDigits;

			switch (numOfDigits)
			{
			case 1:	//one digit number
			{
				Pcheck.set(gameBoard.getDataArr()[i]->xCoord, gameBoard.getDataArr()[i]->yCoord);
				dist1 = DistanceTwoPoints(&Pnow, &Pcheck);
				if (dist1 < min_distance)
				{
					Pnearest.set(Pcheck.getXCoord(), Pcheck.getYCoord());
					min_distance = dist1;
					//gotoxy(0, 50);
					//cout << "neaarest number is : " << gameBoard.getDataArr()[i]->num;
					//cout << "distance  is : " << min_distance;
					//cout << " nearest.x =  " << Pcheck.getXCoord();
					//cout << "nearst.y= " << Pcheck.getYCoord();
				}
				break;
			}
			case 2:
			{
				Pcheck.set(gameBoard.getDataArr()[i]->xCoord, gameBoard.getDataArr()[i]->yCoord);
				dist1 = DistanceTwoPoints(&Pnow, &Pcheck);
				Pcheck.set(Pcheck.getXCoord() + 1, Pcheck.getYCoord());
				dist2 = DistanceTwoPoints(&Pnow, &Pcheck);
				if (dist1 < dist2)
				{
					if (dist1 < min_distance)
					{
						min_distance = dist1;
						Pnearest.set(Pcheck.getXCoord()-1, Pcheck.getYCoord());
						//gotoxy(0, 50);
						//cout << "neaarest number is : " << gameBoard.getDataArr()[i]->num;
						//cout << "distance  is : " << min_distance;
						//cout << " nearest.x =  " << Pcheck.getXCoord();
						//cout << "nearst.y= " << Pcheck.getYCoord();
					}
				}
				else
				{
					if (dist2 < min_distance)
					{
						min_distance = dist2;
						Pnearest.set(Pcheck.getXCoord() , Pcheck.getYCoord());
						//gotoxy(0, 50);
						//cout << "neaarest number is : " << gameBoard.getDataArr()[i]->num;
						//cout << "distance  is : " << min_distance;
						//cout << " nearest.x =  " << Pcheck.getXCoord();
						//cout << "nearst.y= " << Pcheck.getYCoord();
					}
				}
				break;
			}
			case 3:
			{

				Pcheck.set(gameBoard.getDataArr()[i]->xCoord, gameBoard.getDataArr()[i]->yCoord);
				dist1 = DistanceTwoPoints(&Pnow, &Pcheck);
				Pcheck.set(Pcheck.getXCoord() + 1, Pcheck.getYCoord());
				dist2 = DistanceTwoPoints(&Pnow, &Pcheck);
				Pcheck.set(Pcheck.getXCoord() + 1, Pcheck.getYCoord());
				dist3 = DistanceTwoPoints(&Pnow, &Pcheck);


				if (dist1 < dist2)
				{
					if (dist1 < dist3)
					{
						if (dist1 < min_distance)
						{
							min_distance = dist1;
							Pnearest.set(Pcheck.getXCoord()-2, Pcheck.getYCoord());
							//gotoxy(0, 50);
							//cout << "neaarest number is : " << gameBoard.getDataArr()[i]->num;
							//cout << "distance  is : " << min_distance;
							//cout << " nearest.x =  " << Pcheck.getXCoord();
							//cout << "nearst.y= " << Pcheck.getYCoord();
						}
					}
					else //dist3<=dist1
					{
						min_distance = dist3;
						Pnearest.set(Pcheck.getXCoord(), Pcheck.getYCoord());
						//gotoxy(0, 50);
						//cout << "neaarest number is : " << gameBoard.getDataArr()[i]->num;
						//cout << "distance  is : " << min_distance;
						//cout << " nearest.x =  " << Pcheck.getXCoord();
						//cout << "nearst.y= " << Pcheck.getYCoord();
					}
				}
				else  //dist2<dist1
				{
					if (dist2 < dist3)
					{
						if (dist2 <= min_distance)
						{
							min_distance = dist2;
							Pnearest.set(Pcheck.getXCoord() - 1, Pcheck.getYCoord());
							//gotoxy(0, 50);
							//cout << "neaarest number is : " << gameBoard.getDataArr()[i]->num;
							//cout << "distance  is : " << min_distance;
							//cout << " nearest.x =  " << Pcheck.getXCoord();
							//cout << "nearst.y= " << Pcheck.getYCoord();
						} //if
						else   //dist3<dist2
						{
							min_distance = dist3;
							Pnearest.set(Pcheck.getXCoord() , Pcheck.getYCoord());
							//gotoxy(0, 50);
							//cout << "neaarest number is : " << gameBoard.getDataArr()[i]->num;
							//cout << "distance  is : " << min_distance;
							//cout << " nearest.x =  " << Pcheck.getXCoord();
							//cout << "nearst.y= " << Pcheck.getYCoord();
						}

					}
				}//else
				break;

			}//case3
			}//switch
		}//if Sol
	}//for
}//function



void NumFlyers:: initialFlyerToBeginning(board& gameBoard)
{
	min_distance = 80;
	deleteCretureFromBoardAndScreen( gameBoard);
	setBegginingPoint(&StartPoint);
}

void NumFlyers:: HandleWithNotSpace(board& gameBoard, int x, int y)
{
	char temp = gameBoard.charByCoordinate(x, y);

	if (temp >= '0'&& temp <= '9')
	{
		//cout << "HEREEEEEEEEEEEEEEEEEEEE";
		gameBoard.getTheMSDigitCoordinate(&x, &y);
		gameBoard.setDeleteY(y);
		gameBoard.setDeleteX(x);
		gameBoard.deleteNumFromData();
	}
	else if (temp == '!')
	{
		if (Pnow.getXCoord()==x+1)	// !  Left to Pnow
		{
			Pnow.set(Pnow.getXCoord() - 2,y);
		}
		else if (Pnow.getXCoord() == x - 1)	// ! Right to Pnow
		{
			Pnow.set(Pnow.getXCoord() + 2,y);
		}
	}
	else if (temp == '@')
	{
		if (Pnow.getYCoord() == y + 1)	// @  Down to Pnow
		{
			Pnow.set(x,Pnow.getYCoord() - 2);
		}
		else if (Pnow.getYCoord() == y - 1)	// @ Up to Pnow
		{
			Pnow.set(x,Pnow.getYCoord() + 2);
		}
	}
}

void NumFlyers::updateNumEatersLocationInBoardAndScreen(board& gameBoard)
{
	gameBoard.writeOnScreenBoardByCoordinate(getBeginningPoint().getXCoord(), getBeginningPoint().getYCoord()-4,'%');
}