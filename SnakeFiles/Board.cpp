#include  "board.h"
#include "GeneralFunc.h"




board::board(int snake1LogSize, int snake2LogSize, const Point& head1, const Point& head2, char c1, char c2, Direction dir1, Direction dir2) {
	int i, j;
	//initialing board with spaces
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < LINES; j++)
			Board[i][j] = ' ';

	// initialing board with the snakes posotions

	int xToMove = head1.getXCoord();
	int yToMove = head1.getYCoord();
	Board[xToMove][yToMove] = c1;

	for (i = 1; i < snake1LogSize; i++)
	{
		xToMove += head1.getDir_x();
		yToMove += head1.getDir_y();
		Board[xToMove][yToMove] = c1;
	}

	xToMove = head2.getXCoord();
	yToMove = head2.getYCoord();
	Board[xToMove][yToMove] = c2;
	for (i = 1; i < snake2LogSize; i++)
	{
		xToMove += head2.getDir_x();
		yToMove += head2.getDir_y();
		Board[xToMove][yToMove] = c2;
	}
	//initialing dataArr with Nulls;

	dataArr = (DATANUM**)new DATANUM*[SIXTY];
	for (i = 0; i < SIXTY; i++)
	{
		dataArr[i] = NULL;
	}
	printScore(0, 0);
	printFrame();


}



void board::addNumToBoard(bool OnRecord)
{
	if (!OnRecord) {
		ChooseNumToBoard();
		ChoosePointToBoard();	//get two coords and check legality
	}
	else {
		ChosenPoint.set(dataArr[logicSizeOfArr - 1]->xCoord, dataArr[logicSizeOfArr - 1]->yCoord);
		ChosenNum = dataArr[logicSizeOfArr - 1]->num;
	}

	updateBoard();

	if(!OnRecord)
		updateDataArr();

}

int board::getNumByCoordinate(int x, int y)
{
	bool endLoop = false;
	for (int i = 0; i < logicSizeOfArr && endLoop == false; i++)
	{
		if (dataArr[i]->xCoord == deleteX && dataArr[i]->yCoord == deleteY)
			return dataArr[i]->num;
	}
}
//I will update Board when in two cases:
//1) each and every movement of the snake		
//2) add a number to Board.

bool board::updateBoard()
//2) add a number to Board.
{
	char tempStr[4] = "   "; //initial with 3 spaces chars
	if (ChosenNum > 169)  //Check the number is Valid cause tempStr can only handle with 3 digits number
		return false;
	_itoa_s(ChosenNum, tempStr, 10);		//make ChosenNum a string terminated with \0
	int Xco, Yco;
	Xco = ChosenPoint.getXCoord();
	Yco = ChosenPoint.getYCoord();

	if (ChosenNum >= 0 && ChosenNum <= 9)
	{
		Board[Xco][Yco] = tempStr[0];
		gotoxy(Xco, Yco + 4);
		cout << Color(WHITE) << tempStr[0];
		return true;
	}
	else if (ChosenNum >= 10 && ChosenNum <= 99)
	{
		Board[Xco][Yco] = tempStr[0];
		gotoxy(Xco, Yco + 4);
		cout << Color(WHITE) << tempStr[0];
		//
		Board[Xco + 1][Yco] = tempStr[1];
		gotoxy(Xco + 1, Yco + 4);
		cout << Color(WHITE) << tempStr[1];
		return true;
	}
	else if (ChosenNum >= 100 && ChosenNum <= 169)
	{
		Board[Xco][Yco] = tempStr[0];
		gotoxy(Xco, Yco + 4);
		cout << Color(WHITE) << tempStr[0];
		//
		Board[Xco + 1][Yco] = tempStr[1];
		gotoxy(Xco + 1, Yco + 4);
		cout << Color(WHITE) << tempStr[1];
		//
		Board[Xco + 2][Yco] = tempStr[2];
		gotoxy(Xco + 2, Yco + 4);
		cout << Color(WHITE) << tempStr[2];
		return true;
	}
	else
		return false;
}

