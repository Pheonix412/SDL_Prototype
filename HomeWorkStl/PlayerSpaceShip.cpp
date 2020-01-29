#include "PlayerSpaceShip.h"

//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019

PlayerSpaceShip::PlayerSpaceShip()
{
	//on construction of the player it sets their texture to a nullptr
	M_Texture = nullptr;
	std::cout << "playerconstructor" << std::endl;
	LastUpadateTimer = SDL_GetTicks();
	M_Velocity = Vector2(0, 0);
	M_Acceleration = Vector2(0, 0);
	m_MaxVelocity = 0.0f;
	playerdecleration = 0.0f;




	maxVelocity = 0.0f;
	m_Collider = new AABB();
	
	m_isTouchingGround = false;
}

PlayerSpaceShip::PlayerSpaceShip(Texture* texture, Vector2 position, int colWidth, int colHeight)
{
	//this part initalizes the players position,texture,velocity and also acceleration.
	M_Position = position;
	M_Texture = texture;
	M_Velocity = Vector2(0, 0);
	M_Acceleration = Vector2(0, 0);
	maxVelocity = 1000.0f;
	playerdecleration = 2000.0f;
	//maxVelocity = 500.0f;
	m_colWidth = colWidth;
	m_colHeight = colHeight;
	//setup collider
	m_isTouchingGround = false;
	m_Collider = new AABB(M_Position, m_colWidth, m_colHeight);
}

void PlayerSpaceShip::AddPlayerForce(Vector2 force)
{
	//this part increases the players acceleration in a direction by adding the players force to their acceleration 
		M_Acceleration += force;
}

void PlayerSpaceShip::ReducePlayerForce(Vector2 force)
{
		M_Acceleration -= force;
}

AABB * PlayerSpaceShip::GetCollider()
{
	return m_Collider;
}

Vector2 PlayerSpaceShip::GetPlayerPos()
{
	return M_Position;
}

void PlayerSpaceShip::ToggleGorund(bool toggle){
	//toggle isTouchingGround
	m_isTouchingGround = toggle;

}

void PlayerSpaceShip::Draw(SDL_Renderer* renderer)
{
	//this part points to the draw function in the texture class and draws te player on the screen 
	M_Texture->Draw(renderer, M_Position.X, M_Position.Y);

	//draw a box to visualise the collider
	SDL_Rect rect = {
		m_Collider->GetPosition().X,
		m_Collider->GetPosition().Y,
		m_Collider->GetWidth(),
		m_Collider->GetHeight()
	};

	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
	SDL_RenderDrawRect(renderer, &rect);

	for (int i = 0; i < m_bullets.size(); ++i)
	{

		m_bullets[i]->Draw(renderer);
	}
}

void PlayerSpaceShip::Update(float deltaTime)
{
	//this part updates the players posution and also their velocity
	
	//M_Acceleration = M_Acceleration + Vector2(M_Velocity *-0.5f);
		M_Velocity += M_Acceleration * deltaTime;
		float length = M_Velocity.magnitude();
		if (length >= maxVelocity) {
			M_Velocity.NormalizeVector();
			M_Velocity = M_Velocity*maxVelocity;
		}

		M_Position += M_Velocity * deltaTime;
		if (!m_isTouchingGround) {
			M_Position.Y += 500.0f*deltaTime;
		}

		m_Collider->Update(M_Position);
		M_Acceleration = Vector2(0, 0);
	
		//SDL_Log("velocty %f, %f", M_Velocity.X, M_Velocity.Y);
		for (int i = 0; i < m_bullets.size(); ++i)
		{
			m_bullets[i]->Update(deltaTime);
		}
		//M_Acceleration = Vector2(0, 0);
	
}

void PlayerSpaceShip::UserInput1()
{
}


void PlayerSpaceShip::HandleUserInput1(Input* input, Texture* playerBullets)
{
	//this part handles the users input when they press a key down the keyboard, when they press a button down it will add to the players force in the coresponding direction
	/*if (input->IsKeyDown(SDL_SCANCODE_W))
	{
		AddPlayerForce(Vector2(0, -1) * 2000);
	}

	if (input->IsKeyUp(SDL_SCANCODE_W))
	{
		if (M_Velocity.Y > 0) {
			ReducePlayerForce(Vector2(0, -1) * 1000);
		}
	}

	if (input->IsKeyDown(SDL_SCANCODE_S))
	{
		AddPlayerForce(Vector2(0, 1) * 2000);
	}

	if (input->IsKeyUp(SDL_SCANCODE_S))
	{
		if (M_Velocity.Y < 0) {
			ReducePlayerForce(Vector2(0, 1) * 1000);
		}
	}*/

	if (input->IsKeyDown(SDL_SCANCODE_A))
	{
		AddPlayerForce(Vector2(-1,0) * 2000.0f);
	}

	if (input->IsKeyUp(SDL_SCANCODE_A))
	{
		if (M_Velocity.X < 0) {
			ReducePlayerForce(Vector2(-2, 0) *playerdecleration);
		}
	}

	if (input->IsKeyDown(SDL_SCANCODE_D))
	{
		AddPlayerForce(Vector2(1, 0) * 2000.0f);
	}
	if (input->IsKeyUp(SDL_SCANCODE_D))
	{
		if (M_Velocity.X > 0) {
			ReducePlayerForce(Vector2(1, 0) * playerdecleration);
		}
	}
	if (input->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		SDL_Log("SpacePressed");
		unsigned int ticks = SDL_GetTicks() - LastUpadateTimer;
		float deltaTime = ticks / 1000.0f;
		//only allows a bullet to spawn after 0.2 seconds
		if(deltaTime >=0.2f){	
			int X1 = (M_Position.X + 10);
			int Y1 = (M_Position.Y - 40);
			LastUpadateTimer = SDL_GetTicks();
			M_Position2.X = X1;
			M_Position2.Y = Y1;
			Bullet1*playerC = new Bullet1(playerBullets, M_Position2);
			m_bullets.push_back(playerC);
			audio = new Audio();
			audio->PlaySFX("../assets/Shoot.wav");
		}
	}
}


PlayerSpaceShip::~PlayerSpaceShip()
{
	if (M_Texture != nullptr) {
		delete M_Texture;
		M_Texture = nullptr;
	}
	std::cout << "player destructor" << std::endl;

}
