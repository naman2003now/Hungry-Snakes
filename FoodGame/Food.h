#pragma once
#include<SFML/Graphics.hpp>

class Food
{
private:
	sf::Vector2f position = sf::Vector2f(10, 10);
	sf::RectangleShape sprite;
	sf::Vector2f cellSize;

public:
	Food(sf::Vector2f, sf::Color);
	void update(char);
	void draw(sf::RenderWindow&);
};

