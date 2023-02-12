#include "Border.h"

void Border::Render(sf::RenderWindow& window)
{
	sf::RectangleShape border;
	sf::Vector2f originPos = sf::Vector2f(m_size.x / 2, m_size.y / 2);

	border.setFillColor(m_colour);
	border.setSize(m_size);
	border.setOrigin(originPos);
	border.setPosition(m_pos);
	window.draw(border);
}
