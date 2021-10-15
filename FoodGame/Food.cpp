#include "Food.h"

void Food::update(char direction) {
	switch (direction) {
	case 'r':
		position.x += 1;
	case 'l':
		position.x -= 1;
	case 'd':
		position.y += 1;
	case 'u':
		position.x -= 1;
	}
}

void Food::draw(sf::RenderWindow &window) {
	sprite.setPosition(position.x * cellSize.x, position.y * cellSize.y);
	window.draw(sprite);
}

Food::Food(sf::Vector2f cellSize, sf::Color color) {
	this->cellSize = cellSize;
	this->sprite.setSize(cellSize);
	this->sprite.setFillColor(color);
}
