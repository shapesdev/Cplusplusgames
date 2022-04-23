#include <sstream>
#include "InputHandler.h"

using namespace sf;
using namespace std;

void InputHandler::InitialiseInputHandler(ScreenManagerRemoteControl* sw,
	vector<shared_ptr<Button>> buttons, View* pointerToUIView, Screen* parentScreen) {
	m_ScreenManagerRemoteControl = sw;
	m_Buttons = buttons;
	m_PointerToUIPanelView = pointerToUIView;
	m_ParentScreen = parentScreen;
}

void InputHandler::HandleInput(RenderWindow& window, Event& event) {
	if (event.type == Event::KeyPressed) {
		HandleKeyPressed(event, window);
	}
	if (event.type == Event::KeyReleased) {
		HandleKeyReleased(event, window);
	}
	if (event.type == Event::MouseButtonReleased) {
		auto end = m_Buttons.end();
		for (auto i = m_Buttons.begin(); i != end; ++i) {
			if ((*i)->m_Collider.contains(window.mapPixelToCoords(Mouse::getPosition(), (*GetPointerToUIView())))) {
				HandleLeftClick((*i)->m_Text, window);
				break;
			}
		}
	}
	HandleGamepad();
}

void InputHandler::HandleGamepad() {

}

void InputHandler::HandleKeyPressed(Event& event, RenderWindow& window) {

}

void InputHandler::HandleKeyReleased(Event& event, RenderWindow& window) {

}

void InputHandler::HandleLeftClick(std::string& buttonInteractedWith, RenderWindow& window) {

}

View* InputHandler::GetPointerToUIView() {
	return m_PointerToUIPanelView;
}

ScreenManagerRemoteControl* InputHandler::GetPointerToScreenManagerRemoteControl() {
	return m_ScreenManagerRemoteControl;
}

Screen* InputHandler::GetParentScreen() {
	return m_ParentScreen;
}

