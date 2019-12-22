#pragma once
#include"GameObject.h"
class Bullet1 : public GameObject
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
private:
	//this is the varoables for velocity and accleration for the bullets
	Vector2 M_Velocity;
	Vector2 M_Acceleration;
public:
	//bullet constructor and overloaded constructor
	Bullet1();
	Bullet1(Texture * texture, Vector2 position);
//this function adds force to the bullet
	void AddPlayerForce(Vector2 force);
	//this function reduces force to the bullet
	void ReducePlayerForce(Vector2 force);
	//this function draws the bullet
	void Draw(SDL_Renderer*renderer);
	//this function updates the bullet
	void Update(float delraTime);
	//this is the destructor of the bullet
	~Bullet1();
};

