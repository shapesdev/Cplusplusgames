#pragma once

#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
public:
	TextureHolder();

	static Texture& GetTexture(string const& filename);

private:
	static TextureHolder* m_Instance;

	map<string, Texture> m_Textures;
};

#endif

