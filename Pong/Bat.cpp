#include "Bat.h"


Bat::Bat(float startX, float startY) {
	position.x = startX;
	position.y = startY;

	shape.setSize(sf::Vector2f(50, 5));
	shape.setPosition(position);
}

FloatRect Bat::GetPosition()
{
	return shape.getGlobalBounds();
}
RectangleShape Bat::GetShape()
{
	return shape;
}
void Bat::MoveLeft()
{
	movingLeft = true;
}
void Bat::MoveRight()
{
	movingRight = true;
}
void Bat::StopLeft()
{
	movingLeft = false;
}
void Bat::StopRight()
{
	movingRight = false;
}

void Bat::Update(Time dt) {
	if (movingLeft) {
		position.x -= speed * dt.asSeconds();
	}
	if (movingRight) {
		position.x += speed * dt.asSeconds();
	}

	shape.setPosition(position);
}