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

	vector<Vector2f>::iterator itr;

	for (itr = m_FireEmitters.begin(); itr != m_FireEmitters.end(); itr++) {
		float posX = (*itr).x;
		float posY = (*itr).y;

		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		if (m_Thomas.GetPosition().intersects(localRect)) {
			m_SM.PlayFire(Vector2f(posX, posY), m_Thomas.GetCenter());
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

	m_FramesSinceLastHUDUpdate++;

	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate) {
		stringstream ssTime;
		stringstream ssLevel;

		ssTime << (int)m_TimeRemaining;
		m_HUD.SetTime(ssTime.str());

		ssLevel << "Level: " << m_LM.GetCurrentLevel();
		m_HUD.SetLevel(ssLevel.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

	if (m_PS.Running()) {
		m_PS.Update(dtAsSeconds);
	}
}