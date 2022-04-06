#include "Pickup.h"
#include "TextureHolder.h"
#include <iostream>

Pickup::Pickup(int type) {
	m_Type = type;

	if (m_Type == 1) {
		m_Sprite = Sprite(TextureHolder::GetTexture("Graphics/health_pickup.png"));
		m_Value = HEALTH_START_VALUE;
	}
	else {
		m_Sprite = Sprite(TextureHolder::GetTexture("Graphics/ammo_pickup.png"));
		m_Value = AMMO_START_VALUE;
	}

	m_Sprite.setOrigin(25, 25);

	m_SecondsToLive = START_SECONDS_TO_LIVE;
	m_SecondsToWait = START_WAIT_TIME;
}

void Pickup::SetArena(IntRect arena) {
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;

	Spawn();
}

void Pickup::Spawn() {
	srand((int)time(0) / m_Type);
	int x = (rand() % m_Arena.width);
	srand((int)time(0) * m_Type);
	int y = (rand() % m_Arena.height);

	m_SecondsSinceSpawn = 0;
	m_Spawned = true;

	std::cout << x << "/" << y;
	m_Sprite.setPosition(x, y);
}

FloatRect Pickup::GetPosition() {
	return m_Sprite.getGlobalBounds();
}

Sprite Pickup::GetSprite() {
	return m_Sprite;
}

bool Pickup::IsSpawned() {
	return m_Spawned;
}

int Pickup::GotIt() {
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
	return m_Value;
}

void Pickup::Update(float elapsedTime) {
	if (m_Spawned) {
		m_SecondsSinceSpawn += elapsedTime;
	}
	else {
		m_SecondsSinceDeSpawn += elapsedTime;
	}

	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned) {
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}

	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned) {
		Spawn();
	}
}

void Pickup::Upgrade() {
	if (m_Type == 1) {
		m_Value += (HEALTH_START_VALUE * .5);
	}
	else {
		m_Value += (AMMO_START_VALUE * .5);
	}
	m_SecondsToLive += (START_SECONDS_TO_LIVE / 10);
	m_SecondsToWait -= (START_WAIT_TIME / 10);
}