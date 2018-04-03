#include"startNewGame.h"


void StarNewGame() {

	int startGame = printMainMenu();

	
	if (startGame == 2) {
		newGame();	
		
	}
}

void newGame() {
	system("CLS");
	SnakesGame game;
	game.run();
}