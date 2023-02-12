#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Border
{
private:
	sf::Color m_colour = sf::Color(43, 45, 47);
	sf::Vector2f m_size;
	sf::Vector2f m_pos;
public:

	Border(sf::Vector2f size, sf::Vector2f pos, sf::Color colour)
	{
		m_pos = pos;
		m_size = size;
		m_colour = colour;
	};

	void Render(sf::RenderWindow& window);
};
