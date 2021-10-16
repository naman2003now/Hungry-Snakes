#include <SFML\Graphics.hpp>
#include "Snake.h"
#include "Food.h"
#include<Windows.h>


#define BGCOLOR sf::Color(50, 50, 50)
#define SNAKECOLOR sf::Color(250, 250, 250)
#define FOODCOLOR sf::Color(250, 50, 50)

int main() {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	int WINDOW_HEIGHT = 800;
	int WINDOW_WIDTH = 800;

	sf::Vector2f gridSize(40, 40);
	sf::Vector2f cellSize(WINDOW_WIDTH/gridSize.x, WINDOW_HEIGHT/gridSize.y);

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hungry Snakes");
	sf::Event event;
	
	char direction = 'r';
	
	sf::Clock frameTime;
	float frameRate = 15.0f;

	sf::Clock snakeTime;
	float snakeRate = 10.0f;

	sf::Clock snakeSpwanner;
	float snakeSpawnTime = 10.0f;

	Food food(cellSize, FOODCOLOR);
	std::vector<Snake> allSnakes;
	allSnakes.push_back(Snake(cellSize, gridSize , SNAKECOLOR, 10));

	while (window.isOpen()) {
		while (window.pollEvent(event)) {

			//"X" to close the window
			if (event.type == sf::Event::Closed) window.close();
			
			//Keyboard events
			if (event.type == sf::Event::KeyPressed) {

				//Input keys for movement
				if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) direction = 'l';
				if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) direction = 'r';
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) direction = 'u';
				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) direction = 'd';
			}

		}

		//Update Every gameframe
		if (frameTime.getElapsedTime().asSeconds() > 1.0f / frameRate) {
			food.update(direction);
			bool gameOver = false;
			for (int i = 0; i < allSnakes.size(); i++) {
				for (int j = 0; j < allSnakes[i].body.size(); j++) {
					if (allSnakes[i].body[j] == food.position) {
						allSnakes.clear();
						allSnakes.push_back(Snake(cellSize, gridSize, SNAKECOLOR, 10));
						gameOver = true;
						break;
					}
				}
				if (gameOver) break;
			}

			frameTime.restart();
		}
		if (snakeTime.getElapsedTime().asSeconds() > 1.0f / snakeRate) {
			for (int i = 0; i < allSnakes.size(); i++) {
				allSnakes[i].update(allSnakes, food.position);
			}
			snakeTime.restart();
		}
		if (snakeSpwanner.getElapsedTime().asSeconds() > snakeSpawnTime) {
			allSnakes.push_back(Snake(cellSize, gridSize, SNAKECOLOR, 10));
			snakeSpwanner.restart();
		}


		window.clear(BGCOLOR);
		for (int i = 0; i < allSnakes.size(); i++) {
			allSnakes[i].drawBounds(window);
		}
		for (int i = 0; i < allSnakes.size(); i++) {
			allSnakes[i].draw(window);
		}
		food.draw(window);
		window.display();
	}
	return 0;
}
