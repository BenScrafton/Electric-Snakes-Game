#include "SnakeSquare.h"

sf::Vector2f SnakeSquare::GetPos()
{
    return m_pos;
}

void SnakeSquare::SetPos(sf::Vector2f pos)
{
    m_pos = pos;
}

sf::Vector2f SnakeSquare::GetSize()
{
	return m_squareSize;
}

void SnakeSquare::RenderSnakeSquare(sf::RenderWindow& window)
{

	sf::Vector2f originPos = sf::Vector2f(m_squareSize.x / 2, m_squareSize.y / 2);
	sf::RectangleShape square;

	square.setFillColor(m_colour);
	square.setSize(m_squareSize);
	square.setOrigin(originPos);
	square.setPosition(m_pos);
	window.draw(square);
}

void SnakeSquare::RenderElectricFX(sf::RenderWindow& window) 
{
	sf::RectangleShape electricSquare;
	sf::Vector2f electricOriginPos = sf::Vector2f(50 / 2, 50 / 2);

	electricSquare.setFillColor(sf::Color(0, 255, 255, 25));
	electricSquare.setSize(sf::Vector2f(50, 50));
	electricSquare.setOrigin(electricOriginPos);
	electricSquare.setPosition(m_pos);
	window.draw(electricSquare);

	electricOriginPos = sf::Vector2f(30 / 2, 30 / 2);

	electricSquare.setFillColor(sf::Color(0, 255, 255, 50));
	electricSquare.setSize(sf::Vector2f(30, 30));
	electricSquare.setOrigin(electricOriginPos);
	electricSquare.setPosition(m_pos);
	window.draw(electricSquare);
}

