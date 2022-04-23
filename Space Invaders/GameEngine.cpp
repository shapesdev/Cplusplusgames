#include "GameEngine.h"

GameEngine::GameEngine() {
	m_Resolution.x = VideoMode::getDesktopMode().width;
	m_Resolution.y = VideoMode::getDesktopMode().height;
	m_Window.create(VideoMode(m_Resolution.x, m_Resolution.y), "Space Invaders", Style::Fullscreen);

	m_ScreenManager = unique_ptr<ScreenManager>(new ScreenManager(Vector2i(m_Resolution.x, m_Resolution.y)));
}

void GameEngine::Run() {
	while (m_Window.isOpen()) {
		m_DT = m_Clock.restart();
		m_FPS = m_DT.asSeconds();
		HandleInput();
		Update();
		Draw();
	}
}

void GameEngine::HandleInput() {
	m_ScreenManager->HandleInput(m_Window);
}

void GameEngine::Update() {
	m_ScreenManager->Update(m_FPS);
}

void GameEngine::Draw() {
	m_Window.clear(Color::Black);
	m_ScreenManager->Draw(m_Window);
	m_Window.display();
}