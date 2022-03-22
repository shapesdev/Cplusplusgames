#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

void UpdateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

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

	Texture treeTexture;
	treeTexture.loadFromFile("Graphics/tree.png");
	Sprite treeSprite;
	treeSprite.setTexture(treeTexture);
	treeSprite.setPosition(810, 0);

	Texture beeTexture;
	beeTexture.loadFromFile("Graphics/bee.png");
	Sprite beeSprite;
	beeSprite.setTexture(beeTexture);
	beeSprite.setPosition(0, 800);

	bool beeActive = false;
	float beeSpeed = 0.0f;

	Texture cloudTexture;
	cloudTexture.loadFromFile("Graphics/cloud.png");
	Sprite cloudSprite1;
	Sprite cloudSprite2;
	Sprite cloudSprite3;
	cloudSprite1.setTexture(cloudTexture);
	cloudSprite2.setTexture(cloudTexture);
	cloudSprite3.setTexture(cloudTexture);
	cloudSprite1.setPosition(0, 0);
	cloudSprite2.setPosition(0, 250);
	cloudSprite3.setPosition(0, 500);

	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Variables to control time itself
	Clock clock;

	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidtdhPerSecond = timeBarStartWidth / timeRemaining;

	bool paused = true;
	int score = 0;
	
	Text scoreText;
	Text messageText;
	Font font;
	font.loadFromFile("Fonts/KOMIKAP_.ttf");
	messageText.setFont(font);
	scoreText.setFont(font);

	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	scoreText.setCharacterSize(75);
	messageText.setCharacterSize(100);

	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	RectangleShape scoreBar;
	scoreBar.setSize(Vector2f(400, textRect.height));
	scoreBar.setFillColor(Color(0, 0, 0, 80));
	scoreBar.setPosition(20, 20);

	Texture branchTexture;
	branchTexture.loadFromFile("Graphics/branch.png");

	Texture playerTexture;
	playerTexture.loadFromFile("Graphics/player.png");
	Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(580, 720);

	side playerSide = side::LEFT;

	Texture textureRIP;
	textureRIP.loadFromFile("Graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	Texture textureAxe;
	textureAxe.loadFromFile("Graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	Texture textureLog;
	textureLog.loadFromFile("Graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	bool acceptInput = false;

	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("Sounds/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("Sounds/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("Sounds/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(branchTexture);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}

	while (window.isOpen()) {

		// Handle Input

		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::KeyReleased && !paused) {
				acceptInput = true;

				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			paused = false;

			score = 0;

			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			timeRemaining = 6;

			for (int i = 1; i < NUM_BRANCHES; i++) {
				branchPositions[i] = side::NONE;
			}

			spriteRIP.setPosition(675, 2000);
			playerSprite.setPosition(580, 720);

			acceptInput = true;
		}

		if (acceptInput) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				playerSide = side::RIGHT;

				score++;

				std::stringstream ss;
				ss << "Score = " << score;
				scoreText.setString(ss.str());

				timeRemaining += (2 / score) + 1.5;

				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				playerSprite.setPosition(1200, 720);

				UpdateBranches(score);

				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				chop.play();
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				playerSide = side::LEFT;

				score++;

				std::stringstream ss;
				ss << "Score = " << score;
				scoreText.setString(ss.str());

				timeRemaining += (2 / score) + 1.5;

				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				playerSprite.setPosition(580, 720);

				UpdateBranches(score);

				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;

				chop.play();
			}
		}

		// Update the Scene

		if (!paused) {
			Time dt = clock.restart();

			timeRemaining -= dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarWidtdhPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f) {
				paused = true;

				messageText.setString("Out of time!");

				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				outOfTime.play();
			}

			if (!beeActive) {
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				beeSprite.setPosition(2000, height);
				beeActive = true;
			}
			else {
				beeSprite.setPosition(beeSprite.getPosition().x - (beeSpeed * dt.asSeconds()), beeSprite.getPosition().y);
				if (beeSprite.getPosition().x < -100) {
					beeActive = false;
				}
			}

#pragma region Cloud Updates

			if (!cloud1Active) {
				srand((int)time(0));
				cloud1Speed = (rand() % 200);

				srand((int)time(0) * 10);
				float height = (rand() % 150);
				cloudSprite1.setPosition(-200, height);
				cloud1Active = true;
			}
			else {
				cloudSprite1.setPosition(cloudSprite1.getPosition().x + (cloud1Speed * dt.asSeconds()), cloudSprite1.getPosition().y);
				if (cloudSprite1.getPosition().x > 1920) {
					cloud1Active = false;
				}
			}

			if (!cloud2Active) {
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				srand((int)time(0) * 20);
				float height = (rand() % 150);
				cloudSprite2.setPosition(-200, height);
				cloud2Active = true;
			}
			else {
				cloudSprite2.setPosition(cloudSprite2.getPosition().x + (cloud2Speed * dt.asSeconds()), cloudSprite2.getPosition().y);
				if (cloudSprite2.getPosition().x > 1920) {
					cloud2Active = false;
				}
			}

			if (!cloud3Active) {
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				srand((int)time(0) * 30);
				float height = (rand() % 150);
				cloudSprite3.setPosition(-200, height);
				cloud3Active = true;
			}
			else {
				cloudSprite3.setPosition(cloudSprite3.getPosition().x + (cloud3Speed * dt.asSeconds()), cloudSprite3.getPosition().y);
				if (cloudSprite3.getPosition().x > 1920) {
					cloud3Active = false;
				}
			}

#pragma endregion

			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150;
				if (branchPositions[i] == side::LEFT) {
					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT) {
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else {
					branches[i].setPosition(3000, height);
				}
			}

			if (logActive) {
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000) {
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			if (branchPositions[5] == playerSide) {
				paused = true;
				acceptInput = false;

				spriteRIP.setPosition(525, 760);

				playerSprite.setPosition(2000, 660);

				messageText.setString("SQUASHED!!");

				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				death.play();
			}
		}

		// Clear everything from last frame
		window.clear();

		// Draw the Scene
		window.draw(backgroundSprite);

		window.draw(cloudSprite1);
		window.draw(cloudSprite2);
		window.draw(cloudSprite3);

		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}

		window.draw(treeSprite);

		window.draw(playerSprite);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		window.draw(spriteRIP);

		window.draw(beeSprite);

		window.draw(scoreBar);
		window.draw(scoreText);
		window.draw(timeBar);

		if (paused) {
			window.draw(messageText);
		}

		// Show everything we just draw
		window.display();
	}

	return 0;
}

void UpdateBranches(int seed) {
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}

	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r) {
		case 0:
			branchPositions[0] = side::LEFT;
		case 1:
			branchPositions[0] = side::RIGHT;
		default:
			branchPositions[0] = side::NONE;
			break;
	}
}
