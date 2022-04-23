#include "BitmapStore.h"
#include <assert.h>

using namespace std;
using namespace sf;

BitmapStore* BitmapStore::m_s_Instance = nullptr;

BitmapStore::BitmapStore() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

void BitmapStore::AddBitmap(string const& filename) {
	auto& bitmapsMap = m_s_Instance->m_BitmapMap;
	auto keyValuePair = bitmapsMap.find(filename);

	if (keyValuePair == bitmapsMap.end()) {
		auto& texture = bitmapsMap[filename];
		texture.loadFromFile(filename);
	}
}

Texture& BitmapStore::GetBitmap(string const& filename) {
	auto& m = m_s_Instance->m_BitmapMap;
	auto keyValuePair = m.find(filename);

	if (keyValuePair != m.end()) {
		return keyValuePair->second;
	}
	else {
#ifdef debuggingOnConsole
		cout << "BitmapStore::GetBitmap() Texture not found Crrrrash!" << endl;
#endif
		return keyValuePair->second;
	}
}