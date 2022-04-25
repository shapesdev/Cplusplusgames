#pragma once
#include "GameObjectBlueprint.h"
#include "GameObject.h"
#include <vector>

class GameObjectFactoryPlayMode
{
public:
	void BuildGameObject(GameObjectBlueprint& bp, std::vector<GameObject>& gameObjects);
};

