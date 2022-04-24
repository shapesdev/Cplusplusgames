#include "PlayerUpdateComponent.h"
#include "WorldState.h"

void PlayerUpdateComponent::Update(float fps) {
	if (sf::Joystick::isConnected(0)) {
		m_TC->GetLocation().x += ((m_Speed / 100) * m_XExtent) * fps;
		m_TC->GetLocation().y += ((m_Speed / 100) * m_YExtent) * fps;
	}

	if (m_IsHoldingLeft) {
		m_TC->GetLocation().x -= m_Speed * fps;
	}
	if (m_IsHoldingRight) {
		m_TC->GetLocation().x += m_Speed * fps;
	}
	if (m_IsHoldingUp) {
		m_TC->GetLocation().y -= m_Speed * fps;
	}
	if (m_IsHoldingDown) {
		m_TC->GetLocation().x += m_Speed * fps;
	}

	m_RCC->SetOrMoveCollider(m_TC->GetLocation().x, m_TC->GetLocation().y, m_TC->GetSize().x, m_TC->GetSize().y);

	if (m_TC->GetLocation().x > WorldState::WORLD_WIDTH - m_TC->GetSize().x) {
		m_TC->GetLocation().x = WorldState::WORLD_WIDTH - m_TC->GetSize().x;
	}
	else if (m_TC->GetLocation().x < 0) {
		m_TC->GetLocation().x = 0;
	}

	if (m_TC->GetLocation().y > WorldState::WORLD_HEIGHT - m_TC->GetSize().y) {
		m_TC->GetLocation().y = WorldState::WORLD_HEIGHT - m_TC->GetSize().y;
	}
	else if (m_TC->GetLocation().y < WorldState::WORLD_HEIGHT / 2) {
		m_TC->GetLocation().y = WorldState::WORLD_HEIGHT / 2;
	}
}

void PlayerUpdateComponent::UpdateShipTravelWithController(float x, float y) {
	m_XExtent = x;
	m_YExtent = y;
}

void PlayerUpdateComponent::MoveLeft() {
	m_IsHoldingLeft = true;
	StopRight();
}

void PlayerUpdateComponent::MoveRight() {
	m_IsHoldingRight = true;
	StopLeft();
}

void PlayerUpdateComponent::MoveDown() {
	m_IsHoldingDown = true;
	StopUp();
}

void PlayerUpdateComponent::MoveUp() {
	m_IsHoldingUp = true;
	StopDown();
}

void PlayerUpdateComponent::StopLeft() {
	m_IsHoldingLeft = false;
}

void PlayerUpdateComponent::StopRight() {
	m_IsHoldingRight = false;
}

void PlayerUpdateComponent::StopDown() {
	m_IsHoldingDown = false;
}

void PlayerUpdateComponent::StopUp() {
	m_IsHoldingUp = false;
}