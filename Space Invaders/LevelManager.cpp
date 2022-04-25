#include "LevelManager.h"
#include "PlayModeObjectLoader.h"
#include <iostream>

void LevelManager::LoadGameObjectsForPlayMode(string screenToLoad) {
	m_GameObjects.clear();
	string levelToLoad = "" + WORLD_FOLDER + SLASH + screenToLoad;

	PlayModeObjectLoader pmol;
	pmol.LoadGameOBjectsForPlayMode(levelToLoad, m_GameObjects);

	RunStartPhase();
}

vector<GameObject>& LevelManager::GetGameObjects() {
	return m_GameObjects;
}

void LevelManager::RunStartPhase() {
	auto it = m_GameObjects.begin();
	auto end = m_GameObjects.end();

	for (it; it != end; ++it) {
		(*it).Start(this);
	}

	ActivateAllGameObjects();
}

void LevelManager::ActivateAllGameObjects() {
	auto it = m_GameObjects.begin();
	auto end = m_GameObjects.end();

	for (it; it != end; ++it) {
		(*it).SetActive();
	}
}
