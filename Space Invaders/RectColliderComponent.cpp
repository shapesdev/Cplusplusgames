#include "RectColliderComponent.h"

RectColliderComponent::RectColliderComponent(string name) {
	m_Tag = "" + name;
}

string RectColliderComponent::GetColliderTag() {
	return m_Tag;
}

void RectColliderComponent::SetOrMoveCollider(float x, float y, float width, float height) {
	m_Collider.left = x;
	m_Collider.top = y;
	m_Collider.width = width;
	m_Collider.height = height;
}

FloatRect& RectColliderComponent::GetColliderRectF() {
	return m_Collider;
}