//bool updateBoard(char ch) {}
void board::ChooseNumToBoard() //Magrila number
{

	int probability = rand() % 3;
	switch (probability)
	{
	case 0:
		ChosenNum = 0 + rand() % 26;
		break;
	case 1:
		ChosenNum = 26 + rand() % 56;
		break;
	case 2:
		ChosenNum = 82 + rand() % 88;
		break;
	}
}

void board::initialBoard()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < LINES; j++)
			Board[i][j] = ' ';
}



bool board::ChoosePointToBoard()	//return Succees or failure 
{
	int coordX;
	int coordY;
	bool Legality = false;
	while (!Legality)
	{

		coordX = rand() % ROWS;

		coordY = rand() % LINES;
		Legality = isLegalCoord(coordX, coordY);
	}
	ChosenPoint.set(coordX, coordY);
	return true;
}


bool board::isLegalCoord(int coordX, int  coordY)
{
	int chosenNumDig = findHowManyDigits(ChosenNum);


	if (Board[coordX][coordY] == ' '&&Board[coordX - 1][coordY] == ' '&& Board[coordX][coordY - 1] == ' '&&Board[coordX][coordY + 1] == ' ')  //insure that ChosenNum wont to number from left
	{
		//Now i will check that ChosenNum wont mix with any number from its right side
		// i need to deal with 3 seperted cases (1,2 or 3 digits which ChosenNumber can be

		if (chosenNumDig == 1 && Board[coordX + 1][coordY] == ' ')
		{
			return true;
		}
		else if (chosenNumDig == 2 && Board[coordX + 1][coordY] == ' '&& Board[coordX + 2][coordY] == ' ')
		{

			if (Board[coordX + 1][coordY + 1] == ' '&&Board[coordX + 1][coordY - 1] == ' ')
				return true;
		}
		else if (chosenNumDig == 3 && Board[coordX + 1][coordY] == ' '&& Board[coordX + 2][coordY] == ' '&&Board[coordX + 3][coordY] == ' ')

			if (Board[coordX + 1][coordY - 1] == ' '&&Board[coordX + 1][coordY + 1] == ' ')
				if (Board[coordX + 2][coordY - 1] == ' '&& Board[coordX + 2][coordY + 1] == ' ')
					return true;
				else
				{
					//cout << "invalide number " << endl;
					return false;
				}
	}
	//mix with other number in its left side
	return false;
}


void board::updateSnakeLocationInBoard(Point* s, char c, int snakeLogSize, bool Stuck)
{
	for (int i = 0; i <= snakeLogSize; i++)
	{
		int xCoord = s[i].getXCoord();
		int yCoord = s[i].getYCoord();
		Board[xCoord][yCoord] = c;
		if (i == snakeLogSize &&!Stuck)
			Board[xCoord][yCoord] = ' ';
	}
}

void board::deletePointFromBoardAndScreen(int x, int y)
{
	Board[x][y] = ' ';
	gotoxy(x, y + 4);
	cout << ' ';
}
void board::printBoard()
{
	//A function for me to see the Data that stored in Board
	gotoxy(0, 26);
	for (int i = 0; i < LINES; i++)
	{
		for (int j = 0; j < ROWS; j++)
			cout << Board[j][i];
		cout << endl;
	}
}


bool board::nextState(int x, int y, Direction d)
{
	char temp;
	switch (d)
	{
	case LEFT:
		if (Board[x - 1][y] != ' '&&x - 1 > 0)
			return false;
		else
			return true;

	case RIGHT:
		if (Board[x + 1][y] != ' '&&x + 1 < ROWS)
			return false;
		else
			return true;

	case UP:
		if (Board[x][y - 1] != ' '&&y - 1 > 0)
			return false;
		else return true;

	case DOWN:
		temp = Board[x][y + 1];
		if (temp != ' ')
			return false;
		else
			return true;
	default: return false;



	}
}

