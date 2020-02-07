#include "Input.h"
#include "resource.h"
#include <SDL_syswm.h>
#include <string>
#include <codecvt>
#include "Game.h"

//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019

void Input::OnMouseButtonDown(SDL_Event & e)
{
	//if the event is a mouse button down 
	if (e.type==SDL_MOUSEBUTTONDOWN)
	{
		//and the button that is pressed is the left one then set the mouse button state to true
		if (e.button.button == SDL_BUTTON_LEFT) {
			M_MouseButtonStates[MOUSE_BUTTON_LEFT] = true;
		}
		//and the button that is pressed is the middle one then set the mouse button state to true
		if (e.button.button == SDL_BUTTON_MIDDLE) {
			M_MouseButtonStates[MOUSE_BUTTON_MIDDLE] = true;
		}
		//and the button that is pressed is the right one then set the mouse button state to true
		if (e.button.button == SDL_BUTTON_RIGHT) {
			M_MouseButtonStates[MOUSE_BUTTON_RIGHT] = true;
		}
		//set the mouse positon to the place that the user clicked the button
		M_MousePosition.X = e.button.x;
		M_MousePosition.Y = e.button.y;





	}
}

void Input::OnMouseButtonUp(SDL_Event& e)
{
	//if the event is a a mouse button up 
	if (e.type == SDL_MOUSEBUTTONUP)
	{
		//and the button that is let go is the left one then set the mouse button state to false 
		if (e.button.button == SDL_BUTTON_LEFT) {
			M_MouseButtonStates[MOUSE_BUTTON_LEFT] = false;
		}
		//and the button that is let go  is the middle one then set the mouse button state to false 
		if (e.button.button == SDL_BUTTON_MIDDLE) {
			M_MouseButtonStates[MOUSE_BUTTON_MIDDLE] = false;
		}
		//and the button that is let go  is the rigt one then set the mouse button state to false 
		if (e.button.button == SDL_BUTTON_RIGHT) {
			M_MouseButtonStates[MOUSE_BUTTON_RIGHT] = false;
		}
		//set the mouse positon to the place that the user let go of  the button
		M_MousePosition.X = e.button.x;
		M_MousePosition.Y = e.button.y;





	}
}
	


void Input::OnMouseButtonMove(SDL_Event& e)
{
	//if the mouse is moving and the left buttton is presses then set the mouse positon (x or y) to the coresponding mouse moiton postion 
	if (e.type==SDL_MOUSEMOTION&& e.motion.state==SDL_BUTTON_LMASK) {
		M_MousePosition.X = e.motion.x;

		M_MousePosition.Y = e.motion.y;
	}
	//if the mouse is moving and the right buttton is presses then set the mouse positon (x or y) to the coresponding mouse moiton postion 
	if (e.type == SDL_MOUSEMOTION&& e.motion.state == SDL_BUTTON_RMASK) {
		M_MousePosition.X = e.motion.x;

		M_MousePosition.Y = e.motion.y;
	}
}

void Input::OnSystemEvents(SDL_Event& e, Game* g)
{
	WPARAM wp = e.syswm.msg->msg.win.wParam;

	//this part gets the current files name via its path 
	//this part gets the entire path of the application 
	TCHAR AppFileName[MAX_PATH];
	GetModuleFileName(NULL, AppFileName, MAX_PATH);
	TCHAR * t1 = AppFileName;
	std::wstring strAppName(t1);
	//this part extracts the files name from the path of the application
	std::string t2;
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	t2 = converter.to_bytes(strAppName);
	t2 = t2.substr(t2.rfind("\\") + 1);
	t2 = t2.substr(0, t2.size() - 4);
	//this part gets the compiled sdl version of the application
	SDL_version compiled;
	SDL_GetVersion(&compiled);
	std::string  sdlver;
	sdlver = std::to_string(compiled.major);
	//this part adds the sdl version and also the file name to a string
	std::string test2;
	test2 = "program name: " + t2 + " running on sdl version:  " + sdlver;
	//this part converts the string to a wstring so that it could be converted to lpcwstr so that it can be displayed on the message box ,this is used for the message box content
	int len;
	int slength = (int)test2.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, test2.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, test2.c_str(), slength, buf, len);
	std::wstring r(buf);
	std::wstring test1;
	test1 = r;

	std::string test3;
	test3 = t2;
	//this part converts the string to a wstring so that it could be converted to lpcwstr so that it can be displayed on the message box, THIS IS USED FOR THE MESSAGE BOX HEADER
	len;
	slength = (int)test3.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, test3.c_str(), slength, 0, 0);
	buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, test3.c_str(), slength, buf, len);
	std::wstring r1(buf);
	std::wstring test4;
	test4 = r1;

	//for some reason it is only able to get the resource symbol values not the id

	//SDL_Log(abc.c_str());
	switch (wp)
	{
		//40007- NEW WINDOW
		//40002- QUIT-DONE
		//40004- ABOUT SDL 2
		//40006- CIRCLE
		//40005- RECTANGLE

		//QUITS
	case 40002:
		SDL_Log("test");
		//gameover=true
		g->SetGameState(true);
		break;
	
		//ABOUT SDL 2
	case 40003:
		//need to get the owner of the window its the first parameter 
		//second is the text in the text box 
		//third is the title 
		//last is the type of the message box 


		MessageBox(NULL, test1.c_str(), test4.c_str(), MB_OK);
		break;
		//restart game 
	case 40009:
		g->ResetGame();
		break;
		//easy
	case 40004:
		g->ChangeDifficulty(1);
		break;
		//hard
	case 40006:
		g->ChangeDifficulty(2);
		break;
		//medium
	case 40005:
		g->ChangeDifficulty(3);
		break;

	default:
		break;
	}
}

