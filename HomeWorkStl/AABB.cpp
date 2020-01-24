#include "AABB.h"



AABB::AABB(){
	m_position = Vector2(0, 0);
	m_width = 0;
	m_height = 0;
}

AABB::AABB(Vector2 position, int width, int height){
	m_position = position;
	m_width = width;
	m_height = height;
}

const Vector2 AABB::GetPosition() const{
	return m_position;
}

bool AABB::RectCollision(const AABB& rect){
	if (
		rect.GetPosition().X + rect.GetWidth() < m_position.X ||
		rect.GetPosition().X > m_width +m_position.X ||
		rect.GetPosition().Y + rect.GetHeight() < m_position.Y ||
		rect.GetPosition().Y > m_height + m_position.Y
		) {
		return false;
	}
	return true;
}

void AABB::Update(Vector2 position){
	m_position = position;
}


const int AABB::GetWidth() const {
	return m_width;
}

const int AABB::GetHeight() const {
	return m_height;
}

AABB::~AABB(){
}
