#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"
#include "TextureHolder.h"

using namespace sf;

int main()
{
	TextureHolder holder;

	enum class State {
		PAUSED, LEVELING_UP, GAME_OVER, PLAYING
	};

	State state = State::GAME_OVER;

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Shooter", Style::Fullscreen);

	View mainView(FloatRect(0, 0, resolution.x, resolution.y));

	Clock clock;

	Time gameTimeTotal;

	Vector2f mouseWorldPosition;
	Vector2i mouseScreenPosition;

	Player player;

	IntRect arena;

	VertexArray background;
	Texture textureBackground = TextureHolder::GetTexture("Graphics/background_sheet.png");

	int numZombies;
	int numZombiesAlive;
	Zombie* zombies = nullptr;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Return && state == State::PLAYING) {
					state = State::PAUSED;
				}
				else if (event.key.code == Keyboard::Return && state == State::PAUSED) {
					state = State::PLAYING;
					clock.restart();
				}
				else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
					state = State::LEVELING_UP;
				}
				
				if (state == State::PLAYING) {

				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		// INPUT

		if (state == State::PLAYING) {
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				player.MoveUp();
			}
			else {
				player.StopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S)) {
				player.MoveDown();
			}
			else {
				player.StopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A)) {
				player.MoveLeft();
			}
			else {
				player.StopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D)) {
				player.MoveRight();
			}
			else {
				player.StopRight();
			}
		}

		if (state == State::LEVELING_UP) {
			if (event.key.code == Keyboard::Num1) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num2) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num3) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num4) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num5) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num6) {
				state = State::PLAYING;
			}
			if (state == State::PLAYING) {
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;

				int tileSize = CreateBackground(background, arena);

				player.Spawn(arena, resolution, tileSize);

				numZombies = 10;

				delete[] zombies;
				zombies = CreateHorde(numZombies, arena);
				numZombiesAlive = numZombies;

				clock.restart();
			}
		}

		// UPDATE

		if (state == State::PLAYING) {
			Time dt = clock.restart();

			gameTimeTotal += dt;

			float dtAsSeconds = dt.asSeconds();

			mouseScreenPosition = Mouse::getPosition();

			mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

			player.Update(dtAsSeconds, Mouse::getPosition());

			Vector2f playerPosition(player.GetCenter());

			mainView.setCenter(player.GetCenter());

			for (int i = 0; i < numZombies; i++) {
				if (zombies[i].IsAlive()) {
					zombies[i].Update(dt.asSeconds(), playerPosition);
				}
			}
		}

		// DRAWING

		if (state == State::PLAYING) {
			window.clear();

			window.setView(mainView);

			window.draw(background, &textureBackground);

			for (int i = 0; i < numZombies; i++) {
				window.draw(zombies[i].GetSprite());
			}

			window.draw(player.GetSprite());
		}
		if (state == State::LEVELING_UP) {

		}
		if (state == State::PAUSED) {

		}
		if (state == State::GAME_OVER) {

		}

		window.display();
	}

	delete[] zombies;

	return 0;
}
