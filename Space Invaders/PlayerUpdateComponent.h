#pragma once
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

class PlayerUpdateComponent : public UpdateComponent
{
public:
	void UpdateShipTravelWithController(float x, float y);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void StopLeft();
	void StopRight();
	void StopUp();
	void StopDown();

	string Component::GetSpecificType() {
		return m_SpecificType;
	}

	void Component::Start(GameObjectSharer* gos, GameObject* self) {
		m_TC = static_pointer_cast<TransformComponent>(self->GetComponentByTypeAndSpecificType("Transform", "Tranform"));
		m_RCC = static_pointer_cast<RectColliderComponent>(self->GetComponentByTypeAndSpecificType("Collider", "Rect"));
	}

	void Update(float fps) override;

private:
	string m_SpecificType = "Player";

	shared_ptr<TransformComponent> m_TC;
	shared_ptr<RectColliderComponent> m_RCC;

	float m_Speed = 50.0f;
	float m_XExtent = 0;
	float m_YExtent = 0;

	bool m_IsHoldingLeft = false;
	bool m_IsHoldingRight = false;
	bool m_IsHoldingUp = false;
	bool m_IsHoldingDown = false;
};

