#include "Engine.h"

void Engine::LoadLevel() {
	m_Playing = false;

	for (int i = 0; i < m_LM.GetLevelSize().y; ++i) {
		delete[] m_ArrayLevel[i];
	}
	delete[] m_ArrayLevel;

	m_ArrayLevel = m_LM.NextLevel(m_VALevel);

	m_TimeRemaining = m_LM.GetTimeLimit();

	m_Thomas.Spawn(m_LM.GetStartPosition(), GRAVITY);
	m_Bob.Spawn(m_LM.GetStartPosition(), GRAVITY);

	m_NewLevelRequired = false;
}