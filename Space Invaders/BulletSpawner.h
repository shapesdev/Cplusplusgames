#pragma once
#include <SFML/Graphics.hpp>

class BulletSpawner
{
public:
	virtual void SpawnBullet(sf::Vector2f spawnLocation, bool forPlayer) = 0;

};

