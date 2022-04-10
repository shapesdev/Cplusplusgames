#include "Engine.h"

bool Engine::DetectCollisions(PlayableCharacter& character) {
	bool reachedGoal = false;

	FloatRect detectionZone = character.GetPosition();

	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;

	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (endX >= m_LM.GetLevelSize().x) endX = m_LM.GetLevelSize().x;
	if (endY >= m_LM.GetLevelSize().y) endY = m_LM.GetLevelSize().y;

	FloatRect level(0, 0, m_LM.GetLevelSize().x * TILE_SIZE, m_LM.GetLevelSize().y * TILE_SIZE);

	if (!character.GetPosition().intersects(level)) {
		character.Spawn(m_LM.GetStartPosition(), GRAVITY);
	}

	for (int x = startX; x < endX; x++) {
		for (int y = startY; y < endY; y++) {
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;

			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3) {
				if (character.GetHead().intersects(block)) {
					character.Spawn(m_LM.GetStartPosition(), GRAVITY);
					if (m_ArrayLevel[y][x] == 2) {
						m_SM.PlayFallInFire();
					}
					else {
						m_SM.PlayFallInWater();
					}
				}
			}
			if (m_ArrayLevel[y][x] == 1) {
				if (character.GetRight().intersects(block)) {
					character.StopRight(block.left);
				}
				else if (character.GetLeft().intersects(block)) {
					character.StopLeft(block.left);
				}

				if (character.GetFeet().intersects(block)) {
					character.StopFalling(block.top);
				}
				else if (character.GetHead().intersects(block)) {
					character.StopJump();
				}
			}

			if (!m_PS.Running()) {
				if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3) {
					if (character.GetFeet().intersects(block)) {
						m_PS.EmitParticles(character.GetCenter());
					}
				}
			}

			if (m_ArrayLevel[y][x] == 4) {
				reachedGoal = true;
			}
		}
	}
	return reachedGoal;
}