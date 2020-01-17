#include "Game.h"
#include <iostream>
#include <string>
#include "resource1.h"
#include <windows.h>

//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
//credit to https://patrickdearteaga.com for the music
Game::Game()
{
	//please follow he guides in class for a more detailed description of this class 
	//initalizes the window and the renderer
	SdlWindow = nullptr;
	SdlRenderer = nullptr;
	LastUpadateTimer = SDL_GetTicks();
	//checks if sdl is initalized if it isnt  then end the game , else if it has then run the game 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		IsTheGameOver = true;

		std::cout << "error initalizing " << std::endl;
	}
	else
	{
		IsTheGameOver = false;
		//check if SDL_TTF was initalized
		if (TTF_Init() == -1) {
			SDL_Log("Initialized SDL_ttf - Failed");
		}
		else {
			SDL_Log("Initialized SDL_ttf - Success");
		}
		std::cout << "inialized " << std::endl;
	}
}
bool Game::start() {
	//create the renderer
	SdlRenderer = SDL_CreateRenderer(SdlWindow, 0, -1);
	//if its not null
	if (SdlRenderer != nullptr) {
		//make an object of the input  class 
		UserInput = new Input();
		std::cout << "render created " << std::endl;
		//make an object of the texture class
		playerBullets = new Texture();
		//laods the player bullets texture 
		playerBullets->LoadImgFromFile("../assets/B1.bmp", SdlRenderer);
		
		//this part creates another obejct of the texture class , it then loads the bullets texture
		Texture* playerSpacetexture = new Texture();
		playerSpacetexture->LoadImgFromFile("../assets/SP1.bmp", SdlRenderer);
		//its then sets the postion of the bullet class 
		M_Position1.X = 380;
		M_Position1.Y = 400;
		//it then creates a new obejct of that class 
		playerSpaceS = new PlayerSpaceShip(playerSpacetexture, M_Position1);
		//then adds the obeject to the game obejcts list
		M_GameObjects.push_back(playerSpaceS);
	
		lastSpawn = SDL_GetTicks();

		LastUpadateTimer = SDL_GetTicks();

		//intalizing text texture
		m_textTexture = new Texture();
		//initalizing the font
		m_font = TTF_OpenFont("../assets/RobotoBold.ttf", 24);


		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

		return true;
	}
	else
	{
		std::cout << "render failed " << std::endl;
		return false;
	}
	


}
void Game::run(char* title, int width, int height, bool fullscreen) {
	int creationFlag = 0;
	//checks the type of window to be shown
	if (!fullscreen)
	{
		//sets the type of window to be shown
		creationFlag = SDL_WINDOW_SHOWN;
	}
	else
	{
		//sets the type of window to be shown
		creationFlag = SDL_WINDOW_FULLSCREEN;
	}
	//creates the window
	SdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, creationFlag);

	//if there is a window and start is being run then
	if (SdlWindow !=nullptr && start())
	{

		//this part finds the name of the current window and converts to to lpcwstr 
		std::string test;
		test = title;
		int len;
		int slength = (int)test.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, test.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, test.c_str(), slength, buf, len);
		std::wstring r(buf);
		// TEST SDL is the name of the window that the program will try to find. 
		std::wstring test1;
		test1 = r;
		LPCWSTR t1;
		t1 = test1.c_str();
		//this part finds the current window and loads and sets the menu 
		HWND happ = FindWindow(NULL, t1);
		HMENU hmenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU2));
		//this sets the menu to the window.
		SetMenu(happ, hmenu);

		std::cout << "created window" << std::endl;
		//checks if the game is not over 
		while (!IsTheGameOver)
		{
			//process the users input 
			processinput();
			//update the screen 
			update();
			//draw on the screen the obbejcts 
			draw();
		}



	}
	else
	{
		std::cout << "not created window" << std::endl;
		//if not then shutdown the game and destory the objects (including window and etc)
		shutdown();
		destroy();
	
	}


}

