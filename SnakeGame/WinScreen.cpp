#include "WinScreen.h"

void WinScreen::Render(sf::RenderWindow& window)
{
	window.draw(m_gameOver);
	if(m_winners.size() > 0)
	{
		m_winnerIs.setString("CONGRATULATIONS: ");
	}

	window.draw(m_winnerIs);

	float scale = (abs(sin(m_time.getElapsedTime().asMilliseconds() / 1500.0f)) + 10.0f) * 0.1;

	if (scale < 0)
	{
		scale *= -1;
	}

	m_prompt.setScale(scale, scale);

	window.draw(m_prompt);

	sf::Vector2f snakeIconPos = sf::Vector2f(120, 300);

	for(Snake* snake : m_winners)
	{
		m_snakeSprite.setColor(snake->GetColour());
		window.draw(m_snakeSprite);
		m_snakeSprite.setPosition(snakeIconPos);
		snakeIconPos.x += 50;
	}
}

void WinScreen::SetWinners(std::vector<Snake*> winners)
{
	m_winners = winners;
}
