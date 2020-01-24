#pragma once

#include "Texture.h"
#include "EnemyWave1.h"
#include"PlayerSpaceShip.h"
#include<vector>
#include"Vector2.h"
#include"Input.h"
#include<Windows.h>
#include<SDL_syswm.h>
#include"resource1.h"
#include "Audio.h"
class Game
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
	//please refer back to the tutorials done in class for more information about this.
private:
	//these are pointers for the window and the render
	SDL_Window* SdlWindow;
	SDL_Renderer* SdlRenderer;
	//this is a boolean varaible that holds the status of the game 
	bool IsTheGameOver;
	unsigned int LastUpadateTimer;
	unsigned int lastSpawn;
	//this is a pointer to the texture 
	Texture* M_Texture;
	//this creates object for the game obejcts and the enemies 
	std::vector<GameObject*>M_GameObjects;
	std::vector<EnemyWave1*>M_EnemyObjects;
	//this is the pointer of the players space ship
	GameObject* playerSpaceS;
	//this holds the texture of the players space ship
	PlayerSpaceShip* M_Player_SpaceShip;
	Texture* playerBullets;
	//this pointer holds the users input 
	Input* UserInput;
	
	Vector2 M_Position1;
	//this variable holds the numbers of the enemies 
	int enemycount;
	//this is a pointer of the enemy
	EnemyWave1* Enemies;
	//this pointer holds the texture of the enemy 
	Texture* M_EnemyTexture;
	//stores text texture
	Texture* m_textTexture;
	//stores font
	TTF_Font* m_font;

	Audio* audio;
public:
	Game();
	//this function starts the game 
	bool start();
	//this function processes the users input 
	void processinput();
	//this holds the type of event that the user has  done 
	SDL_Event e;
	//this is the update function for the game 
	void update();
	//this is the draw function for the game 
	void draw();
	//this is the shutdown function for the game
	void shutdown();
	//this is the run function for the game 
	void run(char* title,int width,int height,bool fullscreen);
	//this is the destroy function for the game 
	void destroy();
	//player enemy collision check
	void PE_CollisionCheck();

	//this is the destructor for the game
	~Game();

	void SetGameState(bool status);
};