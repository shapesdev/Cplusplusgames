#include "InvaderUpdateComponent.h"
#include "BulletSpawner.h"
#include "WorldState.h"
#include "SoundEngine.h"

void InvaderUpdateComponent::Update(float fps) {
	if (m_MovingRight) {
		m_TC->GetLocation().x += m_Speed * fps;
	}
	else {
		m_TC->GetLocation().x -= m_Speed * fps;
	}

	m_RCC->SetOrMoveCollider(m_TC->GetLocation().x, m_TC->GetLocation().y, m_TC->GetSize().x, m_TC->GetSize().y);

	m_TimeSinceLastShot += fps;

	if ((m_TC->GetLocation().x + (m_TC->GetSize().x / 2)) > (m_PlayerTC->GetLocation().x - m_AccuracyModifier) &&
		(m_TC->GetLocation().x + (m_TC->GetSize().x / 2)) < (m_PlayerTC->GetLocation().x + (m_PlayerTC->GetSize().x + m_AccuracyModifier))) {

		if (m_TimeSinceLastShot > m_TimeBetweenShots) {
			SoundEngine::PlayShoot();
			Vector2f spawnLocation;
			spawnLocation.x = m_TC->GetLocation().x + m_TC->GetSize().x / 2;
			spawnLocation.y = m_TC->GetLocation().y + m_TC->GetSize().y;

			m_BulletSpawner->SpawnBullet(spawnLocation, false);
			srand(m_RandSeed);
			int mTimeBetweenShots = (((rand() % 10)) + 1) / WorldState::WAVE_NUMBER;

			m_TimeSinceLastShot = 0;
		}
	}
}

void InvaderUpdateComponent::DropDownAndReverse() {
	m_MovingRight = !m_MovingRight;
	m_TC->GetLocation().y += m_TC->GetSize().y;
	m_Speed += (WorldState::WAVE_NUMBER)+(WorldState::NUM_INVADERS_AT_START - WorldState::NUM_INVADERS) * m_SpeedModifier;
}

bool InvaderUpdateComponent::IsMovingRight() {
	return m_MovingRight;
}

void InvaderUpdateComponent::InitialiseBulletSpawner(BulletSpawner* bulletSpawner, int randSeed) {
	m_BulletSpawner = bulletSpawner;
	m_RandSeed = randSeed;
	srand(m_RandSeed);
	m_TimeBetweenShots = (rand() % 15 + m_RandSeed);

	m_AccuracyModifier = (rand() % 2);
	m_AccuracyModifier += 0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (10)));
}