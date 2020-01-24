#pragma once
#include <SDL.h>
#include "Vector2.h"
class AABB
{
public:
	AABB();
	AABB(Vector2 position, int width, int height);

	//get the position of the bounding box
	const Vector2 GetPosition() const;

	//create a rectangle collision
	bool RectCollision(const AABB& rect);

	//update the AABB
	void Update(Vector2 position);

	//return the width and height of the bounding box
	const int GetWidth() const;
	const int GetHeight() const;
	~AABB();

	private:
		Vector2 m_position;
		int m_width;
		int m_height;

};

