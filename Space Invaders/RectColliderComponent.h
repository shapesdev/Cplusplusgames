#pragma once
#include "ColliderComponent.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class RectColliderComponent : public ColliderComponent
{
public:
	RectColliderComponent(string name);
	string GetColliderTag();
	void SetOrMoveCollider(float x, float y, float width, float height);

	FloatRect& GetColliderRectF();

	string GetSpecificType() {
		return m_SpecificType;
	}

	void Component::Start(GameObjectSharer* gos, GameObject* self) {

	}

private:
	string m_SpecificType = "Rect";
	FloatRect m_Collider;
	string m_Tag = "";
};

