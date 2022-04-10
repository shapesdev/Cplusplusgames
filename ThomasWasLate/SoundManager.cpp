#include "SoundManager.h"
#include <SFML/Audio.hpp>

using namespace sf;

SoundManager::SoundManager() {
	m_FireBuffer.loadFromFile("Sounds/fire1.wav");
	m_FallInFireBuffer.loadFromFile("Sounds/fallinfire.wav");
	m_FallInWaterBuffer.loadFromFile("Sounds/fallinwater.wav");
	m_JumpBuffer.loadFromFile("Sounds/jump.wav");
	m_ReachGoalBuffer.loadFromFile("Sounds/reachgoal.wav");

	m_Fire1Sound.setBuffer(m_FireBuffer);
	m_Fire2Sound.setBuffer(m_FireBuffer);
	m_Fire3Sound.setBuffer(m_FireBuffer);
	m_FallInFireSound.setBuffer(m_FallInFireBuffer);
	m_FallInWaterSound.setBuffer(m_FallInWaterBuffer);
	m_JumpSound.setBuffer(m_JumpBuffer);
	m_ReachGoalSound.setBuffer(m_ReachGoalBuffer);

	float minDistance = 150;
	float attenuation = 15;

	m_Fire1Sound.setMinDistance(minDistance);
	m_Fire2Sound.setMinDistance(minDistance);
	m_Fire3Sound.setMinDistance(minDistance);

	m_Fire1Sound.setAttenuation(attenuation);
	m_Fire2Sound.setAttenuation(attenuation);
	m_Fire3Sound.setAttenuation(attenuation);

	m_Fire1Sound.setLoop(true);
	m_Fire2Sound.setLoop(true);
	m_Fire3Sound.setLoop(true);
}

void SoundManager::PlayFire(Vector2f emitterLocation, Vector2f listenerLocation) {
	Listener::setPosition(listenerLocation.x, listenerLocation.y, 0.0f);

	switch (m_NextSound) {
		case 1:
			m_Fire1Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);
			if (m_Fire1Sound.getStatus() == Sound::Status::Stopped) {
				m_Fire1Sound.play();
			}
			break;
		case 2:
			m_Fire2Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);
			if (m_Fire2Sound.getStatus() == Sound::Status::Stopped) {
				m_Fire2Sound.play();
			}
			break;
		case 3:
			m_Fire3Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);
			if (m_Fire3Sound.getStatus() == Sound::Status::Stopped) {
				m_Fire3Sound.play();
			}
			break;
	}

	m_NextSound++;

	if (m_NextSound > 3) {
		m_NextSound = 1;
	}
}

void SoundManager::PlayFallInFire() {
	m_FallInFireSound.setRelativeToListener(true);
	m_FallInFireSound.play();
}

void SoundManager::PlayFallInWater() {
	m_FallInWaterSound.setRelativeToListener(true);
	m_FallInWaterSound.play();
}

void SoundManager::PlayJump() {
	m_JumpSound.setRelativeToListener(true);
	m_JumpSound.play();
}

void SoundManager::PlayReachGoal() {
	m_ReachGoalSound.setRelativeToListener(true);
	m_ReachGoalSound.play();
}