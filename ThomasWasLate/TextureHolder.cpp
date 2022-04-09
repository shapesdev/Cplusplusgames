#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::m_Instance = nullptr;

TextureHolder::TextureHolder() {
	assert(m_Instance == nullptr);
	m_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename) {
	auto& map = m_Instance->m_Textures;

	auto keyValuePair = map.find(filename);

	if (keyValuePair != map.end()) {
		return keyValuePair->second;
	}
	else {
		auto& texture = map[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}