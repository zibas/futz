#include <iostream>
using namespace std;

#include <stdlib.h>
#include <stdio.h>

#include "Futz.h"
#include "TestGame.h"
#include "GameBase.h"



int main(int argc, char** argv) {

	// This will both initialize and retrive the futz singleton
	Futz* futz = Futz::Instance();

	// Futz expects a game to provide an object that extends the GameBase class
	TestGame* game = new TestGame();
	futz->gameObject = game;

	// The futz game loop will take it from here
	futz->Start(argc, argv);

	return 0;
}
