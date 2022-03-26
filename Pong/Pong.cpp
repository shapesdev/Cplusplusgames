#include "Bat.h"
#include "Ball.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	VideoMode vm(1920, 1080);

	RenderWindow window(vm, "Pong", Style::Fullscreen);

	int score = 0;
	int lives = 3;

	Bat bat(1920 / 2, 1080 - 20);

	Ball ball(1920 / 2, 0);

	Text hud;
	Font font;
	font.loadFromFile("Fonts/DS-DIGI.ttf");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);

	Clock clock;

	while (window.isOpen()) {

		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			bat.MoveLeft();
		}
		else {
			bat.StopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			bat.MoveRight();
		}
		else {
			bat.StopRight();
		}

		Time dt = clock.restart();
		bat.Update(dt);
		ball.Update(dt);

		std::stringstream ss;
		ss << "Score:" << score << "  Lives:" << lives;
		hud.setString(ss.str());

		if (ball.GetPosition().top > window.getSize().y) {
			ball.ReboundBottom();

			lives--;

			if (lives < 1) {
				score = 0;
				lives = 3;
			}
		}

		if (ball.GetPosition().top < 0) {
			ball.ReboundBatOrTop();

			score++;
		}

		if (ball.GetPosition().left < 0 || ball.GetPosition().left + ball.GetPosition().width > window.getSize().x) {
			ball.ReboundSides();
		}

		if (ball.GetPosition().intersects(bat.GetPosition())) {
			ball.ReboundBatOrTop();
		}

		window.clear();
		window.draw(hud);
		window.draw(bat.GetShape());
		window.draw(ball.GetShape());
		window.display();
	}

	return 0;
}
