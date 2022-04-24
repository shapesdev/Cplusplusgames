#include "BulletUpdateComponent.h"
#include "WorldState.h"

void BulletUpdateComponent::SpawnForPlayer(Vector2f spawnPosition) {
	m_MovingUp = true;
	m_BelongsToPlayer = true;
	m_IsSpawned = true;

	m_TC->GetLocation().x = spawnPosition.x;
	m_TC->GetLocation().y = spawnPosition.y - m_TC->GetSize().y;

	m_RCC->SetOrMoveCollider(m_TC->GetLocation().x, m_TC->GetLocation().y, m_TC->GetSize().x, m_TC->GetSize().y);
}

void BulletUpdateComponent::SpawnForInvader(Vector2f spawnPosition) {
	m_MovingUp = false;
	m_BelongsToPlayer = false;
	m_IsSpawned = true;

	srand((int)time(0));
	m_AlienBulletSpeedModifier = (((rand() % m_ModifierRandomComponent)) + m_MinimmumAdditionalModifier);

	m_TC->GetLocation().x = spawnPosition.x;
	m_TC->GetLocation().y = spawnPosition.y;

	m_RCC->SetOrMoveCollider(m_TC->GetLocation().x, m_TC->GetLocation().y, m_TC->GetSize().x, m_TC->GetSize().y);
}

void BulletUpdateComponent::DeSpawn() {
	m_IsSpawned = false;
}

bool BulletUpdateComponent::IsMovingUp() {
	return m_MovingUp;
}

void BulletUpdateComponent::Update(float fps) {
	if (m_IsSpawned) {
		if (m_MovingUp) {
			m_TC->GetLocation().y -= m_Speed * fps;
		}
		else {
			m_TC->GetLocation().y += m_Speed / m_AlienBulletSpeedModifier * fps;
		}

		if (m_TC->GetLocation().y > WorldState::WORLD_HEIGHT) {
			DeSpawn();
		}

		m_RCC->SetOrMoveCollider(m_TC->GetLocation().x, m_TC->GetLocation().y, m_TC->GetSize().x, m_TC->GetSize().y);
	}
}