#include "GameOverInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include <iostream>

void GameOverInputHandler::HandleKeyPressed(Event& event, RenderWindow& window) {
	if (event.key.code == Keyboard::Escape) {
		SoundEngine::PlayClick();
		GetPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
	}
}

void GameOverInputHandler::HandleLeftClick(std::string& buttonInteractedWith, RenderWindow& window) {
	if (buttonInteractedWith == "Play") {
		SoundEngine::PlayClick();
		WorldState::WAVE_NUMBER = 0;
		GetPointerToScreenManagerRemoteControl()->LoadLevelInPlayMode("level1");
	}
	else if (buttonInteractedWith == "Home") {
		SoundEngine::PlayClick();
		GetPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
	}
}
