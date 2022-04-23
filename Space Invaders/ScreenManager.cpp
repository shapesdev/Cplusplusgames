#include "ScreenManager.h"

ScreenManager::ScreenManager(Vector2i res) {
	m_Screens["Game"] = unique_ptr<GameScreen>(new GameScreen(this, res));

	m_Screens["Select"] = unique_ptr<SelectScreen>(new SelectScreen(this, res));
}

void ScreenManager::HandleInput(RenderWindow& window) {
	m_Screens[m_CurrentScreen]->HandleInput(window);
}

void ScreenManager::Update(float fps) {
	m_Screens[m_CurrentScreen]->Update(fps);
}

void ScreenManager::Draw(RenderWindow& window) {
	m_Screens[m_CurrentScreen]->Draw(window);
}