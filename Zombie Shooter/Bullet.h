#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
public:
	Bullet();

	void Stop();
	void Shoot(float startX, float startY, float xTarget, float yTarget);
	void Update(float elapsedTime);

	FloatRect GetPosition();
	bool IsInFlight();
	RectangleShape GetShape();

private:
	Vector2f m_Position;
	RectangleShape m_BulletShape;

	bool m_InFlight = false;

	float m_BulletSpeed = 1000;
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	float m_MaxX;
	float m_MaxY;
	float m_MinX;
	float m_MinY;
};

