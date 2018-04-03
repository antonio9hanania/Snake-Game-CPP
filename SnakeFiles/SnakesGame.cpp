#include "SnakesGame.h"
//////////////////////////////////RUN//////////////////////////////
void SnakesGame::run() {
	int numCounter = 0;
	int addNumToScreen = 0;
	bool stop2 = false, WinOrLoose=false;
	int scoreS1 = 0, scoreS2 = 0;
	bool shootHimself = false, stuckByReverse ;
	TypeOfBulletHit bulletHitType;
	int dieCounters[2] = { 0,0 };
	char keyPressed;
	bool buxFix = true;

	int whoWon;
	
	mish = MishCont.getRandomizeMissionsFromContainer();
	mish.printInstraction();
	for (size_t k = 0; k < 5; k++)
	{
		flyers[k]->updateCreatureLocationInBoardAndScreen(gameBoard);

	}

//setting 1) the color of the bullet stucks according Snake's color     2)the coords to print bullet stuck visual view on screen	 3) printing bullet stacks visual view on screen

	for (size_t i = 0; i < 2; i++)
	{
		p[i].getAndUpdateSnakeBulletStuck().setColorOfBulletsAndXCoordsToPrintStuck(p[i].getSnakeColor(), p[i].getXToGoToPrintStuckOfBullets(), p[i].getYToGoToPrintStuckOfBullets());
		p[i].getSnakeBulletStuck().printVisualStuck(p[i].getXToGoToPrintStuckOfBullets(), p[i].getYToGoToPrintStuckOfBullets(), 5, p[i].getSnakeBulletStuck().getStackColor());
	}


	mish.readySetGo();

	while (stop2 == false && numCounter < SIXTY && p[0].getSnakeLogSize() < 15 && p[1].getSnakeLogSize() < 15)
	{
		bool stop1 = false;

		
		handleKeyPressed(keyPressed, scoreS1, scoreS2, numCounter, dieCounters);

		for (size_t t = 0; t < size; t++)
		{
			p[t].resetStuckByReverse();
		}

		Sleep(180);
		
		if (addNumToScreen == 5)
		{
			addNumToScreen = 0;
			numCounter++;
			gameBoard.addNumToBoard();
		}
		addNumToScreen++;

		for (size_t i = 0; i < size && stop2 == false; ++i) 
		{

			if (dieCounters[i] == 0)
			{
				stop1 = p[i].move(keyPressed, gameBoard, p[i].getSnakeLogSize());				
			}

			else
				updateDieCounterArr(dieCounters,i);
		


			if(p[i].getStuckByReverse())
				stuckByReverse = true;

			//this func  will check if the keyPressed is a shotting key and will make the movment for all the bullets that have shooted  
			bulletHitType = p[i].getAndUpdateSnakeBulletStuck().checkAndMoveIfPossible(keyPressed,p[i].getShootingKey(),p[i].getHeadOfSnake(),p[i].getDirection(), stuckByReverse, gameBoard, p[i].getSnakeChar(),p[1-i].getAndUpdateSnakeBulletStuck(), dieCounters[i], numCounter);		
			hittenSnake(i, bulletHitType, dieCounters, DontCare);
			stuckByReverse = false;
			if (dieCounters[i] == 0)
			{
				gameBoard.updateSnakeLocationInBoard(p[i].getBody(), p[i].getSnakeChar(), p[i].getSnakeLogSize(), p[i].getSnakeStuck());
			}


			if (bulletHitType == ON_LINE_FLAYER_PIN)
			{
				//cout << "PIN";
				flyers[3]->deleteCretureFromBoardAndScreen(gameBoard);
				flyers[3]->setOnScreen(false);
			}
			else if (bulletHitType == ON_LINE_PLAYER_NPIN)
			{
				//cout << "NPIN";
				flyers[4]->deleteCretureFromBoardAndScreen(gameBoard);
				flyers[4]->setOnScreen(false);
			}


			if (stop1 == true) //snake ate a number
			{
				int resNum = gameBoard.getNumByCoordinate((gameBoard.getDeleteX()+ROWS)%ROWS, (gameBoard.getDeleteY()+LINES)%LINES);
				gameBoard.deleteNumFromData();
				numCounter--;
				for (size_t k = 0; k < 5; k++) //initialFlyerToBeginning
				{
					flyers[k]->initialFlyerToBeginning(gameBoard);
				}
				WinOrLoose = mish.winNumber(resNum);
				whoWon = whoWonTheBattle(i, WinOrLoose);
				gameBoard.printScore(scoreS1, scoreS2);
				stop2 = true;
			}
			p[i].setSnakeStuck(FALSE);
		}


		////////////////////////////////////////////////////////////////////////////////////////
		FlyHit FlayerHitSnake;
		for (int moves = 0; moves < 2; moves++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (flyers[k]->getOnScreen() == true)
				{
					if (!((k == 4 || k == 3) && moves == 1))//make LineFlyers move just one step
					{

						flyers[k]->deleteCretureFromBoardAndScreen(gameBoard);
						FlayerHitSnake = flyers[k]->move(gameBoard, p, mish);	//move flyers 
						if (FlayerHitSnake == RowFlyEatDollar || FlayerHitSnake == RowFlyHitSulamin || FlayerHitSnake == LineFlyerEatSulamit || FlayerHitSnake == LineFlyersEatDollar)
							hittenSnake(k, bulletHitType, dieCounters, FlayerHitSnake);
						if (flyers[k]->getOnScreen())
							flyers[k]->updateCreatureLocationInBoardAndScreen(gameBoard);
						
					}
				}
			}

		}
		///////////////////////////////////////////////////////////////////////////////////////




		if (stop2 == true)
		{
			Sleep(600);

			handleKeyPressed(keyPressed, scoreS1, scoreS2, numCounter, dieCounters); // logsize and score are1 up to zarick
			updatingScoreWinLose(scoreS1, scoreS2, whoWon);
			gameBoard.deleteHalfOfTheNumbers();
			numCounter = gameBoard.getLogSizeArr();
			mish = MishCont.getRandomizeMissionsFromContainer();
			mish.printInstraction();
			for (size_t k = 0; k < 5; k++) //initialFlyerToBeginning
			{
				flyers[k]->initialFlyerToBeginning(gameBoard);
			}
			logsSizeKeyPressed = 0;
			//in a new mission we need to initial the bullet Stacks and after it
			for (size_t i = 0; i < 2; i++)
			{
				p[i].getAndUpdateSnakeBulletStuck().initialBulletStackAndRemoveBullets(p[i].getHeadOfSnake(), p[i].getDirection(), gameBoard);
				p[i].getSnakeBulletStuck().printVisualStuck(p[i].getXToGoToPrintStuckOfBullets(), p[i].getYToGoToPrintStuckOfBullets(), p[i].getSnakeBulletStuck().getLogicSizeOfBulletStuck(), p[i].getSnakeBulletStuck().getStackColor());
				p[i].saveSnakeStartingPos();
				p[i].resetRebornsLogSize();
			}

			bringDiedSnakesToLife(dieCounters);
			stop2 = false;
		}

		if (numCounter == SIXTY)
		{
			gotoxy(30, 0);
			cout << Color(YELLOW) << "Too hard? lets try a different mission";
			Sleep(200);
			cout << Color(WHITE);
			mish.BoldSollutions(gameBoard.getDataArr(), gameBoard.getLogSizeArr());
			handleKeyPressed(keyPressed, scoreS1, scoreS2, numCounter, dieCounters);
			gameBoard.deleteHalfOfTheNumbers();
			numCounter = gameBoard.getLogSizeArr();
			Sleep(3000);
			gotoxy(LINES, 0);
			cout << "                                                       ";
			mish = MishCont.getRandomizeMissionsFromContainer();
			mish.printInstraction();
			for (size_t k = 0; k < 5; k++) //initialFlyerToBeginning
			{
				flyers[k]->initialFlyerToBeginning(gameBoard);
			}
			logsSizeKeyPressed = 0;

			for (size_t i = 0; i < 2; i++)
			{
				p[i].getAndUpdateSnakeBulletStuck().initialBulletStackAndRemoveBullets(p[i].getHeadOfSnake(), p[i].getDirection(), gameBoard);
				p[i].getSnakeBulletStuck().printVisualStuck(p[i].getXToGoToPrintStuckOfBullets(), p[i].getYToGoToPrintStuckOfBullets(), p[i].getSnakeBulletStuck().getLogicSizeOfBulletStuck(), p[i].getSnakeBulletStuck().getStackColor());
				p[i].saveSnakeStartingPos();
				p[i].resetRebornsLogSize();
			}

			mish.readySetGo();
		}
	}

	if (p[0].getSnakeLogSize() >=15 ||  p[1].getSnakeLogSize()>=15)
	{
		gotoxy(24, 0);
		cout << "                                                       ";
		gotoxy(24, 0);
		cout << Color(YELLOW) << "We Have a Winner :) ";
		Sleep(3000);
		clrscr();
		gameBoard.printGameOver(scoreS1, scoreS2);
	}
	
}