void board::updateDataArr() {

	if (logicSizeOfArr <= 60)
	{
		dataArr[logicSizeOfArr] = (DATANUM*)new DATANUM;
		dataArr[logicSizeOfArr]->xCoord = ChosenPoint.getXCoord();
		dataArr[logicSizeOfArr]->yCoord = ChosenPoint.getYCoord();
		dataArr[logicSizeOfArr]->num = ChosenNum;
		dataArr[logicSizeOfArr]->numOfDigits = findHowManyDigits(ChosenNum);

		DatArrWithoutDeletedNumbers[logicSizeDataArrWODN].xCoord = dataArr[logicSizeOfArr]->xCoord;
		DatArrWithoutDeletedNumbers[logicSizeDataArrWODN].yCoord = dataArr[logicSizeOfArr]->yCoord;
		DatArrWithoutDeletedNumbers[logicSizeDataArrWODN].numOfDigits = dataArr[logicSizeOfArr]->numOfDigits;
		DatArrWithoutDeletedNumbers[logicSizeDataArrWODN].num = dataArr[logicSizeOfArr]->num;
		logicSizeDataArrWODN++;

		logicSizeOfArr++;

	}
}


void board::intialDataArr()
{
	dataArr = (DATANUM**)new DATANUM*[SIXTY];
	for (int i = 0; i < SIXTY; i++)
	{
		dataArr[i] = NULL;
	}
}

void board::printDataArray()
{
	gotoxy(0, 31);
	cout << "Data Array is : \n";
	for (int i = 0; i < logicSizeOfArr; i++)
	{
		cout << "num is :" << dataArr[i]->num << " numOfDIGITS is " << dataArr[i]->numOfDigits << "Coords =  (" << dataArr[i]->xCoord << "'" << dataArr[i]->yCoord << ")" << endl;
	}
}


void board::deleteNumFromData()
{

	deleteNumFromArray();
	deleteNumFromBoardAndScreen();


}


void board::getTheMSDigitCoordinate(int* numCoordX, int* numCoordY)
{
	if (Board[*numCoordX - 1][*numCoordY] == ' ')
	{
		return;
	}
	else if (Board[*numCoordX - 1][*numCoordY] >= '0'&&Board[*numCoordX - 1][*numCoordY] <= '9')
	{
		if (Board[*numCoordX - 2][*numCoordY] == ' ')
			*numCoordX = *numCoordX - 1;
		else if (Board[*numCoordX - 2][*numCoordY] >= '0'&&Board[*numCoordX - 2][*numCoordY] <= '9')
			*numCoordX = *numCoordX - 2;
		else
			*numCoordX = *numCoordX - 1;

	}
}
void board::deleteNumFromBoardAndScreen()
{
	int i = 0;


	while (Board[deleteX + i][deleteY] != ' '&&i < 3)
	{

		Board[deleteX + i][(deleteY)] = ' ';

		gotoxy(deleteX + i, (deleteY + 4));

		cout << " ";
		i++;
	}
}



void board::deleteNumFromArray()
{

	bool endLoop = false;
	int xToDelete = deleteX, yToDelete = deleteY;
	for (int i = 0; i < logicSizeOfArr && endLoop == false; i++)
	{
		if (dataArr[i]->xCoord == xToDelete  && dataArr[i]->yCoord == yToDelete)
		{
			swapDataNumInArray(i, logicSizeOfArr - 1);
			delete[] dataArr[logicSizeOfArr - 1];
			logicSizeOfArr--;
			endLoop = true;

		}
	}
}

void board::swapDataNumInArray(int a, int  b)
{
	DATANUM* temp = dataArr[a];
	dataArr[a] = dataArr[b];
	dataArr[b] = temp;
}
void board::swapDataNumInWODNArray(int a, int b) {
	DATANUM temp = DatArrWithoutDeletedNumbers[a];
	DatArrWithoutDeletedNumbers[a] = DatArrWithoutDeletedNumbers[b];
	DatArrWithoutDeletedNumbers[b] = temp;
}



