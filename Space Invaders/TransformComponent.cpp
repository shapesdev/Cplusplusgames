#include "TransformComponent.h"

TransformComponent::TransformComponent(float width, float height, Vector2f location) {
	m_Height = height;
	m_Width = width;
	m_Location = location;
}

Vector2f& TransformComponent::GetLocation() {
	return m_Location;
}

Vector2f TransformComponent::GetSize() {
	return Vector2f(m_Width, m_Height);
}