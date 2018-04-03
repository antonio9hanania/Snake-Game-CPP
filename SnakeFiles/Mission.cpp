#include "Mission.h"


Mission& Mission::operator=(const Mission& other) {
	type = other.type;
	mishString = other.mishString;
	MinRange = other.MinRange;
	MaxRange = other.MaxRange;
	randomPartGiven = other.randomPartGiven;
	instraction = other.instraction;
	xCoordToPrint = other.xCoordToPrint;
	yCoordToPrint = other.yCoordToPrint;
	randomPartFollowRange = other.randomPartFollowRange;
	if (type == EXERCISE_UPPER_D_AND_UNDER_D) {
		for (size_t i = 0; i < 4; i++)
		{
			Arr[i] = other.Arr[i];
		}
		op1 = other.op1;
		op2 = other.op2;
		missingIndx = other.missingIndx;
	}

	return *this;
}

void Mission::navigateType()
{
	bool found = false;
	if ((mishString.compare("PRIME_UPPER_U_AND_UNDER_D") == 0)&& !found) {
		type = PRIME_UPPER_U_AND_UNDER_D;
		xCoordToPrint = 25;
		yCoordToPrint=1;
		found = true;
	}
	else if ((mishString.compare("DEVIDE_X") == 0)&& !found){
		type = DEVIDE_X;
			xCoordToPrint = 33;
			yCoordToPrint= 1 ;
			found = true;
	}
	else if ((mishString.compare("DEVIDES_NUM_UPPER_U_UNDER_D") == 0)&&!found) {
		type = DEVIDES_NUM_UPPER_U_UNDER_D;
			xCoordToPrint = 23;
			yCoordToPrint= 1;
			found = true;
	}
	else if ((mishString.compare("SQRT_OF_INTEGER_UPPER_U_AND_UNDER_D") == 0)&&!found) {
		type = SQRT_OF_INTEGER_UPPER_U_AND_UNDER_D;
		xCoordToPrint = 17;
		yCoordToPrint = 1;
		found = true;
	}
	else if ((mishString.compare("EXERCISE_UPPER_D_AND_UNDER_D") == 0)&&!found) {
		type = EXERCISE_UPPER_D_AND_UNDER_D;
			xCoordToPrint = 18;
			yCoordToPrint= 1;
			found = true;
	}
	else if ((mishString.compare("POWER_OF_X")==0) && !found) {
		type = POWER_OF_X;
			xCoordToPrint = 33;
			yCoordToPrint= 1;
			found = true;
	}
	else {
		cout << " ERROR PLEASE READ THE TAMPLATE OF THE TXT FILE AND GIVE ME THE RIGHT VALUES" << endl;
		getchar();
		exit(1);
	}
}

void Mission::printInstraction() {
	gotoxy(0, 0);
	setTextColor(WHITE);
	cout  <<"Press ESC to get sub menu." << endl;
	gotoxy(5,1);
	cout << "                                                                      ";
	gotoxy(xCoordToPrint, yCoordToPrint);
	cout <<Color(LIGHTBLUE )<< instraction;
	setTextColor(WHITE);

}


void Mission::SetInstraction()
{
	switch (type) {
	case(PRIME_UPPER_U_AND_UNDER_D):
		instraction = "Eat PRIME NUMBER UPPER " + to_string(MinRange) + " And Under " + to_string(MaxRange);
		break;
	case(DEVIDE_X):
		instraction = "Eat X Solution:  X % " + to_string(randomPartGiven) + " = 0";
		break;
	case(DEVIDES_NUM_UPPER_U_UNDER_D):
		instraction = "Eat X sotution   :  X % " + to_string(randomPartFollowRange) + " =" + to_string(randomPartGiven);
		break;
	case(SQRT_OF_INTEGER_UPPER_U_AND_UNDER_D):
		instraction = "Eat X solution " + to_string(MinRange) + "<= X <=" + to_string(MaxRange) + "  SQRT(X) = Integer";
		break;
	case(EXERCISE_UPPER_D_AND_UNDER_D):
		setInstractionToExercise();
		break;
	case(POWER_OF_X):
		instraction = "Eat Power Of " + to_string(randomPartGiven);
		break;
	}
}