void board::deleteHalfOfTheNumbers()
{
	int newSize = logicSizeOfArr / 2;
	for (int i = 0; i < newSize; i++)
	{
		deleteX = dataArr[i]->xCoord;
		deleteY = dataArr[i]->yCoord;
		deleteNumFromData();
	}
	handleDatArrWithoutDeletedNumbers();
	countOfImmediateNumbersOnBoard = logicSizeOfArr;// -newSize;
	logicSizeDataArrWODN = logicSizeOfArr;
	handleImmediateArr();

}

void board::handleDatArrWithoutDeletedNumbers() {
	for (size_t i = 0; i < logicSizeDataArrWODN; i++) {
		if (i < logicSizeOfArr) {
			DatArrWithoutDeletedNumbers[i].num = dataArr[i]->num;
			DatArrWithoutDeletedNumbers[i].numOfDigits = dataArr[i]->numOfDigits;
			DatArrWithoutDeletedNumbers[i].xCoord = dataArr[i]->xCoord;
			DatArrWithoutDeletedNumbers[i].yCoord = dataArr[i]->yCoord;
		}
		else {
			DatArrWithoutDeletedNumbers[i].num = 0;
			DatArrWithoutDeletedNumbers[i].numOfDigits = 0;
			DatArrWithoutDeletedNumbers[i].xCoord = 0;
			DatArrWithoutDeletedNumbers[i].yCoord = 0;
		}
	}
}
void board::handleImmediateArr() {

	for (size_t i = 0; i < countOfImmediateNumbersOnBoard; i++)
	{
		ImmediateNumbersOnBoard[i].num = dataArr[i]->num;
		ImmediateNumbersOnBoard[i].numOfDigits = dataArr[i]->numOfDigits;
		ImmediateNumbersOnBoard[i].xCoord = dataArr[i]->xCoord;
		ImmediateNumbersOnBoard[i].yCoord = dataArr[i]->yCoord;
	}
}

void board::deleteAllDataArray()
{
	for (int i = 0; i < logicSizeOfArr - 1; i++)
	{
		delete dataArr[i];
	}
	logicSizeOfArr = 0;
}
void board::deleteAllocation()
{
	delete[]dataArr;
}


void board::printFrame()
{
	gotoxy(0, LINES + 4);
	for (int i = 0; i < 80; i++)
		cout << Color(DARKGREY) << "+";

	gotoxy(0, 3);
	for (int i = 0; i < 80; i++)
		cout << Color(DARKGREY) << "+";
}
void board::printScore(int scoreS1, int scoreS2)
{
	gotoxy(0, 2);
	cout << Color(RED) << "Player1 '#' :" << scoreS1;
	gotoxy(65, 2);
	cout << Color(GREEN) << "Player2 '$' :" << scoreS2;


}
void board::PrintThat() {
	gotoxy(0, 4);

	for (int i = 0; i < LINES; i++)
	{
		for (int j = 0; j < ROWS; j++) {


			if (Board[j][i] == '#') {
				cout << Color(RED) << '#';
				setTextColor(WHITE);
			}
			else if (Board[j][i] == '$') {
				cout << Color(GREEN) << '$';
				setTextColor(WHITE);
			}
			else if (Board[j][i] == '*')
				cout << ' ';
			else
				cout << Board[j][i];

		}
		//cout << endl;

	}
}

void board::printGameOver(int sc1, int sc2)
{
	const char gameOver[22][81] = {
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
		"+       *******             *                  *       *         ************* +",
		"+     **                   * *                * *     * *        **            +",
		"+   **                    *   *              *   *   *   *       **            +",
		"+ **                     *     *            *     * *     *      **            +",
		"+ **                    *       *          *       *       *     ************* +",
		"+ **        ******     ***********        *                 *    **            +",
		"+ **             *    *           *      *                   *   **            +",
		"+ **             *   *             *    *                     *  **            +",
		"+   *************   *               *  *                       * ************* +",
		"+                                                                              +",
		"+     **********        *                 *    *************    ************** +",
		"+   *            *       *               *     **               **           * +",
		"+ *                *      *             *      **               **           * +",
		"+ *                 *      *           *       **               ************** +",
		"+ *                 *       *         *        *************    **      **     +",
		"+ *                 *        *       *         **               **       **    +",
		"+ *                 *         *     *          **               **        **   +",
		"+ *                *           *   *           **               **         **  +",
		"+   *            *              * *            **               **          ** +",
		"+     **********                 *             *************    **           * +",
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",

	};


	clrscr();

	gotoxy(0, 2);
	for (int i = 0; i < 22; i++)
	{
		cout << Color(LIGHTGREEN) << gameOver[i] << endl;
	}

	gotoxy(35, 0);
	if (sc1 < sc2)
		cout << Color(LIGHTRED) << "the winner is : PLAYER 2    '$' ";
	else if (sc1 > sc2)
		cout << Color(LIGHTRED) << "the winner is : PLAYER 1     '#' ";
	else
		cout << Color(LIGHTRED) << "there is no winer:)";
	setTextColor(WHITE);
	gotoxy(0, 24);
}


