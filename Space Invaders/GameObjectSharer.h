#pragma once
#include <vector>
#include <string>

class GameObject;

class GameObjectSharer
{
public:
	virtual std::vector<GameObject>& GetGameObjectwithGOS() = 0;
	virtual GameObject& FindFirstObjectWithTag(std::string tag) = 0;
};

