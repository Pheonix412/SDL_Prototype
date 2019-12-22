#include "PlayerSpaceShip.h"

//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019

PlayerSpaceShip::PlayerSpaceShip()
{
	//on construction of the player it sets their texture to a nullptr
	M_Texture = nullptr;
	std::cout << "playerconstructor" << std::endl;
}

PlayerSpaceShip::PlayerSpaceShip(Texture * texture, Vector2 position)
{
	//this part initalizes the players position,texture,velocity and also acceleration.
	M_Position = position;
	M_Texture = texture;
	M_Velocity = Vector2(0, 0);
	M_Acceleration = Vector2(0, 0);
	maxvelocity = 10.00f;
}

void PlayerSpaceShip::AddPlayerForce(Vector2 force)
{
	//this part increases the players acceleration in a direction by adding the players force to their acceleration 

	if (M_Acceleration.X<4 ||M_Acceleration.Y<4)
	{
		M_Acceleration += force;
	}
	
}

void PlayerSpaceShip::ReducePlayerForce(Vector2 force)
{

	if (M_Acceleration.X>-10 || M_Acceleration.Y>-10)
	{
		M_Acceleration += force;
	}

}

void PlayerSpaceShip::Draw(SDL_Renderer * renderer)
{
	//this part points to the draw function in the texture class and draws te player on the screen 
	M_Texture->Draw(renderer, M_Position.X, M_Position.Y);
	for (int i = 0; i < m_bullets.size(); ++i)
	{
		m_bullets[i]->Draw(renderer);
	}
}

void PlayerSpaceShip::Update(float delraTime)
{
	//this part updates the players posution and also their velocity
	
	//M_Acceleration = M_Acceleration + Vector2(M_Velocity *-0.5f);
	M_Velocity += M_Acceleration *delraTime;
		M_Position += M_Velocity*delraTime;
		//float speed = M_Velocity.magnitude();
	//}
		//if (speed<=maxvelocity)
		//{
		//	M_Velocity.NormalizedVector();
		//	M_Velocity = M_Velocity*maxvelocity;
		//}
		//SDL_Log("velocty %f, %f", M_Velocity.X, M_Velocity.Y);
		for (int i = 0; i < m_bullets.size(); ++i)
		{
			m_bullets[i]->Update(delraTime);
		}
		//M_Acceleration = Vector2(0, 0);
	
}

void PlayerSpaceShip::UserInput1()
{
}

void PlayerSpaceShip::HandleUserInput(Input * input)
{
	//this part handles the users input when they press a key down the keyboard, when they press a button down it will add to the players force in the coresponding direction
	if (input->IsKeyDown(SDL_SCANCODE_W))
	{
		ReducePlayerForce(Vector2(0, -2));
	}


	if (input->IsKeyDown(SDL_SCANCODE_S))
	{
		AddPlayerForce(Vector2(0, 2));
	}


	if (input->IsKeyDown(SDL_SCANCODE_A))
	{
		
		AddPlayerForce(Vector2(-10, 0));
	}


	if (input->IsKeyDown(SDL_SCANCODE_D))
	{
		//if (M_Position.X <= 200 && M_Velocity.X>=0)
		//{
			AddPlayerForce(Vector2(10, 0));
		//}
		
	}
	if (input->IsKeyUp(SDL_SCANCODE_D))
	{
		//if (M_Position.X <= 200 && M_Velocity.X>=0)
		//{
	//	AddPlayerForce(Vector2(10, 0));
		//}
		M_Acceleration = Vector2(0, 0);
	}
	if (input->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		SDL_Log("SpacePressed");

		//M_GameObjects[0].
		//int X1 = (*M_GameObjects[0]).M_Position.X;
		//int Y1 = (*M_GameObjects[0]).M_Position.Y;
		//M_Position1.X = (X1 + 10);
		//M_Position1.Y = (Y1 - 40);
		//GameObject*playerC = new Bullet1(m_bullets, M_Position1);
		//M_GameObjects.push_back(playerC);


	}
	
}

void PlayerSpaceShip::HandleUserInput1(Input * input, Texture * playerBullets)
{
	//this part handles the users input when they press a key down the keyboard, when they press a button down it will add to the players force in the coresponding direction
	if (input->IsKeyDown(SDL_SCANCODE_W))
	{
		ReducePlayerForce(Vector2(0, -2));
	}


	if (input->IsKeyDown(SDL_SCANCODE_S))
	{
		AddPlayerForce(Vector2(0, 2));
	}


	if (input->IsKeyDown(SDL_SCANCODE_A))
	{

		AddPlayerForce(Vector2(-1, 0));
	}


	if (input->IsKeyDown(SDL_SCANCODE_D))
	{
		//if (M_Position.X <= 200 && M_Velocity.X>=0)
		//{
		AddPlayerForce(Vector2(1, 0));
		

	}
	if (input->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		SDL_Log("SpacePressed");

		
 		int X1 = (M_Position.X+10);
		int Y1 = (M_Position.Y-40);
		
		M_Position2.X = X1 ;
		M_Position2.Y = Y1;
		Bullet1*playerC = new Bullet1(playerBullets, M_Position2);
		m_bullets.push_back(playerC);


	}
}


PlayerSpaceShip::~PlayerSpaceShip()
{
	std::cout << "player destructor" << std::endl;

}
