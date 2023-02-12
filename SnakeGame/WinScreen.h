#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Snake.h";

class WinScreen
{
private:
	sf::Text m_gameOver;
	sf::Text m_winnerIs;
	sf::Text m_prompt;
	sf::Font m_font;

	sf::Texture m_snakeIcon;
	sf::Sprite m_snakeSprite;

	sf::Clock m_time;
	std::vector<Snake*> m_winners;

public:

	WinScreen()
	{
		if (!m_font.loadFromFile("square_pixel-7.ttf"))
		{

		}

		if (!m_snakeIcon.loadFromFile("SN100.png"))
		{
			system("pause");
		}

		m_gameOver.setFont(m_font);
		m_gameOver.setColor(sf::Color(255, 222, 173));
		m_gameOver.setCharacterSize(60);
		m_gameOver.setPosition(sf::Vector2f(115, 100));
		m_gameOver.setString("GAME-OVER");

		m_snakeSprite.setTexture(m_snakeIcon);
		m_snakeSprite.setPosition(sf::Vector2f(450, 300));
		m_snakeSprite.setScale(sf::Vector2f(0.6, 0.6));

		m_winnerIs.setFont(m_font);
		m_winnerIs.setColor(sf::Color(255, 255, 240));
		m_winnerIs.setCharacterSize(30);
		m_winnerIs.setPosition(sf::Vector2f(115, 250));
		m_winnerIs.setString("No one Wins");

		m_prompt.setFont(m_font);
		m_prompt.setColor(sf::Color(255, 255, 240));
		m_prompt.setCharacterSize(30);
		m_prompt.setPosition(sf::Vector2f(115, 400));
		m_prompt.setString("press (c) to continue");
	}

	void SetWinners(std::vector<Snake*> winners);
	void Render(sf::RenderWindow& window);
};