//////////////////////////////////whoWonTheBattle//////////////////////////////

int SnakesGame::whoWonTheBattle(int i, bool WinOrLoose) {
	mish.winnigOrloosing(WinOrLoose);
	if (i == 0 && WinOrLoose == true) {
		gotoxy(30, 0);
		cout << Color(YELLOW) << "Good Job Player 1 :)";
		Sleep(1300);
		gotoxy(30, 0);
		cout << Color(WHITE) << "                    ";
		return 0;
	}

	else if (i == 1 && WinOrLoose == true) {

		gotoxy(30, 0);
		cout << Color(YELLOW) << "Good Job Player 2 :)";
		Sleep(1300);
		gotoxy(30, 0);
		cout << Color(WHITE) << "                    ";
		return 1;
	}

	else if (i == 0 && WinOrLoose == false) {
		gotoxy(30, 0);
		cout << Color(YELLOW) << "Sorry - Wrong!";
		Sleep(1300);
		gotoxy(30, 0);
		cout << Color(WHITE) << "                    ";
		mish.BoldSollutions(gameBoard.getDataArr(), gameBoard.getLogSizeArr());
		return 1;
	}

	else{ // (i == 1 && WinOrLoose == false) {
		gotoxy(30, 0);
		cout << Color(YELLOW) << "Sorry - Wrong!";
		Sleep(1300);
		gotoxy(30, 0);
		cout << Color(WHITE) << "                    ";;
		mish.BoldSollutions(gameBoard.getDataArr(), gameBoard.getLogSizeArr());
		return 0;
	}

}

