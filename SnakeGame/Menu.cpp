#include "Menu.h"

void Menu::Render(sf::RenderWindow& window)
{
	window.draw(m_title);
	window.draw(m_subtitle);
	
	float scale = (abs(sin(m_time.getElapsedTime().asMilliseconds()/1500.0f)) + 10.0f) * 0.1;

	if(scale < 0)
	{
		scale *= -1;
	}

	m_prompt.setScale(scale, scale);
	
	window.draw(m_prompt2);
	window.draw(m_prompt);
}
