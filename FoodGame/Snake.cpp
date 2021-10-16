#include "Snake.h"
#include <random>
#include <math.h>
#include <time.h>

void Snake::move(char direction) {
	bool change = false;
	switch (direction) {
	case 'r':
		if (current_direction != 'l') {
			current_direction = 'r';
			position.x++;
			change = true;
			if (position.x >= gridSize.x) {
				position.x--;
				change = false;
			}
		}
		break;
	case 'l':
		if (current_direction != 'r'){
			current_direction = 'l';
			position.x--;
			change = true;
			if (position.x < 0) {
				position.x++; 
				change = false;
			}
		}
		break;
	case 'd':
		if (current_direction != 'u'){
			current_direction = 'd';
			position.y++;
			change = true;
			if (position.y >= gridSize.y) {
				position.y--;
				change = false;
			}
		}
		break;
	case 'u':
		if (current_direction != 'd'){
			current_direction = 'u';
			position.y--;
			change = true;
			if (position.y < 0) {
				position.y++; 
				change = false;
			}
		}
		break;
	}
	if (change) {
		for (int i = body.size() - 1; i > 0; i--) {
			body[i] = body[i - 1];
		}
		body[0] = position;
	}
}


Snake::Snake(sf::Vector2f cellSize, sf::Vector2f gridSize, sf::Color color, int searchSize) {
	srand(time(NULL));
	this->searchSize = searchSize;
	if (rand() % 2) {
		float x = rand() % (int)gridSize.x;
		this->gridSize = gridSize;
		this->position = sf::Vector2f(0, x);
		this->body.push_back(sf::Vector2f(0, x));
		this->body.push_back(sf::Vector2f(-1, x));
		this->body.push_back(sf::Vector2f(-2, x));
		current_direction = 'r';
	}
	else {
		float x = rand() % (int)gridSize.y;
		this->gridSize = gridSize;
		this->position = sf::Vector2f(x, 0);
		this->body.push_back(sf::Vector2f(x, -0));
		this->body.push_back(sf::Vector2f(x, -1));
		this->body.push_back(sf::Vector2f(x, -2));
		current_direction = 'd';
	}
	this->cellSize = cellSize;
	this->searchColor = sf::Color(45, 45, 45);

	if (rand() % 2) this->snakeColor = sf::Color(rand() % 255, 125, rand() % 255);
	else this->snakeColor = sf::Color(rand() % 255, rand() % 255, 125);

	this->home = sf::Vector2f(rand() % (int)gridSize.x, rand() % (int)gridSize.y);

	this->sprite.setSize(cellSize);
	this->sprite.setFillColor(color);
}

void Snake::draw(sf::RenderWindow &window) {
	sprite.setFillColor(snakeColor);
	for (int i = 0; i < body.size(); i++) {
		sprite.setPosition(body[i].x * cellSize.x, body[i].y * cellSize.y);
		window.draw(sprite);
	}
}

void Snake::drawBounds(sf::RenderWindow& window) {
	sprite.setFillColor(searchColor);
	for (int i = -searchSize; i <	searchSize; i++) {
		for (int j = -searchSize; j < searchSize; j++) {
			sprite.setPosition((position.x + i) * cellSize.x, (position.y - j) * cellSize.y);
			window.draw(sprite);
		}
	}
}

void Snake::update(std::vector<Snake> friends, sf::Vector2f foodPosition) {
	move(nextMove(friends, foodPosition));
}
char Snake::nextMove(std::vector<Snake> friends, sf::Vector2f foodPosition) {
	if (abs(position.x - foodPosition.x) <= 10 && abs(position.y - foodPosition.y) <= 10) {
		if (rand() % 2) {
			if (foodPosition.x > position.x) return 'r';
			if (foodPosition.x < position.x) return 'l';
			if (foodPosition.y > position.y) return 'd';
			if (foodPosition.y < position.y) return 'u';
		}
		else {
			if (foodPosition.y > position.y) return 'd';
			if (foodPosition.y < position.y) return 'u';
			if (foodPosition.x > position.x) return 'r';
			if (foodPosition.x < position.x) return 'l';
		}
	}
	else{
		if (rand() % 2) {
			if (home.x - rand()%8 + 4> position.x) return 'r';
			if (home.x - rand()%8 + 4< position.x) return 'l';
			if (home.y - rand()%8 + 4> position.y) return 'd';
			if (home.y - rand()%8 + 4< position.y) return 'u';
		}
		else {
			if (home.y - rand()%8 + 4> position.y) return 'd';
			if (home.y - rand()%8 + 4< position.y) return 'u';
			if (home.x - rand()%8 + 4> position.x) return 'r';
			if (home.x - rand()%8 + 4< position.x) return 'l';
		}
	}
}