Input::Input()
{//this part sets the mosue positon and also goes through each button state and sets then to false 
	isGameOver = false;
	for (int i = 0; i < 7; ++i) {
		M_MouseButtonStates[i] = false;
	}
	M_MousePosition = Vector2(0, 0);
	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
}

void Input::UpdateInput(Game* game)
{
	SDL_Event e;
	//this part goes through each type of possible event, if they are true it will then run its coresponding function and pass the events value
	while (SDL_PollEvent(&e)) {
		switch (e.type)
		{
		case SDL_SYSWMEVENT:
			OnSystemEvents(e, game);
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonDown(e);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonUp(e);
			break;
		case SDL_MOUSEMOTION:
			OnMouseButtonMove(e);
			break;		
		case SDL_KEYDOWN:
			if (e.button.button == SDL_SCANCODE_ESCAPE)
			{
				isGameOver = true;
			}
			M_keyboardState = SDL_GetKeyboardState(NULL);
			if (e.key.repeat == 0)
			{
				try
				{
					if (e.key.keysym.sym<321)
					{
						m_keyboardPressState[e.key.keysym.sym] = 1;
					}
					
				}
				catch (const std::exception&)
				{
					SDL_Log("not valid key pressed");
				}
				
			}
			break;
		case SDL_KEYUP:
			M_keyboardState = SDL_GetKeyboardState(NULL);
			if (e.key.keysym.sym<321)
			{
				m_keyboardPressState[e.key.keysym.sym] = 2;
			}
			
			break;
		case SDL_QUIT:
			isGameOver = true;
			break;

		}


	}

}

bool Input::IsMouseButtonDown(MouseInputs button)
{
	//if the mouse button is down then set its value to true
	if (M_MouseButtonStates[button]) {
		return true;
	}
	return false;
}

bool Input::IsMouseButtonUp(MouseInputs button)
{
	//if the mouse button is up then set its value to false 
	if (M_MouseButtonStates[button]) {
		return false;
	}
	return true;
}

bool Input::IsKeyDown(SDL_Scancode key)
{
	// if a key is down then set the keys value to true
	if (M_keyboardState != nullptr) {
		if (M_keyboardState[key])
		{
			return true;
		}
	}
	return false;
}

bool Input::IsKeyUp(SDL_Scancode key)
{// if a key is up then set the keys value to false 
	if (M_keyboardState != nullptr) {
		if (M_keyboardState[key] )
		{
			return false;
		}
	}
	return true;
}

Vector2 Input::GetMousePos()
{
	return Vector2();
}


Input::~Input()
{
}

bool Input::wasMouseButtonPressed(MouseInputs button)
{
	if (m_MouseClickStates[button] == 1) {
		return true;
	}

	return false;
}

bool Input::wasMouseButtonReleased(MouseInputs button)
{
	if (m_MouseClickStates[button] == 2) {
		return true;
	}
	return false;
}

void Input::SetClickStateFalse(MouseInputs button)
{
	m_MouseClickStates[button] = 0;
}

bool Input::wasKeyPressed(SDL_Keycode key)
{
	if (m_keyboardPressState[key] == 1) {
		return true;
	}
	return false;
}

bool Input::wasKeyReleased(SDL_Keycode key)
{
	if (m_keyboardPressState[key] == 2) {
		return true;
	}
	return false;
}

void Input::SetKeyboardStateFalse(SDL_Keycode key)
{
	m_keyboardPressState[key] = 0;
}

bool Input::GetGameOver()
{
	return isGameOver;
}
