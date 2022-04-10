#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Particle
{
public:
	Particle(Vector2f direction);
	
	void Update(float dt);
	void SetPosition(Vector2f position);
	Vector2f GetPosition();

private:
	Vector2f m_Position;
	Vector2f m_Velocity;
};

