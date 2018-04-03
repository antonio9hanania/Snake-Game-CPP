#include "Menus.h"


int printMainMenu()
{
	char keyPressed;
	clrscr();
	gotoxy(0, 0);
	cout << Color(LIGHTGREY) << "Edited By: Antonio H."<<endl;cout<<Color(LIGHTGREY)<<"           Dan.N" << endl;
	gotoxy(15, 3);
	setTextColor(LIGHTMAGENTA);
	cout << "***************************************************" << endl;
	gotoxy(15, 4);
	cout << "**    1) Display Instractions Of The Game        **" << endl;
	gotoxy(15, 5);
	cout << "**    2) Start Game                              **" << endl;
	gotoxy(15, 6);
	cout << "**    9) ESC Game                                **" << endl;
	gotoxy(15, 7);
	cout << "***************************************************" << endl;
	gotoxy(22, 8);
	
	cout << Color(LIGHTCYAN) << "Press one of those options (1, 2, 9)" << endl;
	setTextColor(LIGHTBLUE);

	lowdingPress(32, 10);
	setTextColor(WHITE);

	keyPressed = _getch();
	switch (keyPressed) {
	case '1':
		clrscr();
		setTextColor(MAGENTA);
		cout << "It is a snake game: there is 2 kinds of snakes: " << endl;
		cout << "the first is # and the second is $.\n" << endl;
		cout << "In each round will be a new Mission that her Instraction will shown\nabove the game board.\n" << endl;
		cout << "The Winner of a round  will be:\n" << endl;
		cout << Color(CYAN) << "optionA: the one that ate a resualt Number according the Mission.\n" << endl;
		setTextColor(WHITE);
		cout << Color(MAGENTA) << "OR\n" << endl;
		cout << Color(CYAN) << "optionB: if the other snake ate a Non-resualt Number.\n" << endl;

		setTextColor(MAGENTA);
		cout << "\n\nThere is also a shooting Option:\n" << endl;
		cout << Color(LIGHTCYAN)<<"First player " << Color(RED) << '#' << Color(LIGHTCYAN) << " Shoting Key is" << Color(LIGHTRED) << " 'z'\n" << endl;
		cout <<Color(LIGHTCYAN)<< "Second player " << Color(GREEN) << '$' << Color(LIGHTCYAN) << " Shooting Key is" << Color(LIGHTGREEN) << " 'n'\n"<< endl;
		setTextColor(WHITE);
		cout << "\n\nPress any key to continue ";

		_getch();
		clrscr();
		printMainMenu();
	case '2':
		clrscr();
		return 2; //will start game outside this fanc when the returned value is 2
	case '9':
		gotoxy(25, 11);
		exit(1);

	default:
		gotoxy(19, 11);
		cout << "Error, There is no option for this key pressed\n" << endl;
		Sleep(1000);
		printMainMenu();
	}

}




int printSubMenu(Mission & mish,MissionsContainer & mishContainer ,board& gameBoard, int scoreS1, int  scoreS2)
 {
	char keyPressed;
	system("cls");

	gotoxy(15, 3);
	setTextColor(LIGHTMAGENTA);
	cout << "***************************************************" << endl;
	gotoxy(15, 4);
	cout << "**    1) ESC Game                                **" << endl;
	gotoxy(15, 5);
	cout << "**    2) Return to Main Menu                     **" << endl;
	gotoxy(15, 6);
	cout << "**    3) Continu playing at the last point       **" << endl;
	gotoxy(15, 7);
	cout << "**    4) Restart Mission                         **" << endl;
	gotoxy(15, 8);
	cout << "**    5) Start a new Mission                     **" << endl;
	gotoxy(15, 9);
	cout << "**    6) Start a new Game                        **" << endl;
	gotoxy(15, 10);
	cout << "**    7) Play a Recorded to mission till now     **" << endl;
	gotoxy(15, 11);
	cout << "***************************************************" << endl;
	setTextColor(LIGHTBLUE);



	gotoxy(19, 12);

	cout << Color(LIGHTCYAN) << "Press one of those options (1, 2, 3, 4, 5, 6)" << endl;
	setTextColor(LIGHTBLUE);
	lowdingPress(32, 13);
	setTextColor(WHITE);




	keyPressed = _getch();
	switch (keyPressed) {
	case '1':
		clrscr();
		gameBoard.deleteAllDataArray();
		gameBoard.deleteAllocation();
		gameBoard.printGameOver(scoreS1, scoreS2);
		gotoxy(0, 24);
		
		exit(1);
	case '2':
		cout << "\n" << endl;
		gameBoard.deleteAllDataArray();
		gameBoard.deleteAllocation();
		gameBoard.printGameOver(scoreS1, scoreS2);
		StarNewGame();
		break;
	case '3':
	
		clrscr();

		gameBoard.PrintThat();

		mish.printInstraction();
		gameBoard.printScore(scoreS1, scoreS2);
		gameBoard.printFrame();
		cout << Color(WHITE);
		return 3;
	
	case '4':

		clrscr();
		gameBoard.initialBoard();
		
		gameBoard.deleteAllDataArray();
		gameBoard.ResetCountOfImmediateNumbersOnBoard();
		gameBoard.ResetLogicSizeDataArrWODN();
		mish.printInstraction();
		gameBoard.printScore(scoreS1, scoreS2);
		gameBoard.printFrame();
	
		//mish.readySetGo();
		
		return 4;
	case '5':
		clrscr();
		gameBoard.printScore(scoreS1,scoreS2);
		gameBoard.printFrame();
		
		mish = mishContainer.getRandomizeMissionsFromContainer();
		mish.printInstraction();
		gameBoard.PrintThat();
		//mish.readySetGo();
		return 5; // will call startNewGame while saving the scores of snaked befor esc 
	case '6':
		gameBoard.deleteAllDataArray();
		gameBoard.deleteAllocation();
		gameBoard.printScore(scoreS1, scoreS2);

		newGame();
		break;
	case '7':
		clrscr();
		return 7;
		break;

	default:
		gotoxy(19, 14);
		cout << "Error, There is no option for this key pressed\n" << endl;
		Sleep(1000);
		printSubMenu(mish, mishContainer,gameBoard,scoreS1,scoreS2);

	}
}


