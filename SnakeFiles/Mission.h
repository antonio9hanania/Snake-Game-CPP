#ifndef _Missions_H_
#define _Missions_H_

#include <string>
#include <iostream>
#include "Gotoxy.h"
#include "Color.h"
#include "Snake.h"

using namespace std;


enum MissionsIndx {
	PRIME_UPPER_U_AND_UNDER_D, DEVIDE_X, DEVIDES_NUM_UPPER_U_UNDER_D, SQRT_OF_INTEGER_UPPER_U_AND_UNDER_D, EXERCISE_UPPER_D_AND_UNDER_D, POWER_OF_X
};
enum { MissionSize = 6 };



/*        c'tor getting    (string _mish, int _MinRange, int _MaxRange, int _randomPart)        
		  when you want the get a new mission just call SetInstraction before use it to get to randomized mission
*/




class Mission
{
	////////Mission data mems/////////{
	MissionsIndx type;
	string mishString;
	int randomPartGiven = 0;
	int MinRange = 0;
	int MaxRange = 0;
	int randomPartFollowRange = 0;
	string instraction;
	int xCoordToPrint, yCoordToPrint;
	////////////////////////////////////}



	// EXERCISE DATA MEMBERS
	//////EXERCISE DATA MEMBERS//////{
	enum Operations
	{
		MULT, DEVIDE, MINUS, PLUS
	};
	enum { OperationsSize = 4 };

	int Arr[4];
	Operations  op1, op2;
	int missingIndx;
	////////////////////////////////}

	///////Private Functions////////{
	void SetInstraction();
	void setInstractionToExercise();
	void handleDigitSet(int toPrint, int arrIndx, int missingIndx);
	void handleOperator(const Operations op);
	int whoStronger(Operations op1, Operations op2);
	double calculate();
	void  navigateType();
	////////////////////////////////}

	///////////////////////////
	bool powerOfX(int n);
	void Ex2MishHelper();
	bool primeUpperUAndUnderD(int n);
	bool dividesX(int n);
	bool sqrtOfIntegerUpperUNDuNDERd(int n);
	bool Ex2Mishion(int num);
	bool dividesNumUpperUAndUnderD(int n);
	//////////////////////////////





public:
	Mission(string _mish, int _MinRange, int _MaxRange, int _randomPartGiven) :
		mishString(_mish), MinRange(_MinRange), MaxRange(_MaxRange), randomPartGiven(_randomPartGiven)
	{
		navigateType();
		randomPartFollowRange = (rand() ) % ( MaxRange -MinRange + 1) + MinRange ;
	};
	Mission() {};

	Mission & operator=(const Mission & other);

	void readySetGo();

	void winnigOrloosing(bool WinOrLoose);

	void printInstraction();
	
	void randomizeMyMish(){		
		randomPartFollowRange = (rand()) % (MaxRange - MinRange + 1) + MinRange;
		SetInstraction();
	}

	void BoldSollutions(DataNum ** dataArr, int logicSizeOfArr);

	bool winNumber(int num);
};

#endif