#pragma once
#include <SFML/Graphics.hpp>

class SnakeSquare
{
private:
	sf::Vector2f m_pos;
	sf::Vector2f m_squareSize;
	sf::Color m_colour;

public:
	SnakeSquare(sf::Vector2f pos, sf::Color colour, sf::Vector2f squareSize)
	{
		m_pos = pos;
		m_colour = colour;
		m_squareSize = squareSize;
	}

	sf::Vector2f GetPos();
	sf::Vector2f GetSize();
	void SetPos(sf::Vector2f pos);

	void RenderSnakeSquare(sf::RenderWindow& window);
	void RenderElectricFX(sf::RenderWindow& window);
};

