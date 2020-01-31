#include<SDL.h>
#include"Game.h"
#include<iostream>
//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
int main(int argc, char** argv) {
	//this creates the object of the game
	Game* game = new Game();
	//calls the run funcation in the game obejct 
	game->run("TEST SDL", 1500, 800, false);
	//this deltes the game obejct after the run function is called
	delete game;
	//returns 0
	return 0;
}





// TODO: If enemy is shot with bullet, enemy disapears with the bullet


