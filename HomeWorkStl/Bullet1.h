#pragma once
#include"GameObject.h"
class Bullet1 : public GameObject
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
private:
	//this is the varoables for velocity and accleration for the bullets
	Vector2 M_Velocity;
	Vector2 M_Acceleration;
	AABB* m_Collider;
public:
	//bullet constructor and overloaded constructor
	Bullet1();
	Bullet1(SDL_Renderer * renderer, Vector2 position, int colWidth, int colHeight, int speed);
	//this function draws the bullet
	void Draw(SDL_Renderer* renderer);
	//this function updates the bullet
	void Update(float deltaTime);
	//get bullet collider for collision detection
	AABB* GetCollider();

	//this is the destructor of the bullet
	~Bullet1();
};

