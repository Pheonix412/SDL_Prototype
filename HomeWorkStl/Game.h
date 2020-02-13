#pragma once

#include "Texture.h"
#include "EnemyWave1.h"
#include"PlayerSpaceShip.h"
#include"PowerUp.h"

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
	//timers
	unsigned int GameRunTimer;
	unsigned int LastUpadateTimer;
	unsigned int lastSpawnL;
	unsigned int lastSpawnM;
	unsigned int lastSpawnS;
	unsigned int LastBullet;
	float GameTime;
	float lastClear;
	int finalTime;

	//these are pointers for the window and the render
	SDL_Window* SdlWindow;
	SDL_Renderer* SdlRenderer;

	//this is a boolean varaible that holds the status of the game 
	bool IsTheGameOver;
	
	//this is a pointer to the texture 
	Texture* M_Texture;

	//this creates object for the game obejcts and the enemies 
	std::vector<GameObject*>M_GameObjects;
	std::vector<EnemyWave1*>M_EnemyObjects;
    std::vector<PowerUp*>M_PowerUpObjects;
    std::vector<PowerUp*>M_PowerUpObjects2;
    std::vector<PowerUp*>M_PowerUpObjects3;
    std::vector<PowerUp*>M_PowerUpObjects4;
	//this is the pointer of the players space ship
	PlayerSpaceShip* playerSpaceS;
	Texture* playerBullets;

	//this pointer holds the users input 
	Input* UserInput;

	//holds position for enemy and player
	Vector2 M_Position1;

	//this variable holds the numbers of the enemies 
	int enemycount;

	//this is a pointer of the enemy
	EnemyWave1* Enemies;

    PowerUp* PowerU;
    PowerUp* PowerU2;
    PowerUp* PowerU3;
    PowerUp* PowerU4;

	//this pointer holds the texture of the enemy 
	Texture* M_EnemyTexture;

	//stores text texture
	Texture* m_textTexture;

    Texture* M_PowerUpTexture;
    Texture* M_PowerUpTexture2;
    Texture* M_PowerUpTexture3;
    Texture* M_PowerUpTexture4;
	//stores font
	TTF_Font* m_font;
	//stores the audio
	Audio* audio;
    int shootSpeed;
    float PowerUpTime;


	int Lives;
	bool isPlayerAlive;

	Vector2 M_Position2;
	Texture* playerSpacetexture;
	std::vector <Bullet1*> m_bullets;

	int Difiiculty;
    bool PowerUpActive;
    bool isGameFinnished;
    int numberofkills;

public:
	Game();
	//this function starts the game 
	bool start();

	//this function processes the users input 
	void processinput();
	
	//this holds the type of event that the user has  done 
	SDL_Event e;
	
	//this is the update function for the game 
	void update(float deltaTime);
	
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
	
	//Resets the game
	void ResetGame();

	//changes the difficulty of the game
	void ChangeDifficulty(int diff);

	//resets the players lives
	void SetLives(int diff);

	//sets the amount of lives the player has
	int SetIntLives(int diff);

	//this is the destructor for the game
	~Game();

	//sets the game state
	void SetGameState(bool status);
};