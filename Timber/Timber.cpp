#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	// Create new video mode object
	VideoMode vm(1920, 1080);

	//Create and oepn a window for the game
	RenderWindow window(vm, "Timber!", Style::Fullscreen);

	Texture backgroundTexture;

	backgroundTexture.loadFromFile("Graphics/background.png");

	Sprite backgroundSprite;

	backgroundSprite.setTexture(backgroundTexture);

	backgroundSprite.setPosition(0, 0);

	while (window.isOpen()) {

		// Handle Input
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		// Update the Scene

		// Clear everything from last frame
		window.clear();

		// Draw the Scene
		window.draw(backgroundSprite);

		// Show everything we just draw
		window.display();
	}

	return 0;
}