void board::updateBulletInBoard(int x, int y, char ch) {
	Board[x][y] = ch;
}





void board::deleShootCharFromBoardAndScreen(Point prevShootPoint, char shootingChar) {
	int coordX = prevShootPoint.getXCoord();
	int coordY = prevShootPoint.getYCoord();

	if (Board[coordX][coordY] == shootingChar)
	{
		Board[coordX][coordY] = ' ';
		prevShootPoint.draw(' ');
	}
}

void board::ChooseRandomCoordsForDeletedSnake_head(Point& newHead) //choose random head for the deleted snake 
{
	bool LegalCoord = false;
	int x = ((rand()) % ROWS);
	int y = ((rand()) % LINES);
	while (!LegalCoord)
	{
		x = ((rand()) % ROWS);
		y = ((rand()) % LINES);
		if (Board[x][y] == ' ')
		{
			if (Board[x + 1][y] == ' ')
			{
				newHead.changeDir(RIGHT);
				LegalCoord = true;

			}
			else if (Board[x - 1][y] == ' ')
			{
				newHead.changeDir(LEFT);
				LegalCoord = true;

			}
			else if (Board[x][y + 1] == ' ')
			{
				newHead.changeDir(DOWN);
				LegalCoord = true;

			}
			else if (Board[x][y - 1] == ' ')
			{
				newHead.changeDir(UP);
				LegalCoord = true;
			}
		}

	}


	newHead.set(x, y);


}




void board::dropAllImmediateNumToBoardAndScreen() { // initializing board, seting him to immediate numbers, pinting to screen;

	for (size_t i = 0; i < ROWS; i++)
	{
		for (size_t j = 0; j < LINES; j++)
		{
			Board[i][j] = ' ';

		}
	}
	for (size_t i = 0; i < countOfImmediateNumbersOnBoard; i++)
	{
			int x = ImmediateNumbersOnBoard[i].xCoord;
			int y = ImmediateNumbersOnBoard[i].yCoord;
			int num = ImmediateNumbersOnBoard[i].num;
			addSelectedNumToBoardAndScreen(x, y, num);
	}
}

void board::addSelectedNumToBoardAndScreen(int Xco, int Yco, int num) {
	char tempStr[4] = "   "; //initial with 3 spaces chars
	_itoa_s(num, tempStr, 10);		//make ChosenNum a string terminated with \0


	if (num >= 0 && num <= 9)
	{
		Board[Xco][Yco] = tempStr[0];
		gotoxy(Xco, Yco + 4);
		cout << Color(WHITE) << tempStr[0];
	}
	else if (num >= 10 && num <= 99)
	{
		Board[Xco][Yco] = tempStr[0];
		gotoxy(Xco, Yco + 4);
		cout << Color(WHITE) << tempStr[0];
		//
		Board[Xco + 1][Yco] = tempStr[1];
		gotoxy(Xco + 1, Yco + 4);
		cout << Color(WHITE) << tempStr[1];
	}
	else // (num >= 100 && num <= 169)
	{
		Board[Xco][Yco] = tempStr[0];
		gotoxy(Xco, Yco + 4);
		cout << Color(WHITE) << tempStr[0];
		//
		Board[Xco + 1][Yco] = tempStr[1];
		gotoxy(Xco + 1, Yco + 4);
		cout << Color(WHITE) << tempStr[1];
		//
		Board[Xco + 2][Yco] = tempStr[2];
		gotoxy(Xco + 2, Yco + 4);
		cout << Color(WHITE) << tempStr[2];
	}
}

