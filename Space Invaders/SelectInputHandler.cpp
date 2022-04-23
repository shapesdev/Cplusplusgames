#include "SelectInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include <iostream>

int WorldState::WAVE_NUMBER;

void SelectInputHandler::HandleKeyPressed(Event& event, RenderWindow& window) {
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void SelectInputHandler::HandleLeftClick(std::string& buttonInteractedWith, RenderWindow& window) {
	if (buttonInteractedWith == "Play") {
		SoundEngine::PlayClick();
		WorldState::WAVE_NUMBER = 0;
		GetPointerToScreenManagerRemoteControl()->LoadLevelInPlayMode("level1");
	}
	if (buttonInteractedWith == "Quit") {
		SoundEngine::PlayClick();
		window.close();
	}
}
