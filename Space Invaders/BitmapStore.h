#pragma once
#ifndef BITMAP_STORE_H
#define BITMAP_STORE_H

#include <SFML/Graphics.hpp>
#include <map>

class BitmapStore
{
public:
	BitmapStore();

	static sf::Texture& GetBitmap(std::string const& filename);
	static void AddBitmap(std::string const& filename);

private:
	static BitmapStore* m_s_Instance;

	std::map<std::string, sf::Texture> m_BitmapMap;
};

#endif

