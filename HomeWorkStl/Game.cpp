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
	isPlayerAlive = nullptr;
	Lives = 0;
	WaveNum = 0;
	LastUpadateTimer = SDL_GetTicks();
	//checks if sdl is initalized if it isnt  then end the game , else if it has then run the game 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0|| TTF_Init() == -1|| Mix_OpenAudio(192000,MIX_DEFAULT_FORMAT,2,4096)==-1) {
		IsTheGameOver = true;

		std::cout << "error initalizing " << std::endl;
	}
	else
	{
		IsTheGameOver = false;
		std::cout << "inialized " << std::endl;
	}
	audio = nullptr;
}
bool Game::start() {
	Lives = 3;
	WaveNum = 1;
	isPlayerAlive = true;
	//create the renderer
	SdlRenderer = SDL_CreateRenderer(SdlWindow, 0, -1);
	//if its not null
	if (SdlRenderer != nullptr) {
		//make an object of the input  class 
		UserInput = new Input();
	//	std::cout << "render created " << std::endl;
		//make an object of the texture class
		playerBullets = new Texture();
		//laods the player bullets texture 
		playerBullets->LoadImgFromFile("../assets/B1.bmp", SdlRenderer);
		
		audio = new Audio();

		audio->PlayBGMusic("../assets/IntergalacticOdyssey.ogg");
		m_textTexture = new Texture();
		m_font = TTF_OpenFont("../assets/RobotoBold.ttf", 24);
		//this part creates another obejct of the texture class , it then loads the bullets texture
		playerSpacetexture = new Texture();
		playerSpacetexture->LoadImgFromFile("../assets/SP1.bmp", SdlRenderer);
		//its then sets the postion of the bullet class 
		M_Position1.X = 710;
		M_Position1.Y = 700;
		//it then creates a new obejct of that class 
		playerSpaceS = new PlayerSpaceShip(playerSpacetexture, M_Position1,80,80);
		//then adds the obeject to the game obejcts list
		
		// problem with this so dont add it to the space ship class 
		//M_GameObjects.push_back(playerSpaceS);
	

		//intalizing text texture
		//m_textTexture = new Texture();
		//initalizing the font
		//m_font = TTF_OpenFont("../assets/RobotoBold.ttf", 24);

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
			//calculate delta time. 
			unsigned int ticks = SDL_GetTicks() - LastUpadateTimer;
			float deltaTime = ticks / 1000.0f;
			LastUpadateTimer = SDL_GetTicks();

			//process the users input 
			processinput();
			//update the screen 
			update(deltaTime);
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

	playerSpaceS->Draw(SdlRenderer);

	for (int i = 0; i < M_GameObjects.size(); ++i)
	{
		M_GameObjects[i]->Draw(SdlRenderer);
	}
	for (int i = 0; i < m_bullets.size(); ++i)
	{

		m_bullets[i]->Draw(SdlRenderer);
	}
	for (int i = 0; i < M_EnemyObjects.size(); ++i)
	{
		M_EnemyObjects[i]->Draw(SdlRenderer);
	}

	if (m_font != nullptr) {
		SDL_Color colour = { 255,255,255,255 };
		std::string wavenum1;
		wavenum1 = std::to_string((int)WaveNum);
		std::string livenum1;
		livenum1 = std::to_string((int)Lives);
		if (!m_textTexture->RenderText(( " Lives: " + livenum1).c_str(), m_font, SdlRenderer, colour)) {
			//SDL_Log("Text rendered - Success");
		}


		if (isPlayerAlive == false)
		{
			if (!m_textTexture->RenderText("Game over", m_font, SdlRenderer, colour)) {
				//SDL_Log("Text rendered - Success");
			}

		}
		m_textTexture->Draw(SdlRenderer, 10, 10);

	}

	SDL_RenderPresent(SdlRenderer);
}
void Game::destroy() {
//this destroys the window,renderer and also quits the game
	SDL_DestroyWindow(SdlWindow);
	SDL_DestroyRenderer(SdlRenderer);
	SDL_Quit();
}
void Game::PE_CollisionCheck(){
	//these should be both in the player space ship class

	// i have a feeling this is not needed as the player should be able to move freely within the space

	if (playerSpaceS->GetPlayerPos().Y >= (400-80)) {
		playerSpaceS->ToggleGorund(true);
	}
	else {
		playerSpaceS->ToggleGorund(false);
	}

	if (playerSpaceS->GetCollider()) {
		//check that we have collided with the individual enemy collisions
		for (auto itr = M_EnemyObjects.end(); itr != M_EnemyObjects.begin();) {
			--itr;
			//if the enemes collision is within the players collsion bounds then delete the enemy
			if ((*itr) != nullptr && playerSpaceS->GetCollider()->RectCollision(*(*itr)->GetCollider())) {
				//delete* itr;
				//*itr = nullptr;
				//itr = M_EnemyObjects.erase(itr);

			if (Lives > 0) {


				playerSpaceS->~PlayerSpaceShip();
				playerSpacetexture = new Texture();
				playerSpacetexture->LoadImgFromFile("../assets/SP1.bmp", SdlRenderer);
				playerSpaceS = new PlayerSpaceShip(playerSpacetexture, M_Position1, 80, 80);
					Lives--;
				}
				else if (Lives == 0)
				{
					playerSpaceS->~PlayerSpaceShip();
					SDL_Log("game over");

					isPlayerAlive = false;




				}












				SDL_Log("Enemy Deleted");
			}
		}
	}

}
void Game::processinput() {
	//m_player->Input();
	//this calls the update input function
	UserInput->UpdateInput(this);
	PE_CollisionCheck();
	playerSpaceS->HandleUserInput1(UserInput, playerBullets);
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

	if (UserInput->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		SDL_Log("SpacePressed");
		unsigned int BulletTicks = SDL_GetTicks() - LastBullet;
		float bulletTime = BulletTicks / 1000.0f;
		//only allows a bullet to spawn after 0.2 seconds
		if (bulletTime >= 0.2f) {

			int X1 = (playerSpaceS->GetPlayerX() + 10);
			int Y1 = (playerSpaceS->GetPlayerY() - 40);
			LastBullet = SDL_GetTicks();
			M_Position2.X = X1;
			M_Position2.Y = Y1;
			Bullet1*playerC = new Bullet1(playerBullets, M_Position2);
			m_bullets.push_back(playerC);
			audio = new Audio();
			audio->PlaySFX("../assets/Shoot.wav");
		}
	}
	//this part goes through each game object and  handles the user input 
	for (int i = 0; i < M_GameObjects.size(); ++i)
	{
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
void Game::update(float deltaTime) {
	
	playerSpaceS->Update(deltaTime);
	//this displays the delta time 
	//std::cout << "time" << deltaTime<< std::endl;

	//calculate game timer
	unsigned int gameTicks = SDL_GetTicks();
	float GameTime = gameTicks / 1000.0f;

	//calculates the spawn timer
	unsigned int spawnTicksL = SDL_GetTicks() - lastSpawnL;
	float spawnTimerL = spawnTicksL / 1000.0f;
	 
	unsigned int spawnTicksM = SDL_GetTicks() - lastSpawnM;
	float spawnTimerM = spawnTicksM / 1000.0f;

	unsigned int spawnTicksS = SDL_GetTicks() - lastSpawnS;
	float spawnTimerS = spawnTicksS / 1000.0f;

	if (spawnTimerL>0.8) {
		enemycount++;
		M_EnemyTexture = new Texture();
		M_EnemyTexture->LoadImgFromFile("../assets/EnemyShipL.bmp", SdlRenderer);
		int rand_x = rand() % 1400 + 10;
		int rand_y = rand() % 1 + 10;
		Enemies = new EnemyWave1(M_EnemyTexture, Vector2(rand_x, rand_y),60,41,80);
		M_EnemyObjects.push_back(Enemies);
		lastSpawnL = SDL_GetTicks();
	}
	if (spawnTimerM>2&&GameTime>60) {
		enemycount++;
		M_EnemyTexture = new Texture();
		M_EnemyTexture->LoadImgFromFile("../assets/EnemyShipM.bmp", SdlRenderer);
		int rand_x = rand() % 1400 + 10;
		int rand_y = rand() % 1 + 10;
		Enemies = new EnemyWave1(M_EnemyTexture, Vector2(rand_x, rand_y), 41, 41,120);
		M_EnemyObjects.push_back(Enemies);
		lastSpawnM = SDL_GetTicks();
	}
	if (spawnTimerS>1&&GameTime>120) {
		enemycount++;
		M_EnemyTexture = new Texture();
		M_EnemyTexture->LoadImgFromFile("../assets/EnemyShipS.bmp", SdlRenderer);
		int rand_x = rand() % 1400 + 10;
		int rand_y = rand() % 1 + 10;
		Enemies = new EnemyWave1(M_EnemyTexture, Vector2(rand_x, rand_y), 40, 35,200);
		M_EnemyObjects.push_back(Enemies);
		lastSpawnS = SDL_GetTicks();
	}
	
	//this goes through all of the enimies and game obejcts and updates them 
	for (int i = 0; i < M_GameObjects.size(); ++i)
	{
		M_GameObjects[i]->Update(deltaTime);
	}
	
	for (int i = 0; i < M_EnemyObjects.size(); ++i)
	{
		M_EnemyObjects[i]->Update(deltaTime);
	}
	for (int i = 0; i < m_bullets.size(); ++i)
	{
		m_bullets[i]->Update(deltaTime);
	}
}
void Game::shutdown() {
	Mix_Quit();
}
Game::~Game()
{
}
void Game::SetGameState(bool status)
{
	IsTheGameOver = status;
}
