#include "GameScreen.h"
#include "GameUIPanel.h"
#include "GameInputHandler.h"
#include "GameOverUIPanel.h"
#include "WorldState.h"
#include "GameObject.h"
#include "WorldState.h"
#include "BulletUpdateComponent.h"
#include "InvaderUpdateComponent.h"

class BulletSpawner;

int WorldState::WORLD_HEIGHT;
int WorldState::NUM_INVADERS;
int WorldState::NUM_INVADERS_AT_START;

GameScreen::GameScreen(ScreenManagerRemoteControl* smrc, Vector2i res) {
	m_GIH = make_shared<GameInputHandler>();
	auto guip = make_unique<GameUIPanel>(res);
	AddPanel(move(guip), smrc, m_GIH);

	auto m_GOIH = make_shared<GameOverInputHandler>();
	auto gouip = make_unique<GameOverUIPanel>(res);
	AddPanel(move(gouip), smrc, m_GOIH);

	m_ScreenManagerRemoteControl = smrc;
	float screenRatio = VideoMode::getDesktopMode().width / VideoMode::getDesktopMode().height;

	WorldState::WORLD_HEIGHT = WorldState::WORLD_WIDTH / screenRatio;

	m_View.setSize(WorldState::WORLD_WIDTH, WorldState::WORLD_HEIGHT);
	m_View.setCenter(Vector2f(WorldState::WORLD_WIDTH / 2, WorldState::WORLD_HEIGHT / 2));

	m_BackgroundTexture.loadFromFile("Graphics/background.png");
	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	auto textureSize = m_BackgroundSprite.getTexture()->getSize();
	m_BackgroundSprite.setScale(float(m_View.getSize().x) / textureSize.x, float(m_View.getSize().y) / textureSize.y);
}

void GameScreen::Initialise() {
	m_GIH->Initialise();
	m_PhysicsEnginePlayMode.Initialise(m_ScreenManagerRemoteControl->ShareGameObjectSharer());

	WorldState::NUM_INVADERS = 0;

	int i = 0;
	auto it = m_ScreenManagerRemoteControl->GetGameObjects().begin();
	auto end = m_ScreenManagerRemoteControl->GetGameObjects().end();

	for (it; it != end; ++it) {
		if ((*it).GetTag() == "Bullet") {
			m_BulletObjectLocations.push_back(i);
		}
		if ((*it).GetTag() == "Invader") {
			static_pointer_cast<InvaderUpdateComponent>((*it).GetFirstUpdateComponent())->InitialiseBulletSpawner(GetBulletSpawner(), i);
			WorldState::NUM_INVADERS++;
		}
		++i;
	}

	m_GameOver = false;

	if (WorldState::WAVE_NUMBER == 0) {
		WorldState::NUM_INVADERS_AT_START = WorldState::NUM_INVADERS;

		WorldState::WAVE_NUMBER = 1;
		WorldState::LIVES = 3;
		WorldState::SCORE = 0;
	}
}

void GameScreen::Update(float fps) {
	Screen::Update(fps);

	if (!m_GameOver) {

		if (m_WaitingToSpawnBulletForPlayer) {
			static_pointer_cast<BulletUpdateComponent>(m_ScreenManagerRemoteControl->GetGameObjects()[m_BulletObjectLocations[m_NextBullet]]
				.GetFirstUpdateComponent())->SpawnForPlayer(m_PlayerBulletSpawnLocation);
			m_WaitingToSpawnBulletForPlayer = false;
			m_NextBullet++;

			if (m_NextBullet == m_BulletObjectLocations.size()) {
				m_NextBullet = 0;
			}
		}

		if (m_WaitingToSpawnBulletForInvader) {
			static_pointer_cast<BulletUpdateComponent>(m_ScreenManagerRemoteControl->GetGameObjects()[m_BulletObjectLocations[m_NextBullet]]
				.GetFirstUpdateComponent())->SpawnForInvader(m_InvaderBulletSpawnLocation);
			m_WaitingToSpawnBulletForInvader = false;
			m_NextBullet++;

			if (m_NextBullet == m_BulletObjectLocations.size()) {
				m_NextBullet = 0;
			}
		}

		auto it = m_ScreenManagerRemoteControl->GetGameObjects().begin();
		auto end = m_ScreenManagerRemoteControl->GetGameObjects().end();

		for (it; it != end; ++it) {
			(*it).Update(fps);
		}

		m_PhysicsEnginePlayMode.DetectCollisions(m_ScreenManagerRemoteControl->GetGameObjects(), m_BulletObjectLocations);

		if (WorldState::NUM_INVADERS <= 0) {
			WorldState::WAVE_NUMBER++;
			m_ScreenManagerRemoteControl->LoadLevelInPlayMode("level1");
		}
		if (WorldState::LIVES <= 0) {
			m_GameOver = true;
		}
	}
}

void GameScreen::Draw(RenderWindow& window) {
	window.setView(m_View);
	window.draw(m_BackgroundSprite);

	auto it = m_ScreenManagerRemoteControl->GetGameObjects().begin();
	auto end = m_ScreenManagerRemoteControl->GetGameObjects().end();

	for (it; it != end; ++it) {
		(*it).Draw(window);
	}

	Screen::Draw(window);
}

BulletSpawner* GameScreen::GetBulletSpawner() {
	return this;
}