#pragma once
#include "Component.h"
#include "GraphicsComponent.h"
#include <string>

class Component;

class StandardGraphicsComponent : public GraphicsComponent
{
public:
	string Component::GetSpecificType() {
		return m_specificType;
	}

	void Component::Start(GameObjectSharer* gos, GameObject* self) {

	}

	void Draw(RenderWindow& window, shared_ptr<TransformComponent> t) override;
	void InitialiseGraphics(string bitmapName, Vector2f objectSize) override;

private:
	sf::Sprite m_Sprite;
	string m_specificType = "Standard";
};

