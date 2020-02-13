#pragma once
#include"GameObject.h"
class PowerUp3 :public GameObject
{
private:
    //this is the varoables for velocity and accleration for the first wave of enemies 
    Vector2 M_Velocity;
    Vector2 M_Acceleration;
    AABB* m_Collider;
    int M_Speed;
public:
    PowerUp3();
    ~PowerUp3();
    PowerUp3(Texture* texture, Vector2 position, int colWidth, int colHeight, int speed);
    //this function adds force to the enemy 
    void AddPlayerForce(Vector2 force);
    //this function removes force from the enemy
    void ReducePlayerForce(Vector2 force);
    //this funcation draws the enemy
    void Draw(SDL_Renderer* renderer);
    //this function updates the enemy
    void Update(float deltaTime);
    //get enemy collider for collision detection
    AABB* GetCollider();
};

