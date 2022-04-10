#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"

using namespace sf;
using namespace std;

class ParticleSystem : public Drawable
{
public:
	virtual void draw(RenderTarget& target, RenderStates states) const;

	void Init(int count);
	void EmitParticles(Vector2f position);
	void Update(float elapsed);
	bool Running();

private:
	vector<Particle> m_Particles;
	VertexArray m_Vertices;
	float m_Duration;
	bool m_IsRunning = false;
};