void Game::draw() {
	//this part sets the render colour and cleanrs the background
	SDL_SetRenderDrawColor(SdlRenderer, 47, 155, 228, 255);
	SDL_RenderClear(SdlRenderer);
	
	if (m_font != nullptr) {
		SDL_Color colour = { 255,255,255,255 };
		if (!m_textTexture->RenderText("Wave 1", m_font, SdlRenderer, colour)) {
			SDL_Log("Text rendered - Success");
		}
		m_textTexture->Draw(SdlRenderer, 10, 10);
	}
	//this part goes through each of the enemies and game obejcts and draws them
	for (int i = 0; i < M_GameObjects.size(); ++i)
	{
		M_GameObjects[i]->Draw(SdlRenderer);
	}
	for (int i = 0; i < M_EnemyObjects.size(); ++i)
	{
		M_EnemyObjects[i]->Draw(SdlRenderer);
	}
	SDL_RenderPresent(SdlRenderer);
}
void Game::destroy() {
//this destroys the window,renderer and also quits the game
	SDL_DestroyWindow(SdlWindow);
	SDL_DestroyRenderer(SdlRenderer);
	SDL_Quit();
}

void Game::processinput() {
	//m_player->Input();
	//this calls the update input function
	UserInput->UpdateInput(this);
	//if the user has  presses down the left mouse button
	if (UserInput->IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		SDL_Log("ifring");

	}
	//if the user has  let go of the left mouse button
	if (UserInput->IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
		//SDL_Log("did not press te left buttton");

	}
	//if the user has  presses down the right mouse button
	if (UserInput->IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		SDL_Log("ALT ifring");

	}
	//move this to the player class and when you press space in the player class it should spawn a bullet and be able to retrive the current position of the player as it is apart of the game object class
	/*if (UserInput->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		SDL_Log("SpacePressed");

	//M_GameObjects[0].
		int X1 = (*M_GameObjects[0]).M_Position.X;
		int Y1 = (*M_GameObjects[0]).M_Position.Y;
		M_Position1.X = (X1+10);
		M_Position1.Y = (Y1-40);
		GameObject*playerC = new Bullet1(playerBullets, M_Position1);
		M_GameObjects.push_back(playerC);
		

	}*/
	//this part goes through each game object and  handles the user input 
	for (int i = 0; i < M_GameObjects.size(); ++i)
	{
		M_GameObjects[i]->UserInput1();
		//M_GameObjects[i]->HandleUserInput(UserInput);
		M_GameObjects[i]->HandleUserInput1(UserInput, playerBullets);
	}
	//this part checks what type of event the user has done if they have done a quit event then end the game
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type==SDL_QUIT)
		{
			IsTheGameOver = true;
		}

	}

}
void Game::update() {
	//calculate delta time. 
	unsigned int ticks = SDL_GetTicks() - LastUpadateTimer;
	float deltaTime = ticks / 1000.0f;
	LastUpadateTimer = SDL_GetTicks();
	
	//this displays the delta time 
	//std::cout << "time" << deltaTime<< std::endl;

	//calculates the spawn timer
	unsigned int spawnTicks = SDL_GetTicks() - lastSpawn;
	float spawnTimer = spawnTicks / 1000.0f;

	//this displays the spawn timer 
	//std::cout << "Spawn Timer: " << spawnTimer<< std::endl;
	//this spawns the enemies if there is les than 10 of them
	if (spawnTimer>0.5 && enemycount<20) {
		enemycount++;
		M_EnemyTexture = new Texture();
		M_EnemyTexture->LoadImgFromFile("../assets/EnemyShipS.bmp", SdlRenderer);
		int rand_x = rand() % 700 + 10;
		int rand_y = rand() % 1 + 10;
		Enemies = new EnemyWave1(M_EnemyTexture, Vector2(rand_x, rand_y));
		M_EnemyObjects.push_back(Enemies);
		lastSpawn = SDL_GetTicks();
	}

//	ani->Update(deltaTime);
	//m_player->Update(deltaTime);
	
	//this goes through all of the enimies and game obejcts and updates them 
	for (int i = 0; i < M_GameObjects.size(); ++i)
	{
		M_GameObjects[i]->Update(deltaTime);
	}
	for (int i = 0; i < M_EnemyObjects.size(); ++i)
	{
		M_EnemyObjects[i]->Update(deltaTime);
		//M_EnemyObjects[i]->MoveToPlayer(deltaTime, playerSpaceS->GetPosition());

	}
}
void Game::shutdown() {
	Mix_CloseAudio();
}

Game::~Game()
{
}

void Game::SetGameState(bool status)
{
	IsTheGameOver = status;
}
