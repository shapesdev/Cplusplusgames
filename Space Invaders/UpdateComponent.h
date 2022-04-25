#pragma once
#include "Component.h"

class UpdateComponent : public Component
{
public:
	virtual void Update(float fps) = 0;

	string Component::GetType() {
		return m_Type;
	}

	void Component::EnableComponent() {
		m_Enabled = true;
	}

	void Component::DisableComponent() {
		m_Enabled = false;
	}

	bool Component::Enabled() {
		return m_Enabled;
	}

	void Component::Start(GameObjectSharer* gos, GameObject* self) {

	}

private:
	string m_Type = "Update";
	bool m_Enabled = false;
};

