#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "GameObjectSharer.h"
#include <iostream>

using namespace sf;
using namespace std;

class GraphicsComponent : public Component
{
public:
	virtual void Draw(RenderWindow& window, shared_ptr<TransformComponent> t) = 0;
	virtual void InitialiseGraphics(string bitmapName, Vector2f objectSize) = 0;

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
	string m_Type = "Graphics";
	bool m_Enabled = false;
};

