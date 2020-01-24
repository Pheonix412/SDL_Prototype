#include<SDL.h>
#include"Game.h"
#include<iostream>
//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
int main(int argc, char** argv) {
	//this creates the object of the game
	Game* game = new Game();
	//calls the run funcation in the game obejct 
	game->run("TEST SDL", 800, 600, false);
	//this deltes the game obejct after the run function is called
	delete game;
	//returns 0
	return 0;
}


// TODO: Add sound effects for a shooting a bullet

// TODO: If enemy is shot with bullet, enemy disapears with the bullet and 
// is replaced with a explosion

// TODO: Fix player movement

// TODO: Add adjustable speed to enemies are faster in higher waves -Optional

