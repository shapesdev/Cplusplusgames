#include "Bob.h"
#include "TextureHolder.h"
#include <iostream>

Bob::Bob() {
	m_Sprite = Sprite(TextureHolder::GetTexture("Graphics/bob.png"));
	m_JumpDuration = .25;
}

bool Bob::HandleInput() {
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (!m_IsJumping && !m_IsFalling) {
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}
	}
	else {
		m_IsJumping = false;
		m_IsFalling = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		m_LeftPressed = true;
	}
	else {
		m_LeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		m_RightPressed = true;
	}
	else {
		m_RightPressed = false;
	}

	return m_JustJumped;
}
