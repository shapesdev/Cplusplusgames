#include "Engine.h"

using namespace sf;
using namespace std;

void Engine::PopulateEmitters(vector <Vector2f>& soundEmitters, int** arrayLevel) {
	soundEmitters.empty();

	FloatRect previousEmitter;

	for (int x = 0; x < (int)m_LM.GetLevelSize().x; x++) {
		for (int y = 0; y < (int)m_LM.GetLevelSize().y; y++) {
			if (arrayLevel[y][x] == 2) {
				if (!FloatRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE).intersects(previousEmitter)) {
					soundEmitters.push_back(Vector2f(x * TILE_SIZE, y * TILE_SIZE));

					previousEmitter.left = x * TILE_SIZE;
					previousEmitter.top = y * TILE_SIZE;
					previousEmitter.width = TILE_SIZE * 6;
					previousEmitter.height = TILE_SIZE * 6;
				}
			}
		}
	}
	return;
}