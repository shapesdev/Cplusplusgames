#include "Player.h"
#include "TextureHolder.h"

Player::Player() {
	speed = START_SPEED;
	health = START_HEALTH;
	maxHealth = START_HEALTH;

	sprite = Sprite(TextureHolder::GetTexture("Graphics/player.png"));
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

void Player::MoveLeft() {
	leftPressed = true;
}

void Player::MoveRight() {
	rightPressed = true;
}

void Player::MoveDown() {
	downPressed = true;
}

void Player::MoveUp() {
	upPressed = true;
}

void Player::StopLeft() {
	leftPressed = false;
}

void Player::StopRight() {
	rightPressed = false;
}

void Player::StopDown() {
	downPressed = false;
}

void Player::StopUp() {
	upPressed = false;
}

void Player::Update(float elapsedTime, Vector2i mousePosition) {
	if (upPressed) {
		position.y -= speed * elapsedTime;
	}
	if (downPressed) {
		position.y += speed * elapsedTime;
	}
	if (leftPressed) {
		position.x -= speed * elapsedTime;
	}
	if (rightPressed) {
		position.x += speed * elapsedTime;
	}

	sprite.setPosition(position);

	// Keep player in arena area
	if (position.x > arena.width - tileSize) {
		position.x = arena.width - tileSize;
	}
	if (position.x < arena.left + tileSize) {
		position.x = arena.left + tileSize;
	}
	if (position.y > arena.height - tileSize) {
		position.y = arena.height - tileSize;
	}
	if (position.y < arena.top + tileSize) {
		position.y = arena.top + tileSize;
	}

	float angle = (atan2(mousePosition.y - resolution.y / 2, mousePosition.x - resolution.x / 2) * 180) / 3.141;
	sprite.setRotation(angle);
}

void Player::UpgradeSpeed() {
	speed *= (START_SPEED * .2);
}

void Player::UpgradeHealth() {
	health *= (START_HEALTH * .2);
}

void Player::IncreaseHealthLevel(int amount) {
	health += amount;

	if (health > maxHealth) {
		health = maxHealth;
	}
}