//////////////////////////////////updatingScoreWinLose//////////////////////////////

void SnakesGame::updatingScoreWinLose(int& scoreS1, int& scoreS2, int whoWon)
{	
	switch (whoWon) {
	case(0):
		p[0].snakeLogicSize(1);
		scoreS1 += 1;
		gameBoard.printScore(scoreS1, scoreS2);
	case(1):
		p[1].snakeLogicSize(1);
		scoreS2 += 1;
		gameBoard.printScore(scoreS1, scoreS2);
	}

}




//////////////////////////////////updateDieCounterArr//////////////////////////////

void SnakesGame::updateDieCounterArr(int dieCounters[2],int i)
{
		if (dieCounters[i] == 25)
			dieCounters[i] = 0;
		else
			dieCounters[i]++;
}

//////////////////////////////////DeleteSnakeFromScreenAndBoard_ByIndex//////////////////////////////

void SnakesGame:: DeleteSnakeFromScreenAndBoard_ByIndex(int i)
{
	int size = p[i].getSnakeLogSize();

	for (int j = 0;j <=size+1;j++)
	{
		gameBoard.deletePointFromBoardAndScreen(p[i].getBody()[j].getXCoord(), p[i].getBody()[j].getYCoord());
	}

}
//////////////////////////////////hittenSnake//////////////////////////////

