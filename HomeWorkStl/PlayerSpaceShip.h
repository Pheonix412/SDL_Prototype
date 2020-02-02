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
	//this creats and object of the bullet
	
	//this holda the position of player space shi[
	Vector2 M_Position1;
	//this holds the postion of the bulet 
	Vector2 M_Position2;
	Vector2 m_colPOS;
	float maxVelocity;

	//holds how long its been since a bullet has been made
	unsigned int LastUpadateTimer;
	
	AABB* m_Collider;
	int m_colWidth;
	int m_colHeight;
	bool m_isTouchingGround;
	float m_MaxVelocity;
	float playerdecleration;
	SDL_Renderer* m_sdlRenderer;
	Animation* m_animation;
	Audio* audio;
	int m_playerDir;

public:
	//this is the space ship constructor 
	PlayerSpaceShip();
	PlayerSpaceShip(SDL_Renderer* renderer, Vector2 position, int colWidth, int colHeight);

	void AnimationLogic(Input* input);
	// Animtion Functions
	void IdleAnimation();
	void RunAnimation(bool flip = false);
	//this is a bullet pointer
	Bullet1* m_bullet;
	//this is a overloaded constructor of the space ship
//this function adds force to the player 
	void AddPlayerForce(Vector2 force);
	//this function reduces force to the player 
	void ReducePlayerForce(Vector2 force);
	//this function draws the plater 
	float GetPlayerY();
	float GetPlayerX();
	//fix this....
	AABB* GetCollider();

	Vector2 GetPlayerPos();

	void ToggleGorund(bool toggle);
	void Draw(SDL_Renderer* renderer);
	//this function updates the player 
	void Update(float deltaTime);
	//this function updates the users input
	void UserInput1();
	//these functions handle the users input 
	void HandleUserInput1(Input* input);
	//this is the space ship destructor
	~PlayerSpaceShip();
};

