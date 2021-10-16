#include "Snake.h"
#include <random>

void Snake::move(char direction) {
	switch (direction) {
	case 'r':
		position.x++;
		break;
	case 'l':
		position.x--;
		break;
	case 'd':
		position.y++;
		break;
	case 'u':
		position.y--;
		break;
	}
	for (int i = body.size() - 1; i > 0; i--) {
		body[i] = body[i - 1];
	}
	body[0] = position;
}

Snake::Snake(sf::Vector2f cellSize, sf::Color color) {
	float x = rand() % 20;
	this->position = sf::Vector2f(0, x);
	this->body.push_back(sf::Vector2f(0, x));
	this->body.push_back(sf::Vector2f(-1, x));
	this->body.push_back(sf::Vector2f(-2, x));
	this->body.push_back(sf::Vector2f(-3, x));
	this->cellSize = cellSize;
	this->sprite.setSize(cellSize);
	this->sprite.setFillColor(color);
}

void Snake::draw(sf::RenderWindow& window) {
	for (int i = 0; i < body.size(); i++) {
		sprite.setPosition(body[i].x * cellSize.x, body[i].y * cellSize.y);
		window.draw(sprite);
	}
}

void Snake::update(std::vector<Snake> friends) {
	move('r');
}
void Snake::nextMove(std::vector<Snake> friends) {

}

