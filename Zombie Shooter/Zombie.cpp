#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

bool Zombie::IsAlive() {
	return m_Alive;
}

FloatRect Zombie::GetPosition() {
	return m_Sprite.getGlobalBounds();
}

Sprite Zombie::GetSprite() {
	return m_Sprite;
}

void Zombie::Spawn(float startX, float startY, int type, int seed) {
	switch (type) {
		case 0:
			m_Sprite = Sprite(TextureHolder::GetTexture("Graphics/bloater.png"));
			m_Speed = BLOATER_SPEED;
			m_Health = BLOATER_HEALTH;
			break;
		case 1:
			m_Sprite = Sprite(TextureHolder::GetTexture("Graphics/chaser.png"));
			m_Speed = CHASER_SPEED;
			m_Health = CHASE_HEALTH;
			break;
		case 2:
			m_Sprite = Sprite(TextureHolder::GetTexture("Graphics/crawler.png"));
			m_Speed = CRAWLER_SPEED;
			m_Health = CRAWLER_HEALTH;
			break;
	}

	srand((int)time(0) * seed);
	
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	modifier /= 100;
	m_Speed *= modifier;

	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setPosition(m_Position);
}

bool Zombie::Hit() {
	m_Health--;

	if (m_Health < 0) {
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture("Graphics/blood.png"));
		return true;
	}
	return false;
}

void Zombie::Update(float elapsedTime, Vector2f playerLocation) {
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	if (playerX > m_Position.x) {
		m_Position.x += m_Speed * elapsedTime;
	}
	if (playerY > m_Position.y) {
		m_Position.y += m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x) {
		m_Position.x -= m_Speed * elapsedTime;
	}
	if (playerY < m_Position.y) {
		m_Position.y -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);

	float angle = (atan2(playerY - m_Position.y, playerX - m_Position.x) * 180) / 3.141;

	m_Sprite.setRotation(angle);
}
