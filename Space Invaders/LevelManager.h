#pragma once
#include "GameObject.h"
#include <vector>
#include <string>
#include "GameObjectSharer.h"

using namespace std;

class LevelManager : public GameObjectSharer
{
public:
	vector<GameObject>& GetGameObjects();
	void LoadGameObjectsForPlayMode(string screenToLoad);

	vector<GameObject>& GameObjectSharer::GetGameObjectwithGOS() {
		return m_GameObjects;
	}

	GameObject& GameObjectSharer::FindFirstObjectWithTag(string tag) {
		auto it = m_GameObjects.begin();
		auto end = m_GameObjects.end();

		for (it; it != end; ++it) {
			if ((*it).GetTag() == tag) {
				return (*it);
			}
		}

#ifdef debuggingErrors
		cout <<
			"LevelManager.h findFirstGameObjectWithTag() "
			<< "- TAG NOT FOUND ERROR!"
			<< endl;
#endif
		return m_GameObjects[0];
	}

private:
	vector<GameObject> m_GameObjects;
	
	const std::string WORLD_FOLDER = "World";
	const std::string SLASH = "/";

	void RunStartPhase();
	void ActivateAllGameObjects();
};

