#include "Engine.h"

void Engine::Draw() {
	m_Window.clear(Color::White);

	m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());

	if (!m_SplitScreen) {
		m_Window.setView(m_BGMainView);
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		m_Window.setView(m_MainView);

		m_Window.draw(m_VALevel, &m_TexturesTiles);

		m_Window.draw(m_Thomas.GetSprite());
		m_Window.draw(m_Bob.GetSprite());

		if (m_PS.Running()) {
			m_Window.draw(m_PS);
		}
	}
	else {
		m_Window.setView(m_BGLeftView);
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		m_Window.setView(m_LeftView);

		m_Window.draw(m_VALevel, &m_TexturesTiles);

		m_Window.draw(m_Bob.GetSprite());
		m_Window.draw(m_Thomas.GetSprite());

		if (m_PS.Running()) {
			m_Window.draw(m_PS);
		}

		m_Window.setView(m_BGRightView);
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		m_Window.setView(m_RightView);

		m_Window.draw(m_VALevel, &m_TexturesTiles);

		m_Window.draw(m_Thomas.GetSprite());
		m_Window.draw(m_Bob.GetSprite());

		if (m_PS.Running()) {
			m_Window.draw(m_PS);
		}
	}

	m_Window.setView(m_HudView);
	m_Window.draw(m_HUD.GetLevel());
	m_Window.draw(m_HUD.GetTime());
	if (!m_Playing) {
		m_Window.draw(m_HUD.GetMessage());
	}

	m_Window.display();
}