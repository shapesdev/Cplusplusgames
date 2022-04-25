#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
#include "BlueprintObjectParser.h"
#include "GameObjectFactoryPlayMode.h"

using namespace std;

class PlayModeObjectLoader
{
public:
	void LoadGameOBjectsForPlayMode(string pathToFile, vector<GameObject>& mGameObjects);

private:
	BlueprintObjectParser m_BOP;
	GameObjectFactoryPlayMode m_GameObjectFactoryPlayMode;
};

