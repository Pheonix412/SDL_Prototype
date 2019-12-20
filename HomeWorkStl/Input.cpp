#include "Input.h"



void Input::OnMouseButtonDown(SDL_Event & e)
{
	if (e.type==SDL_MOUSEBUTTONDOWN)
	{

		if (e.button.button == SDL_BUTTON_LEFT) {
			M_MouseButtonStates[MOUSE_BUTTON_LEFT] = true;
		}
		if (e.button.button == SDL_BUTTON_MIDDLE) {
			M_MouseButtonStates[MOUSE_BUTTON_MIDDLE] = true;
		}
		if (e.button.button == SDL_BUTTON_RIGHT) {
			M_MouseButtonStates[MOUSE_BUTTON_RIGHT] = true;
		}
		M_MousePosition.X = e.button.x;
		M_MousePosition.Y = e.button.y;





	}
}

void Input::OnMouseButtonUp(SDL_Event & e)
{
	if (e.type == SDL_MOUSEBUTTONUP)
	{

		if (e.button.button == SDL_BUTTON_LEFT) {
			M_MouseButtonStates[MOUSE_BUTTON_LEFT] = false;
		}
		if (e.button.button == SDL_BUTTON_MIDDLE) {
			M_MouseButtonStates[MOUSE_BUTTON_MIDDLE] = false;
		}
		if (e.button.button == SDL_BUTTON_RIGHT) {
			M_MouseButtonStates[MOUSE_BUTTON_RIGHT] = false;
		}
		M_MousePosition.X = e.button.x;
		M_MousePosition.Y = e.button.y;





	}
}
	


void Input::OnMouseButtonMove(SDL_Event & e)
{
	if (e.type==SDL_MOUSEMOTION&& e.motion.state==SDL_BUTTON_LMASK) {
		M_MousePosition.X = e.motion.x;

		M_MousePosition.Y = e.motion.y;
	}
	if (e.type == SDL_MOUSEMOTION&& e.motion.state == SDL_BUTTON_RMASK) {
		M_MousePosition.X = e.motion.x;

		M_MousePosition.Y = e.motion.y;
	}
}

Input::Input()
{
	for (int i = 0; i < 7; ++i) {
		M_MouseButtonStates[i] = false;
	}
	M_MousePosition = Vector2(0, 0);
}

void Input::UpdateInput()
{
	SDL_Event e;
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
	if (M_MouseButtonStates[button]) {
		return true;
	}
	return false;
}

bool Input::IsMouseButtonUp(MouseInputs button)
{
	if (M_MouseButtonStates[button]) {
		return false;
	}
	return true;
}

bool Input::IsKeyDown(SDL_Scancode key)
{
	if (M_keyboardState != nullptr) {
		if (M_keyboardState[key]==true)
		{
			return true;
		}
	}
	return false;
}

bool Input::IsKeyUp(SDL_Scancode key)
{
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
