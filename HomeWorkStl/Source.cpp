#include<SDL.h>
#include"Game.h"
#include<iostream>
int main(int argc, char ** argv) {



	Game* game = new Game();

	game->run("TEST SDL", 800, 600, false);
	delete game;

	return 0;
}