#include "Food.h"

void Food::update(char direction) {
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
}

void Food::draw(sf::RenderWindow &window) {
	sprite.setPosition(position.x * cellSize.x, position.y * cellSize.y);
	window.draw(sprite);
}

Food::Food(sf::Vector2f cellSize, sf::Color color) {
	this->position = sf::Vector2f(10, 10);
	this->cellSize = cellSize;
	this->sprite.setSize(cellSize);
	this->sprite.setFillColor(color);
}
