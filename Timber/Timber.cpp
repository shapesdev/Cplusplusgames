#include <sstream>
#include <SFML/Graphics.hpp>

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

	messageText.setCharacterSize(75);
	messageText.setCharacterSize(100);

	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	Texture branchTexture;
	branchTexture.loadFromFile("Graphics/branch.png");

	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(branchTexture);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}

	while (window.isOpen()) {

		// Handle Input
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			paused = false;

			score = 0;
			timeRemaining = 6;
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

			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

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
		window.draw(beeSprite);

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
