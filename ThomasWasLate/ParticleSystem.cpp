#include "ParticleSystem.h"

using namespace sf;
using namespace std;

void ParticleSystem::Init(int numParticles) {
	m_Vertices.setPrimitiveType(Points);
	m_Vertices.resize(numParticles);

	for (int i = 0; i < numParticles; i++) {
		srand(time(0) + i);
		float angle = (rand() % 360) * 3.14f / 180.f;
		float speed = (rand() % 600) + 600.f;

		Vector2f direction;
		direction = Vector2f(cos(angle) * speed, sin(angle) * speed);
		m_Particles.push_back(Particle(direction));
	}
}

void ParticleSystem::Update(float dt) {
	m_Duration -= dt;
	vector<Particle>::iterator itr;
	int currentVertex = 0;

	for (itr = m_Particles.begin(); itr != m_Particles.end(); itr++) {
		(*itr).Update(dt);
		m_Vertices[currentVertex++].position = itr->GetPosition();

		if (m_Duration < 0) {
			m_IsRunning = false;
		}
	}
}

void ParticleSystem::EmitParticles(Vector2f startPosition) {
	m_IsRunning = true;
	m_Duration = 2;

	int currentVertex = 0;

	for (auto itr = m_Particles.begin(); itr != m_Particles.end(); itr++) {
		m_Vertices[currentVertex++].color = Color::Yellow;
		itr->SetPosition(startPosition);
	}
}

void ParticleSystem::draw(RenderTarget& target, RenderStates states) const {
	target.draw(m_Vertices, states);
}

bool ParticleSystem::Running() {
	return m_IsRunning;
}