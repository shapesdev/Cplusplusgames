#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"

using namespace sf;

class Engine
{
public:
	Engine();
	void Run();

private:
	TextureHolder th;

	Thomas m_Thomas;
	Bob m_Bob;

	LevelManager m_LM;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;
	const int GRAVITY = 300;

	RenderWindow m_Window;

	View m_MainView;
	View m_LeftView;
	View m_RightView;

	View m_BGMainView;
	View m_BGLeftView;
	View m_BGRightView;

	View m_HudView;

	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	bool m_Playing;
	bool m_Character1 = true;
	bool m_SplitScreen = false;

	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;

	bool m_NewLevelRequired = true;

	VertexArray m_VALevel;
	int** m_ArrayLevel = NULL;
	Texture m_TexturesTiles;

	void Input();
	void Update(float dtAsSeconds);
	void Draw();
	void LoadLevel();
	bool DetectCollisions(PlayableCharacter& character);
};