int  Mission:: whoStronger(Operations op1, Operations op2) {
	if ((op1 == MINUS || op1 == PLUS) && (op2 == MULT || op2 == DEVIDE)) return 1;
	else return 0;
}


double Mission::calculate() {
	double firstPartRes;
	int firstOperand = whoStronger(op1, op2);

	if (firstOperand == 0) {
		switch (op1) {
		case(MULT):
			firstPartRes = Arr[0] * Arr[1];
			break;
		case(DEVIDE):
			firstPartRes = (double)Arr[0] / (double)Arr[1];
			break;
		case(MINUS):
			firstPartRes = Arr[0] - Arr[1];
			break;
		case(PLUS):
			firstPartRes = Arr[0] + Arr[1];
			break;
		}
		switch (op2) {
		case(MULT):
			return firstPartRes * (double)Arr[2];
		case(DEVIDE):
			return firstPartRes / (double)Arr[2];
		case(MINUS):
			return firstPartRes - Arr[2];
		case(PLUS):
			return firstPartRes + Arr[2];


		}
	}

	else {
		switch (op2) {
		case(MULT):
			firstPartRes = Arr[1] * Arr[2];
			break;
		case(DEVIDE):
			firstPartRes = (double)Arr[1] / (double)Arr[2];
			break;
		case(MINUS):
			firstPartRes = Arr[1] - Arr[2];
			break;
		case(PLUS):
			firstPartRes = Arr[1] + Arr[2];
			break;


		}
		switch (op1) {
		case(MULT):
			return (double)Arr[0] * firstPartRes;
		case(DEVIDE):
			return (double)Arr[0] / firstPartRes;
		case(MINUS):
			return Arr[0] - firstPartRes;
		case(PLUS):
			return Arr[0] + firstPartRes;

		}
	}
}


void Mission::Ex2MishHelper() { // will select numbers , operators and updete them in caller func


	double resOfCalc;

	for (size_t i = 0; i < 3; i++) {// num4 is the res of the rest so it is not randomal
		Arr[i] = (rand()) % (MaxRange - MinRange + 1) + MinRange;
	}

	op1 = (Operations)(rand() % OperationsSize);
	op2 = (Operations)(rand() % OperationsSize);

	resOfCalc = calculate();

	while (resOfCalc != (int)resOfCalc) {
		op1 = (Operations)(rand() % OperationsSize);
		op2 = (Operations)(rand() % OperationsSize);
		resOfCalc = calculate();

	}


	Arr[3] = (int)resOfCalc;

	missingIndx = rand() % 4;

	while (Arr[missingIndx] > 169 || Arr[missingIndx] < 0) {
		missingIndx = rand() % 4;
	}

}



void Mission::setInstractionToExercise()
{
	Ex2MishHelper();
	instraction = "Eat X solution " + to_string(MinRange) + "<= X <= " + to_string(MaxRange) + " :  ";

	Operations opArr[2];
	opArr[0] = op1;
	opArr[1] = op2;

	for (int i = 0; i < 4; i++)
	{
		handleDigitSet(Arr[i], i, missingIndx);
		if (i < 2)
			handleOperator(opArr[i]);
		if (i == 2)
			instraction += " = ";
	}

}

void Mission::handleDigitSet(int toPrint, int arrIndx, int missingIndx)  {
	if (missingIndx == arrIndx)
		instraction += " X ";
	else
		instraction += to_string(toPrint);
}

void Mission::handleOperator(const Operations op) {
	switch (op)
	{
	case(MULT):
		instraction += " * ";
		break;

	case(DEVIDE):
		instraction += " / ";
		break;

	case(MINUS):
		instraction +=  " - ";
		break;
	case(PLUS):
		instraction +=  " + ";
		break;
	}
}






bool Mission::powerOfX(int n) {
	int k = n;
	while (((n % randomPartGiven )== 0) && n>1)
		n  = n / randomPartGiven;
	
	if (n == 1)
		return true;
	else
		return false;
}


