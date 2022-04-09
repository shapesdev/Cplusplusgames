#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::Update(float dtAsSeconds) {
	if (m_NewLevelRequired) {
		LoadLevel();
	}

	if (m_Playing) {
		m_Thomas.Update(dtAsSeconds);
		m_Bob.Update(dtAsSeconds);

		if (DetectCollisions(m_Thomas) && DetectCollisions(m_Bob)) {
			m_NewLevelRequired = true;
		}
		else {
			DetectCollisions(m_Bob);
		}

		if (m_Bob.GetFeet().intersects(m_Thomas.GetHead())) {
			m_Bob.StopFalling(m_Thomas.GetHead().top);
		}
		else if (m_Thomas.GetFeet().intersects(m_Bob.GetHead())) {
			m_Thomas.StopFalling(m_Bob.GetHead().top);
		}

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