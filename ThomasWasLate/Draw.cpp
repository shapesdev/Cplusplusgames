#include "Engine.h"

void Engine::Draw() {
	m_Window.clear(Color::White);

	if (!m_SplitScreen) {
		m_Window.setView(m_BGMainView);
		m_Window.draw(m_BackgroundSprite);
		m_Window.setView(m_MainView);

		m_Window.draw(m_VALevel, &m_TexturesTiles);

		m_Window.draw(m_Thomas.GetSprite());
		m_Window.draw(m_Bob.GetSprite());
	}
	else {
		m_Window.setView(m_BGLeftView);
		m_Window.draw(m_BackgroundSprite);
		m_Window.setView(m_LeftView);

		m_Window.draw(m_VALevel, &m_TexturesTiles);

		m_Window.draw(m_Bob.GetSprite());
		m_Window.draw(m_Thomas.GetSprite());

		m_Window.setView(m_BGRightView);
		m_Window.draw(m_BackgroundSprite);
		m_Window.setView(m_RightView);

		m_Window.draw(m_VALevel, &m_TexturesTiles);

		m_Window.draw(m_Thomas.GetSprite());
		m_Window.draw(m_Bob.GetSprite());
	}

	m_Window.setView(m_HudView);
	m_Window.display();
}