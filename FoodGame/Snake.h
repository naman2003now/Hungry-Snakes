#pragma once
#include<SFML/Graphics.hpp>
#include<vector>


class Snake
{
private:
	sf::Vector2f position;
	sf::Vector2f cellSize;
	sf::RectangleShape sprite;
	void move(char direction);
	void nextMove(std::vector<Snake>);

public:
	std::vector<sf::Vector2f> body;
	Snake(sf::Vector2f, sf::Color);
	void draw(sf::RenderWindow&);
	void update(std::vector<Snake>);
};

