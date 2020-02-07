#pragma once
#include <vector>
#include "GameObject.h"
#include"Bullet1.h"
#include <SDL_mixer.h>
#include "Audio.h"

class PlayerSpaceShip : public GameObject
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
private:
	//this holds the velocity and acceleration x and y variables 
	Vector2 M_Velocity;
	Vector2 M_Acceleration;
	//this holds the position of player space ship
	Vector2 M_Position1;
	//this holds the postion of the bulet 
	Vector2 M_Position2;
	//Vector2 m_colPOS;
	float maxVelocity;

	//holds how long its been since a bullet has been made
	unsigned int LastUpadateTimer;
	
	AABB* m_Collider;
	int m_colWidth;
	int m_colHeight;
	float m_MaxVelocity;
	SDL_Renderer* m_sdlRenderer;
	Animation* m_animation;
	Audio* audio;
	int m_playerDir;

public:
	//this is the space ship constructor 
	PlayerSpaceShip();
	//this is a overloaded constructor of the space ship
	PlayerSpaceShip(SDL_Renderer* renderer, Vector2 position, int colWidth, int colHeight);
	//Animtion Functions
	void AnimationLogic(Input* input);
	void IdleAnimation();
	void RunAnimation(bool flip = false);

	//this function adds force to the player 
	void AddPlayerForce(Vector2 force);

	//this function reduces force to the player 
	void ReducePlayerForce(Vector2 force);

	//get the player's X and Y position
	float GetPlayerY();
	float GetPlayerX();

	//get collider for player collisions
	AABB* GetCollider();
	
	//get player position
	Vector2 GetPlayerPos();
	
	//this function draws the player 
	void Draw(SDL_Renderer* renderer);

	//this function updates the player 
	void Update(float deltaTime);
	
	//these functions handle the users input 
	void HandleUserInput(Input* input);
	
	//this is the space ship destructor
	~PlayerSpaceShip();
};

