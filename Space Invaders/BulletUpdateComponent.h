#pragma once
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

class BulletUpdateComponent : public UpdateComponent
{
public:
	bool m_BelongsToPlayer = false;
	bool m_IsSpawned = false;

	void SpawnForPlayer(Vector2f spawnPosition);
	void SpawnForInvader(Vector2f spawnPosition);
	void DeSpawn();
	bool IsMovingUp();

	string Component::GetSpecificType() {
		return m_SpecificType;
	}

	void Component::Start(GameObjectSharer* gos, GameObject* self) {
		m_TC = static_pointer_cast<TransformComponent>(self->GetComponentByTypeAndSpecificType("Transform", "Transform"));
		m_RCC = static_pointer_cast<RectColliderComponent>(self->GetComponentByTypeAndSpecificType("Collider", "Rect"));
	}

	void Update(float fps) override;

private:
	string m_SpecificType = "Bullet";
	shared_ptr<TransformComponent> m_TC;
	shared_ptr<RectColliderComponent> m_RCC;

	float m_Speed = 75.0f;

	int m_AlienBulletSpeedModifier;
	int m_ModifierRandomComponent = 5;
	int m_MinimmumAdditionalModifier = 5;

	bool m_MovingUp = true;
};

