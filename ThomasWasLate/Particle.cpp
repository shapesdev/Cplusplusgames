#include "Particle.h"

Particle::Particle(Vector2f direction) {
	m_Velocity.x = direction.x;
	m_Velocity.y = direction.y;
}

void Particle::Update(float dtAsSeconds) {
	m_Position += m_Velocity * dtAsSeconds;
}

void Particle::SetPosition(Vector2f position) {
	m_Position = position;
}

Vector2f Particle::GetPosition() {
	return m_Position;
}