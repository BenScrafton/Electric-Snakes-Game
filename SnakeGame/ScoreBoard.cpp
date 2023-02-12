#include "ScoreBoard.h";
#include <string>
using namespace std;

void ScoreBoard::Render(sf::RenderWindow& window)
{
	sf::Vector2f posText = sf::Vector2f(800, 140);
	sf::Vector2f posSprite = sf::Vector2f(750, 145);
	sf::FloatRect bounds;

	int i = 0;

	for(Snake* snake : m_snakes)
	{
		i++;

		if (i > 1)
		{
			posText.y += 75;
			posSprite.y += 75;
		}
		
		if(snake->GetScore() < 10)
		{
			m_scoreText.setString("0" + to_string(snake->GetScore()));
		}
		else
		{
			m_scoreText.setString(to_string(snake->GetScore()));
		}
		
		bounds = m_scoreText.getLocalBounds();
		
		posText.x = 850 - bounds.width;
		
		m_scoreText.setPosition(posText);
		m_scoreText.setColor(snake->GetColour());

		m_snakeSprite.setPosition(posSprite);
		m_snakeSprite.setColor(snake->GetColour());

		window.draw(m_scoreText);
		window.draw(m_snakeSprite);
	}

	m_timeRemaining = 90 - (int)m_clock.getElapsedTime().asSeconds();

	if(m_timeRemaining <= 0)
	{
		m_timeRemaining = 0;
	}

	if(m_timeRemaining < 10)
	{
		m_timerText.setString("TIME : 0" + to_string(m_timeRemaining));
	}
	else
	{
		m_timerText.setString("TIME : " + to_string(m_timeRemaining));
	}
	
	window.draw(m_timerText);
	window.draw(m_title);
	window.draw(m_mainTitle);
	window.draw(m_playerTitle);
	window.draw(m_AiTitle);
}

void ScoreBoard::ResetClock()
{
	m_timeRemaining = 90;
	m_clock.restart();
}