void SnakesGame::hittenSnake(int i, TypeOfBulletHit hit, int dieCounters[2], FlyHit FlyerHitSnake,bool isRecord)
{

	if (FlyerHitSnake == RowFlyHitSulamin)
	{
		Point newHead;
		dieCounters[0]++;
		DeleteSnakeFromScreenAndBoard_ByIndex(0);		//Unfortuantly - cannot include "Snake.h" in bulletStuck
		if (!isRecord) {
			gameBoard.ChooseRandomCoordsForDeletedSnake_head(newHead);//choose random head for the deleted snake 
			p[0].setRebornPoints(newHead);
		}
		else
			newHead = p[0].getRebornInRebArr();
		p[0].setNewHeadForSnake(newHead);
	}

	if (FlyerHitSnake == RowFlyEatDollar)
	{
		Point newHead;
		dieCounters[1]++;
		DeleteSnakeFromScreenAndBoard_ByIndex(1);		//Unfortuantly - cannot include "Snake.h" in bulletStuck
		if (!isRecord) {
			gameBoard.ChooseRandomCoordsForDeletedSnake_head(newHead);//choose random head for the deleted snake 
			p[1].setRebornPoints(newHead);
		}
		else			
			newHead = p[1].getRebornInRebArr();
		p[1].setNewHeadForSnake(newHead);
	}

	if (hit == ON_MY_SNAKE) {
		Point newHead;
		dieCounters[i]++;
		DeleteSnakeFromScreenAndBoard_ByIndex(i);		//Unfortuantly - cannot include "Snake.h" in bulletStuck
		if (!isRecord) {
			gameBoard.ChooseRandomCoordsForDeletedSnake_head(newHead);//choose random head for the deleted snake 
			p[i].setRebornPoints(newHead);
		}
		else
			newHead = p[i].getRebornInRebArr();
		p[i].setNewHeadForSnake(newHead);
		//choose a good Dir for the head so he wont stuck on another number at the first move
	}

	if (hit == ON_OTHER_SNAKE) {
		Point newHead;
		dieCounters[1 - i]++;
		DeleteSnakeFromScreenAndBoard_ByIndex(1 - i);
		if (!isRecord) {
			gameBoard.ChooseRandomCoordsForDeletedSnake_head(newHead);//choose random head for the deleted snake 
			p[1 - i].setRebornPoints(newHead);
		}
		else
			newHead = p[1 - i].getRebornInRebArr();
		p[1 - i].setNewHeadForSnake(newHead);
	}
	if (hit == ON_BOTH_SNAKES) {
		Point newHead1;
		dieCounters[i]++;
		DeleteSnakeFromScreenAndBoard_ByIndex(i);		//Unfortuantly - cannot include "Snake.h" in bulletStuck
		if (!isRecord) {
			gameBoard.ChooseRandomCoordsForDeletedSnake_head(newHead1);//choose random head for the deleted snake 
			p[i].setRebornPoints(newHead1);
		}
		else
			newHead1 = p[i].getRebornInRebArr();

		p[i].setNewHeadForSnake(newHead1);

		Point newHead2;
		dieCounters[1 - i]++;
		DeleteSnakeFromScreenAndBoard_ByIndex(1 - i);
		if (!isRecord) {
			gameBoard.ChooseRandomCoordsForDeletedSnake_head(newHead2);//choose random head for the deleted snake 
			p[1 - i].setRebornPoints(newHead2);
		}
		else {
			newHead2 = p[1 - i].getRebornInRebArr();
		}
		p[1 - i].setNewHeadForSnake(newHead2);
	}


	if (FlyerHitSnake == LineFlyersEatDollar)
	{

		Point newHead;
		dieCounters[1]++;
		DeleteSnakeFromScreenAndBoard_ByIndex(1);		//Unfortuantly - cannot include "Snake.h" in bulletStuck
		if (!isRecord) {
			gameBoard.ChooseRandomCoordsForDeletedSnake_head(newHead);//choose random head for the deleted snake 
			p[1].setRebornPoints(newHead);
		}
		else
			newHead = p[1].getRebornInRebArr();
		p[1].setNewHeadForSnake(newHead);
	}
	if (LineFlyerEatSulamit == FlyerHitSnake)
	{
		Point newHead;
		dieCounters[0]++;
		DeleteSnakeFromScreenAndBoard_ByIndex(0);		//Unfortuantly - cannot include "Snake.h" in bulletStuck
		if (!isRecord) {
			gameBoard.ChooseRandomCoordsForDeletedSnake_head(newHead);//choose random head for the deleted snake 
			p[0].setRebornPoints(newHead);
		}
		else
			newHead = p[0].getRebornInRebArr();
		p[0].setNewHeadForSnake(newHead);
	}

}


//////////////////////////////////bringDiedSnakesToLife//////////////////////////////

void SnakesGame::bringDiedSnakesToLife(int dieCounters[2])
{
	int i;
	for (i = 0; i < 2; i++)
	{
		if (dieCounters[i] !=0)
		{
			dieCounters[i] = 0;
		}
	}

}

//////////////////////////////////handleKeyPressed//////////////////////////////

