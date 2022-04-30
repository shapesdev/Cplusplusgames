#include "PhysicsEnginePlayMode.h"
#include "DevelopState.h"
#include <iostream>
#include "SoundEngine.h"
#include "WorldState.h"
#include "InvaderUpdateComponent.h"
#include "BulletUpdateComponent.h"

void PhysicsEnginePlayMode::DetectInvaderCollisions(vector<GameObject>& objects, const vector<int>& bulletPositions) {
	Vector2f offScreen(-1, -1);

	auto invaderIt = objects.begin();
	auto invaderEnd = objects.end();

	for (invaderIt; invaderIt != invaderEnd; ++invaderIt) {
		if ((*invaderIt).IsActive() && (*invaderIt).GetTag() == "Invader") {
			auto bulletIt = objects.begin();
			advance(bulletIt, bulletPositions[0]);
			auto bulletEnd = objects.end();
			for (bulletIt; bulletIt != bulletEnd; ++bulletIt) {
				if ((*invaderIt).GetEncompassingRectCollider().intersects((*bulletIt).GetEncompassingRectCollider()) &&
					(*bulletIt).GetTag() == "Bullet" &&
					static_pointer_cast<BulletUpdateComponent>((*bulletIt).GetFirstUpdateComponent())->m_BelongsToPlayer) {

					SoundEngine::PlayInvaderExplode();
					(*invaderIt).GetTransformComponent()->GetLocation() = offScreen;
					(*bulletIt).GetTransformComponent()->GetLocation() = offScreen;
					WorldState::SCORE++;
					WorldState::NUM_INVADERS--;
					(*invaderIt).SetInactive();
				}
			}
		}
	}
}

void PhysicsEnginePlayMode::DetectPlayerCollisionsAndInvaderDirection(vector<GameObject>& objects, const vector<int>& bulletPositions) {
	Vector2f offScreen(-1, -1);

	FloatRect playerCollider = m_Player->GetEncompassingRectCollider();

	shared_ptr<TransformComponent> playerTransform = m_Player->GetTransformComponent();

	Vector2f playerLocation = playerTransform->GetLocation();

	auto it3 = objects.begin();
	auto end3 = objects.end();

	for (it3; it3 != end3; ++it3) {
		if ((*it3).IsActive() && (*it3).HasCollider() && (*it3).GetTag() != "Player") {
			FloatRect currentCollider = (*it3).GetEncompassingRectCollider();

			if (currentCollider.intersects(playerCollider)) {
				if ((*it3).GetTag() == "Bullet") {
					SoundEngine::PlayPlayerExplode();
					WorldState::LIVES--;
					(*it3).GetTransformComponent()->GetLocation() = offScreen;
				}
				if ((*it3).GetTag() == "Invader") {
					SoundEngine::PlayPlayerExplode();
					SoundEngine::PlayInvaderExplode();
					WorldState::LIVES--;
					(*it3).GetTransformComponent()->GetLocation() = offScreen;

					WorldState::SCORE++;
					(*it3).SetInactive();
				}
			}

			shared_ptr<TransformComponent> currentTransform = (*it3).GetTransformComponent();
			Vector2f currentLocation = currentTransform->GetLocation();

			string currentTag = (*it3).GetTag();
			Vector2f currentSize = currentTransform->GetSize();

			if (currentTag == "Invader") {
				if (!m_NeedToDropDownAndReverse && !m_InvaderHitWallThisFrame) {
					if (currentLocation.x >= WorldState::WORLD_WIDTH - currentSize.x) {
						if (static_pointer_cast<InvaderUpdateComponent>((*it3).GetFirstUpdateComponent())->IsMovingRight()) {
							m_InvaderHitWallThisFrame = true;
						}
					}
					else if (currentLocation.x < 0) {
						if (!static_pointer_cast<InvaderUpdateComponent>((*it3).GetFirstUpdateComponent())->IsMovingRight()) {
							m_InvaderHitWallThisFrame = true;
						}
					}
				}
				else if (m_NeedToDropDownAndReverse && !m_InvaderHitWallPreviousFrame) {
					if ((*it3).HasUpdateComponent()) {
						static_pointer_cast<InvaderUpdateComponent>((*it3).GetFirstUpdateComponent())->DropDownAndReverse();
					}
				}
			}
		}
	}
}

void PhysicsEnginePlayMode::HandleInvaderDirection() {
	if (m_InvaderHitWallThisFrame) {
		m_NeedToDropDownAndReverse = true;
		m_InvaderHitWallThisFrame = false;
	}
	else {
		m_NeedToDropDownAndReverse = false;
	}
}

void PhysicsEnginePlayMode::Initialise(GameObjectSharer& gos) {
	m_PUC = static_pointer_cast<PlayerUpdateComponent>(gos.FindFirstObjectWithTag("Player")
		.GetComponentByTypeAndSpecificType("Update", "Player"));
	m_Player = &gos.FindFirstObjectWithTag("Player");
}

void PhysicsEnginePlayMode::DetectCollisions(vector<GameObject>& objects, const vector<int>& bulletPositions) {
	DetectInvaderCollisions(objects, bulletPositions);
	DetectPlayerCollisionsAndInvaderDirection(objects, bulletPositions);

	HandleInvaderDirection();
}