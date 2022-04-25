#pragma once
#include <vector>
#include <string>
#include <map>

using namespace std;

class GameObjectBlueprint
{
public:
	float GetWidth();
	void SetWidth(float width);
	float GetHeight();
	void SetHeight(float height);

	float GetLocationX();
	void SetLocationX(float x);
	float GetLocationY();
	void SetLocationY(float y);

	float GetSpeed();
	void SetSpeed(float speed);

	string GetName();
	void SetName(string name);

	vector<string>& GetComponentList();
	void AddToComponentList(string newComponent);

	string GetBitmapName();
	void SetBitmapName(string bitmapName);

	bool GetEncompassingRectCollider();
	string GetEncompassingRectColliderLabel();
	void SetEncompassingRectCollider(string label);

private:
	string m_Name = "";
	vector<string> m_ComponentList;
	string m_BitmapName;
	float m_Width;
	float m_Height;
	float m_LocationX;
	float m_LocationY;
	float m_Speed;
	bool m_EncompassingRectCollider = false;
	string m_EmpompassingRectColliderLabel = "";
};

