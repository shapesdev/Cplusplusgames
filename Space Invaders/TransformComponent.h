#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Component;

class TransformComponent : public Component
{
public:
	TransformComponent(float width, float height, Vector2f location);
	Vector2f& GetLocation();
	Vector2f GetSize();

	string Component::GetType() {
		return m_Type;
	}

	string Component::GetSpecificType() {
		return m_Type;
	}

	void Component::DisableComponent() {}
	void Component::EnableComponent() {}

	bool Component::Enabled() {
		return false;
	}

	void Component::Start(GameObjectSharer* gos, GameObject* self) {}

private:
	const string m_Type = "Transform";
	Vector2f m_Location;
	float m_Height;
	float m_Width;
};