void board::PrintDatArrWithoutDeletedNumbers() { // just for checking
	
	for (size_t i = 0; i < logicSizeDataArrWODN; i++)
	{
		gotoxy(DatArrWithoutDeletedNumbers[i].xCoord, DatArrWithoutDeletedNumbers[i].yCoord + 4);
		char temp[4] = "   ";
		_itoa_s(DatArrWithoutDeletedNumbers[i].num, temp, 10);
		cout << temp;
	}
}

void board::insertAllImidiatsToDataArr() {

	for (int i = 0; i < countOfImmediateNumbersOnBoard; i++)
	{
		dataArr[i] = (DATANUM*)new DATANUM;
		dataArr[i]->num = ImmediateNumbersOnBoard[i].num;
		dataArr[i]->numOfDigits	= ImmediateNumbersOnBoard[i].numOfDigits;
		dataArr[i]->xCoord = ImmediateNumbersOnBoard[i].xCoord;
		dataArr[i]->yCoord = ImmediateNumbersOnBoard[i].yCoord;
	}
	logicSizeOfArr = countOfImmediateNumbersOnBoard;

}



void board::printReplayEnd() {


	char replayEnd[24][81] = { "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
							   "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
							   "++                                                                            ++",
							   "++                                                                            ++",
							   "++      *********     ***    *      *** *                   ***      *******  ++",
							   "++      **            *  *   *      *    *                 *   *     **       ++",
							   "++      *********     *   *  *      *     *               *     *    *****    ++",
							   "++      **            *    * *      *    *                 *   *     **       ++",
							   "++      *********     *     **      *** *                   ***      **       ++",
							   "++                                                                            ++",
							   "++                                                                            ++",
							   "++                                                                            ++",
							   "++                                                                            ++",
							   "++      *********   *********   ********    **              **       *     *  ++",
							   "++      **      *   **          **     *    **             *  *       *   *   ++",
							   "++      ********    *********   ********    **            *    *       * *    ++",
							   "++      **  **      **          **          **           ********       *     ++",
							   "++      **    **    **          **          **          *        *      *     ++",
							   "++      **     **   *********   **          *********  *          *     *     ++",
							   "++                                                                            ++",
							   "++                                                                            ++",
							   "++                                                                            ++",
							   "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
							   "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++",
	};
	clrscr();

	gotoxy(0, 0);
	for (int i = 0; i < 24; i++)
	{
		cout << Color(LIGHTCYAN) << replayEnd[i] << Color(WHITE) << endl;

	}
	gotoxy(25, 21);
	cout << "Press any key to continue " << endl;
	_getch();
}

void board::updateDataArrFromrDataArrWODN(int index) {
	int myIndex = index + countOfImmediateNumbersOnBoard ;
	dataArr[logicSizeOfArr] = (DATANUM*)new DATANUM;
	dataArr[logicSizeOfArr]->num = DatArrWithoutDeletedNumbers[myIndex].num;
	dataArr[logicSizeOfArr]->numOfDigits = DatArrWithoutDeletedNumbers[myIndex].numOfDigits;
	dataArr[logicSizeOfArr]->xCoord = DatArrWithoutDeletedNumbers[myIndex].xCoord;
	dataArr[logicSizeOfArr]->yCoord = DatArrWithoutDeletedNumbers[myIndex].yCoord;
	logicSizeOfArr++;

}


void board::updateCreatureInBoard(int x, int y, char c)
{
	Board[x][y] = c;

	gotoxy(x, y + 4);
	cout << c;
}

void board::writeOnScreenBoardByCoordinate(int x, int y, char c)
{
	Board[x][y] = c;

	gotoxy(x, y + 4);
	cout << c;
}