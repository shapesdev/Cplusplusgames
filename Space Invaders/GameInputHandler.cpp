#include "GameInputHandler.h"
#include "SoundEngine.h"
#include "GameScreen.h"

void GameInputHandler::Initialise() {}

void GameInputHandler::HandleGamepad() {}

void GameInputHandler::HandleKeyPressed(Event& event, RenderWindow& window) {
	if (event.key.code == Keyboard::Escape) {
		SoundEngine::PlayClick();
		GetPointerToScreenManagerRemoteControl()->LoadLevelInPlayMode("Select");
	}
}

void GameInputHandler::HandleKeyReleased(Event& event, RenderWindow& window) {

}