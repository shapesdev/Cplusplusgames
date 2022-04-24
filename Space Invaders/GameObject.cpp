#include "GameObject.h"
#include "DevelopState.h"
#include "UpdateComponent.h"
#include "RectColliderComponent.h"
#include <iostream>

void GameObject::Update(float fps) {
	if (m_Active && m_HasUpdateComponent) {
		for (int i = m_FirstUpdateComponentLocation; i < m_FirstUpdateComponentLocation +
			m_NumberUpdateComponents; i++) {

			shared_ptr<UpdateComponent> tempUpdate = static_pointer_cast<UpdateComponent>(m_Components[i]);
			if (tempUpdate->Enabled()) {
				tempUpdate->Update(fps);
			}
		}
	}
}

void GameObject::Draw(RenderWindow& window) {
	if (m_Active && m_HasGraphicsComponent) {
		if (m_Components[m_FirstGraphicsComponentLocation]->Enabled()) {
			GetGraphicsComponent()->Draw(window, GetTransformComponent());
		}
	}
}

shared_ptr<GraphicsComponent> GameObject::GetGraphicsComponent() {
	return static_pointer_cast<GraphicsComponent>(m_Components[m_FirstGraphicsComponentLocation]);
}

shared_ptr<TransformComponent> GameObject::GetTransformComponent() {
	return static_pointer_cast<TransformComponent>(m_Components[m_FirstTransformComponentLocation]);
}

void GameObject::AddComponent(shared_ptr<Component> component) {
	m_Components.push_back(component);
	component->EnableComponent();

	if (component->GetType() == "Update") {
		m_HasUpdateComponent = true;
		m_NumberUpdateComponents++;
		if (m_NumberUpdateComponents == 1) {
			m_FirstUpdateComponentLocation = m_Components.size() - 1;
		}
	}
	else if (component->GetType() == "Graphics") {
		m_HasGraphicsComponent = true;
		m_FirstGraphicsComponentLocation = m_Components.size() - 1;
	}
	else if (component->GetType() == "Transform") {
		m_FirstTransformComponentLocation = m_Components.size() - 1;
	}
	else if (component->GetType() == "Collider" && component->GetSpecificType() == "Rect") {
		m_HasCollider = true;
		m_NumberRectColliderComponents++;
		if (m_NumberRectColliderComponents == 1) {
			m_FirstRectColliderComponentLocation = m_Components.size() - 1;
		}
	}
}

void GameObject::SetActive() {
	m_Active = true;
}

void GameObject::SetInactive() {
	m_Active = false;
}

bool GameObject::IsActive() {
	return m_Active;
}

void GameObject::SetTag(string tag) {
	m_Tag = "" + tag;
}

std::string GameObject::GetTag() {
	return m_Tag;
}

void GameObject::Start(GameObjectSharer* gos) {
	auto it = m_Components.begin();
	auto end = m_Components.end();

	for (it; it != end; ++it) {
		(*it)->Start(gos, this);
	}
}

shared_ptr<Component> GameObject::GetComponentByTypeAndSpecificType(string type, string specificType) {
	auto it = m_Components.begin();
	auto end = m_Components.end();

	for (it; it != end; ++it) {
		if ((*it)->GetType() == type) {
			if ((*it)->GetSpecificType() == specificType) {
				return (*it);
			}
		}
	}

#ifdef debuggingErrors
	cout <<
		"GameObject.cpp::getComponentByTypeAndSpecificType-"
		<< "COMPONENT NOT FOUND ERROR!"
		<< endl;
#endif
	return m_Components[0];

}

FloatRect& GameObject::GetEncompassingRectCollider() {
	if (m_HasCollider) {
		return (static_pointer_cast<RectColliderComponent>(m_Components[m_FirstRectColliderComponentLocation]))->GetColliderRectF();
	}
}

string GameObject::GetEncompassingRectColliderTag() {
	return static_pointer_cast<RectColliderComponent>(m_Components[m_FirstRectColliderComponentLocation])->GetColliderTag();
}

shared_ptr<UpdateComponent> GameObject::GetFirstUpdateComponent() {
	return static_pointer_cast<UpdateComponent>(m_Components[m_FirstUpdateComponentLocation]);
}

bool GameObject::HasCollider() {
	return m_HasCollider;
}

bool GameObject::HasUpdateComponent() {
	return m_HasUpdateComponent;
}