#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

class Menu
{
private:
	sf::Text m_title;
	sf::Text m_subtitle;
	sf::Text m_prompt;
	sf::Text m_prompt2;
	sf::Font m_font;

	sf::Clock m_time;
public:



	Menu()
	{
		if (!m_font.loadFromFile("square_pixel-7.ttf"))
		{

		}

		m_title.setFont(m_font);
		m_title.setColor(sf::Color(255, 222, 173));
		m_title.setCharacterSize(60);
		m_title.setPosition(sf::Vector2f(115, 200));
		m_title.setString("ELECTRIC-SNAKES");

		m_subtitle.setFont(m_font);
		m_subtitle.setColor(sf::Color(255, 255, 240));
		m_subtitle.setCharacterSize(30);
		m_subtitle.setPosition(sf::Vector2f(115, 190));
		m_subtitle.setString("ben scrafton's");

		m_prompt.setFont(m_font);
		m_prompt.setColor(sf::Color(255, 255, 240));
		m_prompt.setCharacterSize(30);
		m_prompt.setPosition(sf::Vector2f(115, 300));
		m_prompt.setString("press (p) to play");

		m_prompt2.setFont(m_font);
		m_prompt2.setColor(sf::Color(255, 255, 240));
		m_prompt2.setCharacterSize(30);
		m_prompt2.setPosition(sf::Vector2f(115, 400));
		m_prompt2.setString("press (q) to quit");

	}
	void Render(sf::RenderWindow& window);
};