void SnakesGame::handleKeyPressed(char & keyPressed, int &scoreS1, int& scoreS2, int & numCounter, int dieCounters[2]) {
	if (_kbhit()) {
		keyPressed = _getch();
		if (keyPressed == KEYS::ESC) {
			
			int temp = printSubMenu(mish, MishCont,gameBoard, scoreS1, scoreS2);

			if (temp == 4 || temp == 5)
			{
				for (size_t k = 0; k < 5; k++) //initialFlyerToBeginning
				{
					flyers[k]->initialFlyerToBeginning(gameBoard);
					flyers[k]->updateCreatureLocationInBoardAndScreen(gameBoard);

				}
				for (size_t i = 0; i < 2; i++)
				{
					p[i].saveSnakeStartingPos();
					p[i].printSnake();
					p[i].resetRebornsLogSize();
				}

				bringDiedSnakesToLife(dieCounters);
				logsSizeKeyPressed = 0;

				for (size_t i = 0; i < size; i++)
				{
					if (p[i].getStuckByReverse())
					{
						p[i].setLegalMove(false);

					}
				}


				for (size_t i = 0; i < 2; i++)
				{
					p[i].getAndUpdateSnakeBulletStuck().initialBulletStackAndRemoveBullets(p[i].getHeadOfSnake(), p[i].getDirection(), gameBoard);
				}
				if(temp == 4)
					numCounter = 0;


			}
			
			if (temp != 7) {
				//printing snake's bullet stack

				for (size_t i = 0; i < 2; i++)
				{
					p[i].getSnakeBulletStuck().printVisualStuck(p[i].getXToGoToPrintStuckOfBullets(), p[i].getYToGoToPrintStuckOfBullets(), p[i].getSnakeBulletStuck().getLogicSizeOfBulletStuck(), p[i].getSnakeBulletStuck().getStackColor());

				}
			}

			if (temp != 3 && temp!=7)
				mish.readySetGo();
			if (temp == 7) {

				for (size_t k = 0; k < 5; k++) //initialFlyerToBeginning
				{
					flyers[k]->initialFlyerToBeginning(gameBoard);
				}

				for (size_t i = 0; i < size; i++)
				{
					if (p[i].getStuckByReverse())
					{
						p[i].setLegalMove(false);
					}
				}
				runReplay();
			}
		}
	}
	else {
		keyPressed = 0;
	}
	keyPressedSaver[logsSizeKeyPressed++]  = keyPressed;
}


//////////////////////////////////runReplay//////////////////////////////

