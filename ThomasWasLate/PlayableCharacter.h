#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter {
public:
	void Spawn(Vector2f startPosition, float gravity);
	void Update(float elapsedTime);

	bool virtual HandleInput() = 0;

	FloatRect GetPosition();
	FloatRect GetFeet();
	FloatRect GetHead();
	FloatRect GetRight();
	FloatRect GetLeft();

	Sprite GetSprite();

	void StopFalling(float position);
	void StopRight(float position);
	void StopLeft(float position);
	void StopJump();

	Vector2f GetCenter();

protected:
	Sprite m_Sprite;

	float m_JumpDuration;
	float m_TimeThisJump;

	bool m_IsJumping;
	bool m_IsFalling;
	bool m_JustJumped = false;

	bool m_LeftPressed;
	bool m_RightPressed;

private:
	float m_Gravity;
	float m_Speed = 400;

	// World Position
	Vector2f m_Position;

	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	Texture m_Texture;
};
