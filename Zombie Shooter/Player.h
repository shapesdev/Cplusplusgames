#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
public:
	Player();

	void Spawn(IntRect arena, Vector2f resolution, int tileSize);
	void ResetPlayerStats();
	bool Hit(Time timeHit);

	Time GetLastHitTime();
	FloatRect GetPosition();
	Vector2f GetCenter();
	float GetRotation();
	Sprite GetSprite();
	
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void StopLeft();
	void StopRight();
	void StopUp();
	void StopDown();

	void Update(float elapsedTime, Vector2i mousePosition);
	void UpgradeSpeed();
	void UpgradeHealth();
	void IncreaseHealthLevel(int amount);

	int GetHealth();

private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	Vector2f position;

	Sprite sprite;
	Texture texture;

	Vector2f resolution;
	IntRect arena;
	int tileSize;

	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;

	int health;
	int maxHealth;
	Time lastHit;
	float speed;
};

