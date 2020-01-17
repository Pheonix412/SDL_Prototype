#pragma once
#include <vector>
#include "GameObject.h"
#include"Bullet1.h"
#include <SDL_mixer.h>
class PlayerSpaceShip : public GameObject
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
private:
	//this holds the velocity and acceleration x and y variables 
	Vector2 M_Velocity;
	Vector2 M_Acceleration;
	//this creats and object of the bullet
	std::vector <Bullet1*> m_bullets;
	//this holda the position of player space shi[
	Vector2 M_Position1;
	//this holds the postion of the bulet 
	Vector2 M_Position2;
	float maxvelocity;
	//std::vector<GameObject*>M_GameObjects;
public:
	//this is the space ship constructor 
	PlayerSpaceShip();
	//this is a bullet pointer
	Bullet1* m_bullet;
	//this is a overloaded constructor of the space ship
	PlayerSpaceShip(Texture* texture, Vector2 position);
//this function adds force to the player 
	void AddPlayerForce(Vector2 force);
	//this function reduces force to the player 
	void ReducePlayerForce(Vector2 force);
	//this function draws the plater 
	void Draw(SDL_Renderer* renderer);
	//this function updates the player 
	void Update(float deltaTime);
	//this function updates the users input
	void UserInput1();
	//these functions handle the users input 
	void HandleUserInput(Input* input);
	void HandleUserInput1(Input* input, Texture* playerBullets);
	//this is the space ship destructor
	~PlayerSpaceShip();
};

