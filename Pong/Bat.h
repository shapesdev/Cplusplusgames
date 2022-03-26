#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
public:
	Bat(float startX, float startY);

	FloatRect GetPosition();
	RectangleShape GetShape();

	void MoveLeft();
	void MoveRight();
	void StopLeft();
	void StopRight();
	void Update(Time dt);

private:
	Vector2f position;
	RectangleShape shape;
	float speed = 1000.0f;
	bool movingRight = false;
	bool movingLeft = false;
};

