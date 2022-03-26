#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
public:
	Ball(float startX, float startY);

	FloatRect GetPosition();
	RectangleShape GetShape();

	float GetXVelocity();
	void ReboundSides();
	void ReboundBatOrTop();
	void ReboundBottom();
	void Update(Time dt);

private:
	Vector2f position;
	RectangleShape shape;

	float speed = 300.0f;
	float directionX = .2f;
	float directionY = .2f;
};

