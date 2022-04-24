#include "StandardGraphicsComponent.h"
#include "BitmapStore.h"
#include <iostream>

void StandardGraphicsComponent::InitialiseGraphics(string bitmapName, Vector2f objectSize) {
	BitmapStore::AddBitmap("Graphics/" + bitmapName + ".png");
	m_Sprite.setTexture(BitmapStore::GetBitmap("Graphics/" + bitmapName + ".png"));

	auto textureSize = m_Sprite.getTexture()->getSize();
	m_Sprite.setScale(float(objectSize.x) / textureSize.x, float(objectSize.y) / textureSize.y);
	m_Sprite.setColor(sf::Color(0, 255, 0));
}

void StandardGraphicsComponent::Draw(RenderWindow& window, shared_ptr<TransformComponent> t) {
	m_Sprite.setPosition(t->GetLocation());
	window.draw(m_Sprite);
}