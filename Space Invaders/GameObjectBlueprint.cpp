#include "GameObjectBlueprint.h"

// GETTERS

float GameObjectBlueprint::GetWidth() {
	return m_Width;
}

float GameObjectBlueprint::GetHeight() {
	return m_Height;
}

float GameObjectBlueprint::GetLocationX() {
	return m_LocationX;
}

float GameObjectBlueprint::GetLocationY() {
	return m_LocationY;
}

string GameObjectBlueprint::GetName() {
	return m_Name;
}

string GameObjectBlueprint::GetBitmapName() {
	return m_BitmapName;
}

vector<string>& GameObjectBlueprint::GetComponentList() {
	return m_ComponentList;
}

bool GameObjectBlueprint::GetEncompassingRectCollider() {
	return m_EncompassingRectCollider;
}

string GameObjectBlueprint::GetEncompassingRectColliderLabel() {
	return m_EmpompassingRectColliderLabel;
}

// SETTERS

void GameObjectBlueprint::SetWidth(float width) {
	m_Width = width;
}

void GameObjectBlueprint::SetHeight(float height) {
	m_Height = height;
}

void GameObjectBlueprint::SetLocationX(float x) {
	m_LocationX = x;
}

void GameObjectBlueprint::SetLocationY(float y) {
	m_LocationY = y;
}

void GameObjectBlueprint::SetName(string name) {
	m_Name = name;
}

void GameObjectBlueprint::SetBitmapName(string bitmap) {
	m_BitmapName = bitmap;
}

void GameObjectBlueprint::SetSpeed(float speed) {
	m_Speed = speed;
}

void GameObjectBlueprint::AddToComponentList(string newComponent) {
	m_ComponentList.push_back(newComponent);
}