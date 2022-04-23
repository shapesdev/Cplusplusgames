#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace std;

class UIPanel
{
public:
	View m_View;
	UIPanel(Vector2i res, int x, int y, float width, float height,
		int alpha, int red, int green, int blue);

	vector<shared_ptr<Button>> GetButtons();
	virtual void Draw(RenderWindow& window);
	void Show();
	void Hide();

private:
	RectangleShape m_UIPanel;
	bool m_Hidden = false;
	vector<shared_ptr<Button>> m_Buttons;

protected:
	float m_ButtonWidth = 0;
	float m_ButtonHeight = 0;
	float m_ButtonPadding = 0;

	Font m_Font;
	Text m_Text;

	void AddButton(float x, float y, int width, int height,
		int red, int green, int blue, string label);
};

