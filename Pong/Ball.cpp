#include "Ball.h"

Ball::Ball(float startX, float startY) {
	position.x = startX;
	position.y = startY;

	shape.setSize(sf::Vector2f(10, 10));
	shape.setPosition(position);
}

FloatRect Ball::GetPosition()
{
	return shape.getGlobalBounds();
}
RectangleShape Ball::GetShape()
{
	return shape;
}
float Ball::GetXVelocity()
{
	return directionX;
}

void Ball::ReboundSides() {
	directionX = -directionX;
}

void Ball::ReboundBatOrTop() {
	directionY = -directionY;
}

void Ball::ReboundBottom() {
	position.y = 0;
	position.x = 500;
	directionY = -directionY;
}

void Ball::Update(Time dt) {
	position.x += directionX * speed * dt.asSeconds();
	position.y += directionY * speed * dt.asSeconds();

	shape.setPosition(position);
}