bool Mission::primeUpperUAndUnderD(int n) {

	if (n<MinRange || n > MaxRange)
		return false;
	else {
		if (n == 0 || n == 1)
			return false;
		else {
			int i = 2;
			if (MinRange >= 2)
				i = MinRange;
			for (; i < n; i++)
			{
				if (n % i == 0)
					return false;
			}
			return true;
			}
	}
}





bool Mission::dividesX(int n) {

	return n%randomPartGiven == 0;
}



bool Mission::sqrtOfIntegerUpperUNDuNDERd(int n)
{
	if (n< MinRange || n> MaxRange)
		return false;
	else {
		double res = sqrt(n);
		return res == (int)res;
	}
}



bool Mission:: Ex2Mishion(int num) {
	return num == Arr[missingIndx];
}




bool Mission::dividesNumUpperUAndUnderD(int n) {
		return(( n % randomPartFollowRange) == randomPartGiven);
}


bool Mission::winNumber(int num) { // will get a number and needed to know the current mission and will return the result if the number is a win or lose.
	switch (type) {
	case PRIME_UPPER_U_AND_UNDER_D: return primeUpperUAndUnderD(num);
	case DEVIDE_X: return dividesX(num);
	case DEVIDES_NUM_UPPER_U_UNDER_D: return dividesNumUpperUAndUnderD(num);
	case SQRT_OF_INTEGER_UPPER_U_AND_UNDER_D: return sqrtOfIntegerUpperUNDuNDERd(num);
	case EXERCISE_UPPER_D_AND_UNDER_D: return Ex2Mishion(num);
	case POWER_OF_X: return powerOfX(num);
	}
}




void Mission::BoldSollutions(DataNum **  dataArr, int logicSizeOfArr) {
	bool flag = false;
	for (size_t i = 0; i < logicSizeOfArr; i++)
	{
		if (winNumber(dataArr[i]->num) == true) {
			flag = true;
			gotoxy(dataArr[i]->xCoord, dataArr[i]->yCoord + 4);
			cout << Color(BOLD) << dataArr[i]->num;
			Sleep(10);
			gotoxy(dataArr[i]->xCoord, dataArr[i]->yCoord + 4);
			cout << Color(WHITE) << dataArr[i]->num;
			Sleep(10);
			gotoxy(dataArr[i]->xCoord, dataArr[i]->yCoord + 4);
			cout << Color(BOLD) << dataArr[i]->num;
			Sleep(10);
			gotoxy(dataArr[i]->xCoord, dataArr[i]->yCoord + 4);
			cout << Color(WHITE) << dataArr[i]->num;
			Sleep(10);
			gotoxy(dataArr[i]->xCoord, dataArr[i]->yCoord + 4);
			cout << Color(BOLD) << dataArr[i]->num;

		}
		setTextColor(WHITE);
	}
	if (flag)
		Sleep(2000);
	for (size_t i = 0; i < logicSizeOfArr; i++)
	{
		if (winNumber(dataArr[i]->num) == true) {
			gotoxy(dataArr[i]->xCoord, dataArr[i]->yCoord + 4);
			cout << Color(WHITE) << dataArr[i]->num;
		}
	}
}














void Mission::readySetGo()
{
	gotoxy(35, 0);
	cout << Color(YELLOW) << "READY!";
	Beep(349, 200);
	Sleep(1000);
	gotoxy(35, 0);
	cout << "       ";
	gotoxy(35, 0);
	cout << Color(YELLOW) << "SET";
	Beep(349, 200);
	Sleep(1000);

	gotoxy(35, 0);
	cout << "       ";
	gotoxy(35, 0);
	cout << Color(YELLOW) << "GO!!";
	Beep(587, 700);

	Sleep(1000);
	gotoxy(35, 0);
	cout << "       ";
	cout << Color(WHITE);
}

void Mission::winnigOrloosing(bool WinOrLoose) {
	if (!WinOrLoose)
		looseSong();
	else
		winSong();
}













































