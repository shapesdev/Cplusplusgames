#pragma once
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

class BulletSpawner;

class InvaderUpdateComponent : public UpdateComponent
{
public:
	void DropDownAndReverse();
	bool IsMovingRight();
	void InitialiseBulletSpawner(BulletSpawner* bulletSpawner, int randSeed);

	string Component::GetSpecificType() {
		return m_SpecificType;
	}

	void Component::Start(GameObjectSharer* gos, GameObject* self) {
		m_PlayerTC = static_pointer_cast<TransformComponent>(gos->FindFirstObjectWithTag("Player").GetComponentByTypeAndSpecificType(
			"Transform", "Transform"));

		m_PlayerRCC = static_pointer_cast<RectColliderComponent>(gos->FindFirstObjectWithTag("Player").GetComponentByTypeAndSpecificType(
			"Collider", "Rect"));

		m_TC = static_pointer_cast<TransformComponent>(self->GetComponentByTypeAndSpecificType(
			"Transform", "Transform"));

		m_RCC = static_pointer_cast<RectColliderComponent>(self->GetComponentByTypeAndSpecificType(
			"Collider", "Rect"));
	}

	void Update(float fps) override;

private:
	string m_SpecificType = "Invader";

	shared_ptr<TransformComponent> m_TC;
	shared_ptr<RectColliderComponent> m_RCC;
	shared_ptr<TransformComponent> m_PlayerTC;
	shared_ptr<RectColliderComponent> m_PlayerRCC;

	BulletSpawner* m_BulletSpawner;

	float m_Speed = 10.0f;
	bool m_MovingRight = true;
	float m_TimeSinceLastShot;
	float m_TimeBetweenShots = 5.0f;
	float m_AccuracyModifier;
	float m_SpeedModifier = 0.05;
	int m_RandSeed;
};

