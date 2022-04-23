#include "SoundEngine.h"
#include <assert.h>

using namespace std;
using namespace sf;

SoundEngine* SoundEngine::m_s_Instance = nullptr;

SoundEngine::SoundEngine() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;

	m_ShootBuffer.loadFromFile("Sounds/shoot.ogg");
	m_PlayerExplodeBuffer.loadFromFile("Sounds/playerexplode.ogg");
	m_InvaderExplodeBuffer.loadFromFile("Sounds/invaderexplode.ogg");
	m_ClickBuffer.loadFromFile("Sounds/click.ogg");

	m_ShootSound.setBuffer(m_ShootBuffer);
	m_PlayerExplodeSound.setBuffer(m_PlayerExplodeBuffer);
	m_InvaderExplodeSound.setBuffer(m_InvaderExplodeBuffer);
	m_ClickSound.setBuffer(m_ClickBuffer);
}

void SoundEngine::PlayShoot() {
	m_s_Instance->m_ShootSound.play();
}

void SoundEngine::PlayPlayerExplode() {
	m_s_Instance->m_PlayerExplodeSound.play();
}

void SoundEngine::PlayInvaderExplode() {
	m_s_Instance->m_InvaderExplodeSound.play();
}

void SoundEngine::PlayClick() {
	m_s_Instance->m_ClickSound.play();
}