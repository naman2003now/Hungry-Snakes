#include <SFML\Graphics.hpp>
#include <iostream>
#include "Snake.h"
#include "Food.h"

#define BGCOLOR sf::Color(50, 50, 50)
#define SNAKECOLOR sf::Color(250, 250, 250)
#define FOODCOLOR sf::Color(250, 50, 50)

int main() {

	int WINDOW_HEIGHT = 800;
	int WINDOW_WIDTH = 800;

	sf::Vector2f gridSize(40, 40);
	sf::Vector2f cellSize(WINDOW_WIDTH/gridSize.x, WINDOW_HEIGHT/gridSize.y);

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hungry Snakes");
	sf::Event event;
	
	char direction = 'r';
	
	sf::Clock frameTime;
	float frameRate = 10.0f;

	Food food(cellSize, FOODCOLOR);
	std::vector<Snake> allSnakes;
	allSnakes.push_back(Snake(cellSize, SNAKECOLOR));
	allSnakes.push_back(Snake(cellSize, SNAKECOLOR));

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
			for (int i = 0; i < allSnakes.size(); i++) {
				allSnakes[i].update(allSnakes);
			}
			frameTime.restart();
		}


		window.clear(BGCOLOR);
		for (int i = 0; i < allSnakes.size(); i++) {
			allSnakes[i].draw(window);
		}
		food.draw(window);
		window.display();
	}
	return 0;
}