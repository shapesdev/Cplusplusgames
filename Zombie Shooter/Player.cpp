#include "Player.h"

Player::Player() {
	speed = START_SPEED;
	health = START_HEALTH;
	maxHealth = START_HEALTH;

	texture.loadFromFile("Graphics/player.png");
	sprite.setTexture(texture);
	sprite.setOrigin(25, 25);
}

void Player::Spawn(IntRect arena, Vector2f resolution, int tileSize) {
	position.x = arena.width / 2;
	position.y = arena.height / 2;

	this->arena.left = arena.left;
	this->arena.width = arena.width;
	this->arena.top = arena.top;
	this->arena.height = arena.height;

	this->tileSize = tileSize;

	this->resolution.x = resolution.x;
	this->resolution.y = resolution.y;
}

void Player::ResetPlayerStats() {
	speed = START_SPEED;
	health = START_HEALTH;
	maxHealth = START_HEALTH;
}

Time Player::GetLastHitTime() {
	return lastHit;
}

bool Player::Hit(Time timeHit) {
	if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > 200) {
		lastHit = timeHit;
		health -= 10;
		return true;
	}
	else {
		return false;
	}
}

FloatRect Player::GetPosition() {
	return sprite.getGlobalBounds();
}

Vector2f Player::GetCenter() {
	return position;
}

float Player::GetRotation() {
	return sprite.getRotation();
}

Sprite Player::GetSprite() {
	return sprite;
}

int Player::GetHealth() {
	return health;
}

