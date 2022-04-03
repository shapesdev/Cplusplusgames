#pragma once
#include "Zombie.h"

using namespace sf;

int CreateBackground(VertexArray& rVA, IntRect arena);
Zombie* CreateHorde(int numZombies, IntRect arena);

