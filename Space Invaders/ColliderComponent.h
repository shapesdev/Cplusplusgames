#pragma once
#include "Component.h"
#include <iostream>

class ColliderComponent : public Component
{
public:
	string Component::GetType() {
		return m_Type;
	}

	void Component::DisableComponent() {
		m_Enabled = false;
	}

	void Component::EnableComponent() {
		m_Enabled = true;
	}

	bool Component::Enabled() {
		return m_Enabled;
	}

	void Component::Start(GameObjectSharer* gos, GameObject* self) {

	}

private:
	string m_Type = "Collider";
	bool m_Enabled = false;
};

