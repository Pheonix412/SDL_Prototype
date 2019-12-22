#include "Input.h"

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

void Input::OnMouseButtonUp(SDL_Event & e)
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
	


void Input::OnMouseButtonMove(SDL_Event & e)
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

Input::Input()
{//this part sets the mosue positon and also goes through each button state and sets then to false 
	for (int i = 0; i < 7; ++i) {
		M_MouseButtonStates[i] = false;
	}
	M_MousePosition = Vector2(0, 0);
}

void Input::UpdateInput()
{
	SDL_Event e;
	//this part goes through each type of possible event, if they are true it will then run its coresponding function and pass the events value
	while (SDL_PollEvent(&e)) {
		switch (e.type)
		{
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
			M_keyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYUP:
			M_keyboardState = SDL_GetKeyboardState(NULL);
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
		if (M_keyboardState[key]==true)
		{
			return true;
		}
	}
	return false;
}

bool Input::IsKeyUp(SDL_Scancode key)
{// if a key is up then set the keys value to false 
	if (M_keyboardState != nullptr) {
		if (M_keyboardState[key] == false)
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
