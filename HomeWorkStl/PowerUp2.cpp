#include "PowerUp2.h"
#include <random>


PowerUp2::PowerUp2()
{
    M_Texture = nullptr;
    m_Collider = nullptr;
}


PowerUp2::~PowerUp2()
{
    if (M_Texture != nullptr) {
        delete  M_Texture;
        M_Texture = nullptr;
    }
}

PowerUp2::PowerUp2(Texture * texture, Vector2 position, int colWidth, int colHeight, int speed)
{
    //this initalizes the enemies texture and position 
    M_Texture = texture;
    M_Position = position;
    //initalize collider
    m_Collider = new AABB(position, colWidth, colHeight);
    M_Speed = speed;
}

void PowerUp2::AddPlayerForce(Vector2 force)
{
    if (M_Acceleration.X<4 || M_Acceleration.Y<4)
    {
        M_Acceleration += force;
    }
}

void PowerUp2::ReducePlayerForce(Vector2 force)
{
    if (M_Acceleration.X>-10 || M_Acceleration.Y>-10)
    {
        M_Acceleration -= force;
    }
}

void PowerUp2::Draw(SDL_Renderer * renderer)
{
    M_Texture->Draw(renderer, M_Position.X, M_Position.Y);

    SDL_Rect rect = {
        m_Collider->GetPosition().X,
        m_Collider->GetPosition().Y,
        m_Collider->GetWidth(),
        m_Collider->GetHeight()
    };

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
    SDL_RenderDrawRect(renderer, &rect);
}

void PowerUp2::Update(float deltaTime)
{
    //this function increases the postion of the enemy when it updates 
    M_Position.X += (0 * deltaTime);
    M_Position.Y += (M_Speed * deltaTime);

    m_Collider->Update(M_Position);
}

AABB * PowerUp2::GetCollider()
{
    return m_Collider;
}
