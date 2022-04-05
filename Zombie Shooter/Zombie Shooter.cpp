#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Pickup.h"

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

	Bullet bullets[100];
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletInClip = 6;
	int clipSize = 6;
	float fireRate = 1;
	Time lastPressed;

	window.setMouseCursorVisible(true);
	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture("Graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	Pickup healthPickup(1);
	Pickup ammoPickup(2);

	int score = 0;
	int hiScore = 0;

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
					if (event.key.code == Keyboard::R) {
						if (bulletsSpare >= clipSize) {
							bulletInClip = clipSize;
							bulletsSpare -= clipSize;
						}
						else if (bulletsSpare > 0) {
							bulletInClip = bulletsSpare;
							bulletsSpare = 0;
						}
						else {

						}
					}
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

			if (Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletInClip > 0) {
					bullets[currentBullet].Shoot(player.GetCenter().x, player.GetCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);

					currentBullet++;
					if (currentBullet > 99) {
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;

					bulletInClip--;
				}
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

				healthPickup.SetArena(arena);
				ammoPickup.SetArena(arena);

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

			spriteCrosshair.setPosition(mouseWorldPosition);

			player.Update(dtAsSeconds, Mouse::getPosition());

			Vector2f playerPosition(player.GetCenter());

			mainView.setCenter(player.GetCenter());

			for (int i = 0; i < numZombies; i++) {
				if (zombies[i].IsAlive()) {
					zombies[i].Update(dt.asSeconds(), playerPosition);
				}
			}

			for (int i = 0; i < 100; i++) {
				if (bullets[i].IsInFlight()) {
					bullets[i].Update(dtAsSeconds);
				}
			}

			healthPickup.Update(dtAsSeconds);
			ammoPickup.Update(dtAsSeconds);

			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < numZombies; j++) {
					if (bullets[i].IsInFlight() && zombies[j].IsAlive()) {
						if (bullets[i].GetPosition().intersects(zombies[j].GetPosition())) {
							bullets[i].Stop();
							if (zombies[j].Hit()) {
								score += 10;
								if (hiScore <= score) {
									hiScore = score;
								}

								numZombiesAlive--;

								if (numZombiesAlive == 0) {
									state = State::LEVELING_UP;
								}
							}
						}
					}
				}
			}

			for (int i = 0; i < numZombies; i++) {
				if (player.GetPosition().intersects(zombies[i].GetPosition()) && zombies[i].IsAlive()) {
					if (player.Hit(gameTimeTotal)) {

					}

					if (player.GetHealth() <= 0) {
						state = State::GAME_OVER;
					}
				}
			}

			if (player.GetPosition().intersects(healthPickup.GetPosition()) && healthPickup.IsSpawned()) {
				player.IncreaseHealthLevel(healthPickup.GotIt());
			}
			if (player.GetPosition().intersects(ammoPickup.GetPosition()) && ammoPickup.IsSpawned()) {
				bulletsSpare += ammoPickup.GotIt();
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

			for (int i = 0; i < 100; i++) {
				if (bullets[i].IsInFlight()) {
					window.draw(bullets[i].GetShape());
				}
			}

			window.draw(player.GetSprite());

			if (ammoPickup.IsSpawned()) {
				window.draw(ammoPickup.GetSprite());
			}
			if (healthPickup.IsSpawned()) {
				window.draw(healthPickup.GetSprite());
			}

			window.draw(spriteCrosshair);
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
