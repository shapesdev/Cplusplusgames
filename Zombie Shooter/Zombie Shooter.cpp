#include <iostream>
#include <sstream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

	Sprite spriteGameOver;
	Texture textureGameOver = TextureHolder::GetTexture("Graphics/background.png");
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);

	View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	Sprite spriteAmmoIcon;
	Texture textureAmmoIcon = TextureHolder::GetTexture("Graphics/ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, 980);

	Font font;
	font.loadFromFile("Fonts/zombiecontrol.ttf");

	Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(Color::White);
	pausedText.setPosition(400, 400);
	pausedText.setString("Press Enter \nto continue");

	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(125);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition(250, 800);
	gameOverText.setString("Press Enter to play");

	// LEVELING UP
	Text levelUpText;
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(80);
	levelUpText.setFillColor(Color::White);
	levelUpText.setPosition(150, 250);
	std::stringstream levelUpStream;
	levelUpStream <<
		"1- Increased rate of fire" <<
		"\n2- Increased clip size(next reload)" <<
		"\n3- Increased max health" <<
		"\n4- Increased run speed" <<
		"\n5- More and better health pickups" <<
		"\n6- More and better ammo pickups";
	levelUpText.setString(levelUpStream.str());

	Text ammoText;
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::White);
	ammoText.setPosition(200, 980);

	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 0);

	std::ifstream inputFile("Data/scores.txt", fstream::app);
	if (inputFile.is_open()) {
		inputFile >> hiScore;
		inputFile.close();
	}

	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setPosition(1400, 0);
	std::stringstream s;
	s << "High Score: " << hiScore;
	hiScoreText.setString(s.str());

	Text zombiesRemainingText;
	zombiesRemainingText.setFont(font);
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(Color::White);
	zombiesRemainingText.setPosition(1500, 980);
	zombiesRemainingText.setString("Zombies: 100");

	int wave = 0;
	Text waveNumberText;
	zombiesRemainingText.setFont(font);
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(Color::White);
	zombiesRemainingText.setPosition(1250, 980);
	zombiesRemainingText.setString("Wave: 0");

	RectangleShape healthBar;
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(450, 980);

	Text debugText;
	debugText.setFont(font);
	debugText.setCharacterSize(25);
	debugText.setFillColor(Color::White);
	debugText.setPosition(20, 200);
	std::ostringstream ss;

	int framesSinceLastHUDUpdate = 0;
	int fpsMeasurementFrameInterval = 1000;

	SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("Sounds/hit.wav");
	Sound hit;
	hit.setBuffer(hitBuffer);

	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("Sounds/shoot.wav");
	Sound shoot;
	shoot.setBuffer(shootBuffer);

	SoundBuffer splatBuffer;
	shootBuffer.loadFromFile("Sounds/splat.wav");
	Sound splat;
	splat.setBuffer(splatBuffer);

	SoundBuffer reloadBuffer;
	reloadBuffer.loadFromFile("Sounds/reload.wav");
	Sound reload;
	reload.setBuffer(reloadBuffer);

	SoundBuffer reloadFailedBuffer;
	reloadBuffer.loadFromFile("Sounds/reload_failed.wav");
	Sound reloadFailed;
	reloadFailed.setBuffer(reloadFailedBuffer);

	SoundBuffer powerupBuffer;
	reloadBuffer.loadFromFile("Sounds/powerup.wav");
	Sound powerup;
	powerup.setBuffer(powerupBuffer);

	SoundBuffer pickupBuffer;
	reloadBuffer.loadFromFile("Sounds/pickup.wav");
	Sound pickup;
	pickup.setBuffer(pickupBuffer);

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
					wave = 0;
					score = 0;

					currentBullet = 0;
					bulletsSpare = 24;
					bulletInClip = 6;
					clipSize = 6;
					fireRate = 1;

					player.ResetPlayerStats();
				}
				
				if (state == State::PLAYING) {
					if (event.key.code == Keyboard::R) {
						if (bulletsSpare >= clipSize) {
							bulletInClip = clipSize;
							bulletsSpare -= clipSize;
							reload.play();
						}
						else if (bulletsSpare > 0) {
							bulletInClip = bulletsSpare;
							bulletsSpare = 0;
							reload.play();
						}
						else {
							reloadFailed.play();
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


					shoot.play();

					bulletInClip--;
				}
			}
		}

		if (state == State::LEVELING_UP) {
			if (event.key.code == Keyboard::Num1) {
				state = State::PLAYING;
				fireRate++;
			}
			if (event.key.code == Keyboard::Num2) {
				state = State::PLAYING;
				clipSize += clipSize;
			}
			if (event.key.code == Keyboard::Num3) {
				state = State::PLAYING;
				player.UpgradeHealth();
			}
			if (event.key.code == Keyboard::Num4) {
				state = State::PLAYING;
				player.UpgradeSpeed();
			}
			if (event.key.code == Keyboard::Num5) {
				state = State::PLAYING;
				healthPickup.Upgrade();
			}
			if (event.key.code == Keyboard::Num6) {
				state = State::PLAYING;
				ammoPickup.Upgrade();
			}
			if (state == State::PLAYING) {
				wave++;

				arena.width = 500 * wave;
				arena.height = 500 * wave;
				arena.left = 0;
				arena.top = 0;

				int tileSize = CreateBackground(background, arena);

				player.Spawn(arena, resolution, tileSize);

				healthPickup.SetArena(arena);
				ammoPickup.SetArena(arena);

				numZombies = 5 * wave;

				delete[] zombies;
				zombies = CreateHorde(numZombies, arena);
				numZombiesAlive = numZombies;

				powerup.play();

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
							splat.play();
						}
					}
				}
			}

			for (int i = 0; i < numZombies; i++) {
				if (player.GetPosition().intersects(zombies[i].GetPosition()) && zombies[i].IsAlive()) {
					if (player.Hit(gameTimeTotal)) {
						hit.play();
					}

					if (player.GetHealth() <= 0) {
						state = State::GAME_OVER;

						std::ofstream outputFile("Data/scores.txt");
						outputFile << hiScore;
						outputFile.close();
					}
				}
			}

			if (player.GetPosition().intersects(healthPickup.GetPosition()) && healthPickup.IsSpawned()) {
				player.IncreaseHealthLevel(healthPickup.GotIt());
				pickup.play();
			}
			if (player.GetPosition().intersects(ammoPickup.GetPosition()) && ammoPickup.IsSpawned()) {
				bulletsSpare += ammoPickup.GotIt();
				reload.play();
			}

			healthBar.setSize(Vector2f(player.GetHealth() * 3, 50));
			framesSinceLastHUDUpdate++;

			if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval) {
				std::stringstream ssAmmo;
				std::stringstream ssScore;
				std::stringstream ssHiScore;
				std::stringstream ssWave;
				std::stringstream ssZombiesAlive;

				ssAmmo << bulletInClip << "/" << bulletsSpare;
				ammoText.setString(ssAmmo.str());

				ssScore << "Score: " << score;
				scoreText.setString(ssScore.str());

				ssHiScore << "High Score: " << hiScore;
				hiScoreText.setString(ssHiScore.str());

				ssWave << "Wave: " << wave;
				waveNumberText.setString(ssWave.str());

				ssZombiesAlive << "Zombies: " << numZombiesAlive;
				zombiesRemainingText.setString(ssZombiesAlive.str());

				framesSinceLastHUDUpdate = 0;
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

			window.setView(hudView);

			window.draw(spriteAmmoIcon);
			window.draw(ammoText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(healthBar);
			window.draw(waveNumberText);
			window.draw(zombiesRemainingText);
		}
		if (state == State::LEVELING_UP) {
			window.draw(spriteGameOver);
			window.draw(levelUpText);
		}
		if (state == State::PAUSED) {
			window.draw(pausedText);
		}
		if (state == State::GAME_OVER) {
			window.draw(spriteGameOver);
			window.draw(gameOverText);
			window.draw(scoreText);
			window.draw(hiScoreText);
		}

		window.display();
	}

	delete[] zombies;

	return 0;
}
