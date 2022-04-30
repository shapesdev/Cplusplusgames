#include "GameInputHandler.h"
#include "SoundEngine.h"
#include "GameScreen.h"

class BulletSpawner;

void GameInputHandler::Initialise() {}

void GameInputHandler::HandleKeyPressed(Event& event, RenderWindow& window) {
	if (event.key.code == Keyboard::Escape) {
		SoundEngine::PlayClick();
		GetPointerToScreenManagerRemoteControl()->LoadLevelInPlayMode("Select");
	}

	if (event.key.code == Keyboard::Left) {
		m_PUC->MoveLeft();
	}
	if (event.key.code == Keyboard::Right) {
		m_PUC->MoveRight();
	}
	if (event.key.code == Keyboard::Up) {
		m_PUC->MoveUp();
	}
	if (event.key.code == Keyboard::Down) {
		m_PUC->MoveDown();
	}
}

void GameInputHandler::HandleKeyReleased(Event& event, RenderWindow& window) {
	if (event.key.code == Keyboard::Left) {
		m_PUC->StopLeft();
	}
	else if (event.key.code == Keyboard::Right) {
		m_PUC->StopRight();
	}
	else if (event.key.code == Keyboard::Up) {
		m_PUC->StopUp();
	}
	else if (event.key.code == Keyboard::Down) {
		m_PUC->StopDown();
	}
	else if (event.key.code == Keyboard::Space) {
		SoundEngine::PlayShoot();
		Vector2f spawnLocation;
		spawnLocation.x = m_PTC->GetLocation().x + m_PTC->GetSize().x / 2;
		spawnLocation.y = m_PTC->GetLocation().y;

		static_cast<GameScreen*>(GetParentScreen())->SpawnBullet(spawnLocation, true);
	}
}

void GameInputHandler::HandleGamepad() {
	float deadZone = 10.0f;
	float x = Joystick::getAxisPosition(0, sf::Joystick::X);
	float y = Joystick::getAxisPosition(0, sf::Joystick::Y);

	if (x < deadZone && x > -deadZone) {
		x = 0;
	}
	if (y < deadZone && y > -deadZone) {
		y = 0;
	}

	m_PUC->UpdateShipTravelWithController(x, y);

	if (Joystick::isButtonPressed(0, 1)) {
		m_ButtonPressed = true;
	}

	if (!Joystick::isButtonPressed(0, 1) && m_ButtonPressed) {
		m_ButtonPressed = false;

		SoundEngine::PlayShoot();
		Vector2f spawnLocation;
		spawnLocation.x = m_PTC->GetLocation().x + m_PTC->GetSize().x / 2;
		spawnLocation.y = m_PTC->GetLocation().y;

		static_cast<GameScreen*>(GetParentScreen())->GetBulletSpawner()->SpawnBullet(spawnLocation, true);
	}
}