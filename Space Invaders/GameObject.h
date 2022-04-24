#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Component.h"
#include "GraphicsComponent.h"
#include "GameObjectSharer.h"
#include "UpdateComponent.h"

class GameObject
{
public:
	void Update(float fps);
	void Draw(RenderWindow& window);
	void AddComponent(shared_ptr<Component> component);

	void SetActive();
	void SetInactive();
	bool IsActive();
	void SetTag(string tag);
	string GetTag();

	void Start(GameObjectSharer* gos);

	// Slow, only in init or start
	shared_ptr<Component> GetComponentByTypeAndSpecificType(string type, string specificType);

	FloatRect& GetEncompassingRectCollider();
	bool HasCollider();
	bool HasUpdateComponent();
	string GetEncompassingRectColliderTag();

	shared_ptr<GraphicsComponent> GetGraphicsComponent();
	shared_ptr<TransformComponent> GetTransformComponent();
	shared_ptr<UpdateComponent> GetFirstUpdateComponent();

private:
	vector<shared_ptr<Component>> m_Components;

	string m_Tag;
	bool m_Active = false;
	bool m_HasCollider = false;

	int m_NumberUpdateComponents = 0;
	int m_NumberRectColliderComponents = 0;

	bool m_HasUpdateComponent = false;
	bool m_HasGraphicsComponent = false;

	int m_FirstUpdateComponentLocation = -1;
	int m_FirstGraphicsComponentLocation = -1;
	int m_FirstTransformComponentLocation = -1;
	int m_FirstRectColliderComponentLocation = -1;
};

