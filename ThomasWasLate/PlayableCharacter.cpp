#include "PlayableCharacter.h"

void PlayableCharacter::Spawn(Vector2f startPosition, float gravity) {
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	m_Gravity = gravity;

	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::Update(float elapsedTime)
{
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}
	// Handle Jumping
	if (m_IsJumping)
	{
		// Update how long the jump has been going
		m_TimeThisJump += elapsedTime;
		// Is the jump going upwards
		if (m_TimeThisJump < m_JumpDuration)
		{
			// Move up at twice gravity
			m_Position.y -= m_Gravity * 2 * elapsedTime;
		}
		else
		{
			m_IsJumping = false;
			m_IsFalling = true;
		}
	}
	// Apply gravity
	if (m_IsFalling)
	{
		m_Position.y += m_Gravity * elapsedTime;
	}
	// Update the rect for all body parts
	FloatRect r = GetPosition();

	// Feet
	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left;
	m_Head.top = r.top + (r.height * .3);
	m_Head.width = r.width;
	m_Head.height = 1;
	// Right
	m_Right.left = r.left + r.width - 2;
	m_Right.top = r.top + r.height * .35;
	m_Right.width = 1;
	m_Right.height = r.height * .3;
	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .5;
	m_Left.width = 1;
	m_Left.height = r.height * .3;
	// Move the sprite into position
	m_Sprite.setPosition(m_Position);
}

FloatRect PlayableCharacter::GetPosition() {
	return m_Sprite.getGlobalBounds();
}

Vector2f PlayableCharacter::GetCenter() {
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2);
}

FloatRect PlayableCharacter::GetFeet() {
	return m_Feet;
}

FloatRect PlayableCharacter::GetHead() {
	return m_Head;
}

FloatRect PlayableCharacter::GetLeft() {
	return m_Left;
}

FloatRect PlayableCharacter::GetRight() {
	return m_Right;
}

Sprite PlayableCharacter::GetSprite() {
	return m_Sprite;
}

void PlayableCharacter::StopFalling(float position) {
	m_Position.y = position - GetPosition().height;
	m_Sprite.setPosition(m_Position);
	m_IsFalling = false;
}

void PlayableCharacter::StopRight(float position) {
	m_Position.x = position - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::StopLeft(float position) {
	m_Position.x = position + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::StopJump() {
	m_IsJumping = false;
	m_IsFalling = true;
}