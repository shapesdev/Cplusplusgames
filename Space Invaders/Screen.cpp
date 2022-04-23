#include "Screen.h"

void Screen::Initialise() {}

void Screen::AddPanel(unique_ptr<UIPanel> uip, ScreenManagerRemoteControl* smrc, shared_ptr<InputHandler> ih) {
	ih->InitialiseInputHandler(smrc, uip->GetButtons(), &uip->m_View, this);
	m_Panels.push_back(move(uip));
	m_InputHandlers.push_back(ih);
}

void Screen::HandleInput(RenderWindow& window) {
	Event event;
	auto itr = m_InputHandlers.begin();
	auto end = m_InputHandlers.end();
	while (window.pollEvent(event)) {
		for (itr; itr != end; ++itr) {
			(*itr)->HandleInput(window, event);
		}
	}
}

void Screen::Update(float fps) {}

void Screen::Draw(RenderWindow& window) {
	auto itr = m_Panels.begin();
	auto end = m_Panels.end();

	for (itr; itr != end; ++itr) {
		(*itr)->Draw(window);
	}
}
