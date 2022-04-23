#pragma once
#ifndef SOUND_ENGINE_H
#define SOUND_ENGINE_H

#include <SFML/Audio.hpp>

using namespace sf;

class SoundEngine
{
public:
	SoundEngine();

	static void PlayShoot();
	static void PlayPlayerExplode();
	static void PlayInvaderExplode();
	static void PlayClick();

	static SoundEngine* m_s_Instance;

private:
	SoundBuffer m_ShootBuffer;
	SoundBuffer m_PlayerExplodeBuffer;
	SoundBuffer m_InvaderExplodeBuffer;
	SoundBuffer m_ClickBuffer;

	Sound m_ShootSound;
	Sound m_PlayerExplodeSound;
	Sound m_InvaderExplodeSound;
	Sound m_UhSound;
	Sound m_OhSound;
	Sound m_ClickSound;
};

#endif
