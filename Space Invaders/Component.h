#pragma once
#include "GameObjectSharer.h"
#include <string>

using namespace std;

class GameObject;

class Component
{
public:
	virtual string GetType() = 0;
	virtual string GetSpecificType() = 0;
	virtual void DisableComponent() = 0;
	virtual void EnableComponent() = 0;
	virtual bool Enabled() = 0;
	virtual void Start(GameObjectSharer* gos, GameObject* self) = 0;
};

