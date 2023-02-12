#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Snake.h";

class ScoreBoard
{
private:
	std::vector<Snake*> m_snakes;
	sf::Text m_scoreText;
	sf::Text m_title;
	sf::Text m_mainTitle;
	sf::Text m_playerTitle;
	sf::Text m_AiTitle;
	sf::Font m_font;
	sf::Texture m_snakeIcon;
	sf::Sprite m_snakeSprite;
	sf::RectangleShape m_square;

	sf::Clock m_clock;
	sf::Text m_timerText;
	int m_timeRemaining;

public:
	ScoreBoard(std::vector<Snake*> snakes)
	{
		m_snakes = snakes;

		if (!m_font.loadFromFile("square_pixel-7.ttf"))
		{

		}

		if (!m_snakeIcon.loadFromFile("SN100.png"))
		{
			system("pause");
		}

		m_timerText.setCharacterSize(30);
		m_timerText.setColor(sf::Color::White);
		m_timerText.setFont(m_font);
		m_timerText.setPosition(sf::Vector2f(725, 20));

		m_snakeSprite.setTexture(m_snakeIcon);
		m_snakeSprite.setPosition(sf::Vector2f(705, 55));
		m_snakeSprite.setScale(sf::Vector2f(0.6, 0.6));

		m_scoreText.setCharacterSize(30);
		m_scoreText.setFont(m_font);
		m_scoreText.setColor(sf::Color::White);
		m_scoreText.setPosition(sf::Vector2f(545, 100));

		m_title.setCharacterSize(40);
		m_title.setFont(m_font);
		m_title.setColor(sf::Color::White);
		m_title.setString("SCORE:");
		m_title.setPosition(sf::Vector2f(745, 60));

		m_playerTitle.setCharacterSize(25);
		m_playerTitle.setFont(m_font);
		m_playerTitle.setColor(sf::Color::White);
		m_playerTitle.setString("PLAYER:");
		m_playerTitle.setPosition(sf::Vector2f(755, 110));

		m_AiTitle.setCharacterSize(25);
		m_AiTitle.setFont(m_font);
		m_AiTitle.setColor(sf::Color::White);
		m_AiTitle.setString("AI:");
		m_AiTitle.setPosition(sf::Vector2f(785, 175));

		m_mainTitle.setCharacterSize(40);
		m_mainTitle.setFont(m_font);
		m_mainTitle.setColor(sf::Color::White);
		m_mainTitle.setString("electric-snakes");
		m_mainTitle.setPosition(sf::Vector2f(200, -17));
	}
	void ResetClock();

	void Render(sf::RenderWindow& window);
};

