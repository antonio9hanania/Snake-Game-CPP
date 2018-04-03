#ifndef _BOARD
#define _BOARD
#include "Point.h"
#include "Direction.h"
#include "stdlib.h"
#include "Point.h"
#include "GeneralFunc.h"
#include <time.h>

#define SIXTY 60

typedef struct DataNum {
	int num;
	int xCoord,yCoord;
	int numOfDigits;
//	bool isImmidiete = false;
	
}DATANUM;

class board {
	int deleteX, deleteY;
	//char OriginalBoard[ROWS][LINES];
	char Board[ROWS][LINES];

	Point ChosenPoint;
	int	  ChosenNum  ;
	DATANUM** dataArr;

	DATANUM ImmediateNumbersOnBoard[SIXTY]; // straring 
	int countOfImmediateNumbersOnBoard = 0;
	int logicSizeOfArr = 0;

	
	DATANUM DatArrWithoutDeletedNumbers[500]; 
	int logicSizeDataArrWODN = 0;

public:
	board(int snake1LogSize, int snake2LogSize, const Point & head1, const Point & head2, char c1, char c2, Direction dir1 = Direction::DOWN, Direction dir2 = Direction::DOWN);
	void ResetCountOfImmediateNumbersOnBoard() { countOfImmediateNumbersOnBoard = 0; }
	int getCountOfImmediateNumbersOnBoard()const {return countOfImmediateNumbersOnBoard;}
	void ResetLogicSizeDataArrWODN() { logicSizeDataArrWODN = 0; }
	void updateBulletInBoard( int x, int y, char ch = '*');
	void deleShootCharFromBoardAndScreen(Point prevShootPoint, char shootingChar = '*');
	DATANUM** getDataArr() { return dataArr; }
	int getLogSizeArr() { return logicSizeOfArr; }
	int getDeleteX() { return deleteX; }
	int getDeleteY() { return deleteY; }
	void setDeleteX(int x) {  deleteX = x; }
	void setDeleteY(int y) {  deleteY = y; }
	void board::printGameOver(int sc1, int sc2);
	void deleteAllDataArray();
	void board::deleteAllocation();
	void board::printFrame();
	void board::printScore(int scoreS1, int scoreS2);
	void board::PrintThat();
	void initialBoard();
	void ChooseNumToBoard(); //Magrila number
	bool ChoosePointToBoard();	//return Succees or failure 
	bool isLegalCoord(int coordX, int  coordY);// 
	void addNumToBoard(bool OnRecord = false);
	int getNumByCoordinate(int x, int y);
	bool updateBoard();
	void updateSnakeLocationInBoard(Point* s,char c, int snakeLogSize,bool Stuck);
	void printBoard();
	char charByCoordinate(int x, int y) { return Board[x][y]; }
	bool nextState(int x, int y, Direction d);
	void updateDataArr();
	void intialDataArr();
	void printDataArray();
	//void deleteNumFromDatArrWithoutDeletedNumbers();
	void deleteNumFromData();
	void getTheMSDigitCoordinate(int* numCoordX, int* numCoordY);
	void deleteNumFromBoardAndScreen();
	void deleteNumFromArray();
	void swapDataNumInArray(int a,int b);
	void swapDataNumInWODNArray(int a, int b);
	void deleteHalfOfTheNumbers();
	void handleDatArrWithoutDeletedNumbers();
	void handleImmediateArr();
	void deletePointFromBoardAndScreen(int x, int y);
	void ChooseRandomCoordsForDeletedSnake_head(Point &newHead);
	void addSelectedNumToBoardAndScreen(int x, int y, int num);
	void PrintDatArrWithoutDeletedNumbers();
	void insertAllImidiatsToDataArr();
	void printReplayEnd();
	void updateDataArrFromrDataArrWODN(int index);
	void dropAllImmediateNumToBoardAndScreen();
	void updateCreatureInBoard(int x, int y, char c);
	void writeOnScreenBoardByCoordinate(int x, int y, char c);


};


#endif // !_BOARD
