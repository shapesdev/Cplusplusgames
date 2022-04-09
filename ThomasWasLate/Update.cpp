#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::Update(float dtAsSeconds) {
	if (m_NewLevelRequired) {
		m_Thomas.Spawn(Vector2f(0, 0), GRAVITY);
		m_Bob.Spawn(Vector2f(100, 0), GRAVITY);

		m_TimeRemaining = 10;
		m_NewLevelRequired = false;
	}

	if (m_Playing) {
		m_Thomas.Update(dtAsSeconds);
		m_Bob.Update(dtAsSeconds);

		m_TimeRemaining -= dtAsSeconds;

		if (m_TimeRemaining <= 0) {
			m_NewLevelRequired = true;
		}
	}

	if (m_SplitScreen) {
		m_LeftView.setCenter(m_Thomas.GetCenter());
		m_RightView.setCenter(m_Bob.GetCenter());
	}
	else {
		if (m_Character1) {
			m_MainView.setCenter(m_Thomas.GetCenter());
		}
		else {
			m_MainView.setCenter(m_Bob.GetCenter());
		}
	}
}