void SnakesGame::runReplay() {

	int numCounter = gameBoard.getCountOfImmediateNumbersOnBoard();
	int addNumToScreen = 0;
	bool stop2 = false, WinOrLoose = false;
	int scoreS1 = p[0].getScore(), scoreS2 = p[1].getScore();
	bool shootHimself = false, stuckByReverse = false;
	TypeOfBulletHit bulletHitType;
	int dieCounters[2] = { 0,0 };
	char keyPressed;
	int indexOfDataArr = 0;

	gameBoard.deleteAllDataArray();
	gameBoard.insertAllImidiatsToDataArr();

	gameBoard.dropAllImmediateNumToBoardAndScreen();

	for (size_t k = 0; k < 5; k++)
	{
		flyers[k]->updateCreatureLocationInBoardAndScreen(gameBoard);

	}

	for (size_t i = 0; i < 2; i++)
	{
		p[i].setBodyToStartPos();
		p[i].getAndUpdateSnakeBulletStuck().initialBulletStackAndRemoveBullets(p[i].getHeadOfSnake(), p[i].getDirection(), gameBoard);
	}

	gameBoard.printScore(scoreS1, scoreS2);
	gameBoard.printFrame();

	mish.printInstraction();

	//setting 1) the color of the bullet stucks according Snake's color     2)the coords to print bullet stuck visual view on screen	 3) printing bullet stacks visual view on screen

	for (size_t i = 0; i < 2; i++)
	{
		p[i].getAndUpdateSnakeBulletStuck().setColorOfBulletsAndXCoordsToPrintStuck(p[i].getSnakeColor(), p[i].getXToGoToPrintStuckOfBullets(), p[i].getYToGoToPrintStuckOfBullets());
		p[i].getSnakeBulletStuck().printVisualStuck(p[i].getXToGoToPrintStuckOfBullets(), p[i].getYToGoToPrintStuckOfBullets(), 5, p[i].getSnakeBulletStuck().getStackColor());
	}

	
	mish.readySetGo();

	for (int key = 0; key < logsSizeKeyPressed; key++)
	{
		bool stop1 = false;
		keyPressed = keyPressedSaver[key];

		for (size_t t = 0; t < size; t++)
		{
			p[t].resetStuckByReverse();
		}

		Sleep(180);


		if (addNumToScreen == 5)
		{
			numCounter++;
			gameBoard.updateDataArrFromrDataArrWODN(indexOfDataArr);
			gameBoard.addNumToBoard(true);
			indexOfDataArr++;
			addNumToScreen = 0;
		}
		addNumToScreen++;

		for (size_t i = 0; i < size && stop2 == false; ++i)
		{
			if (dieCounters[i] == 0)
			{

				stop1 = p[i].move(keyPressed, gameBoard, p[i].getSnakeLogSize());
			}

			else
				updateDieCounterArr(dieCounters, i);



			if (p[i].getStuckByReverse())
				stuckByReverse = true;

			//this func  will check if the keyPressed is a shotting key and will make the movment for all the bullets that have shooted  
			bulletHitType = p[i].getAndUpdateSnakeBulletStuck().checkAndMoveIfPossible(keyPressed, p[i].getShootingKey(), p[i].getHeadOfSnake(), p[i].getDirection(), stuckByReverse, gameBoard, p[i].getSnakeChar(), p[1 - i].getAndUpdateSnakeBulletStuck(), dieCounters[i], numCounter);


			stuckByReverse = false; // initionig to false to continue

			hittenSnake(i, bulletHitType, dieCounters, DontCare, true);




			//gameBoard.printBoard();
			if (dieCounters[i] == 0)
			{
				gameBoard.updateSnakeLocationInBoard(p[i].getBody(), p[i].getSnakeChar(), p[i].getSnakeLogSize(), p[i].getSnakeStuck());
			}

			if (bulletHitType == ON_LINE_FLAYER_PIN)
			{
				//cout << "PIN";
				flyers[3]->deleteCretureFromBoardAndScreen(gameBoard);
				flyers[3]->setOnScreen(false);
			}
			else if (bulletHitType == ON_LINE_PLAYER_NPIN)
			{
				//cout << "NPIN";
				flyers[4]->deleteCretureFromBoardAndScreen(gameBoard);
				flyers[4]->setOnScreen(false);
			}

			if (stop1 == true) //snake ate a number
			{
				int resNum = gameBoard.getNumByCoordinate((gameBoard.getDeleteX() + ROWS) % ROWS, (gameBoard.getDeleteY() + LINES) % LINES);
				gameBoard.deleteNumFromData();
				numCounter--;
				WinOrLoose = mish.winNumber(resNum);
				whoWonTheBattle(i, WinOrLoose );			
				stop2 = true;
			}
			p[i].setSnakeStuck(FALSE);

			////////////////////////////////////////////////////////////////////////////////////////
			

			///////////////////////////////////////////////////////////////////////////////////////
			
			if (numCounter == SIXTY)
			{
				gotoxy(30, 0);
				cout << Color(YELLOW) << "Too hard? lets try a different mission";
				Sleep(200);
				cout << Color(WHITE);
				mish.BoldSollutions(gameBoard.getDataArr(), gameBoard.getLogSizeArr());
			}
		}
		FlyHit FlayerHitSnake;
		for (int moves = 0; moves < 2; moves++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (flyers[k]->getOnScreen() == true)
				{
					if (!((k == 4 || k == 3) && moves == 1))//make LineFlyers move just one step
					{
					
						flyers[k]->deleteCretureFromBoardAndScreen(gameBoard);
						FlayerHitSnake = flyers[k]->move(gameBoard, p, mish);	//move flyers 
						if (FlayerHitSnake == RowFlyEatDollar || FlayerHitSnake == RowFlyHitSulamin || FlayerHitSnake == LineFlyerEatSulamit || FlayerHitSnake == LineFlyersEatDollar)
							hittenSnake(k, NOT_RELEVENT, dieCounters, FlayerHitSnake,true);
						if (flyers[k]->getOnScreen())
							flyers[k]->updateCreatureLocationInBoardAndScreen(gameBoard);
					}
				}
			}

		}

	}
	for (size_t i = 0; i < size; i++)
	{
		p[i].resetResetIndexToTravelReborn();
	}

	gameBoard.printReplayEnd();
	system("cls");

	gameBoard.PrintThat();
	mish.printInstraction();
	gameBoard.printScore(scoreS1, scoreS2);
	gameBoard.printFrame();
	for (size_t k = 0; k < 5; k++) //initialFlyerToBeginning
	{
		flyers[k]->initialFlyerToBeginning(gameBoard);
		flyers[k]->updateCreatureLocationInBoardAndScreen(gameBoard);
	}

}