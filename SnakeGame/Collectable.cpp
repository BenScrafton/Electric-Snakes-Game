#include "Collectable.h"

void Collectable::Update(std::vector<sf::Vector2f> positions)
{
	m_takenPositions = positions;
	if(m_isRenewing)
	{
		Renew();
	}
}

void Collectable::Renew()
{
	if(m_type == Etype::FOOD)
	{
		if (m_clock.getElapsedTime().asSeconds() > 1)
		{
			Randomise(m_takenPositions);
			m_isRenewing = false;
			SetActive(true);
		}
	}
	else
	{
		if (m_clock.getElapsedTime().asSeconds() > 5)
		{
			Randomise(m_takenPositions);
			m_isRenewing = false;
			SetActive(true);
		}
	}
}

void Collectable::Randomise(std::vector<sf::Vector2f> positions)
{	
	m_pos = sf::Vector2f((rand() % 60) * 10 + 50, (rand() % 47) * 10 + 50);
	for(sf::Vector2f position : positions)
	{
		while(m_pos == position)
		{
			m_pos = sf::Vector2f((rand() % 60) * 10 + 50, (rand() % 47) * 10 + 50);
		}
	}
	
	m_amount = ((int)rand() % 2) + 1;

	if(m_type == FOOD)
	{
		if (m_amount == 1)
		{
			m_typeColour = sf::Color::White;
		}
		else
		{
			m_typeColour = sf::Color::Red;
		}
	}
}

sf::Vector2f Collectable::GetPos()
{
	return m_pos;
}

int Collectable::GetAmount()
{
	return m_amount;
}

sf::Vector2f Collectable::GetSize()
{
	return m_squareSize;
}

bool Collectable::GetActive()
{
	return m_isActive;
}

Collectable::Etype Collectable::GetType()
{
	return m_type;
}

void Collectable::SetColour(sf::Color colour)
{
	m_curColour = colour;
}

void Collectable::SetActive(bool isActive)
{
	m_isActive = isActive;

	if(!isActive)
	{
		m_curColour = sf::Color::Transparent;
		m_clock.restart();
		m_isRenewing = true;
	}
	else
	{
		m_curColour = m_typeColour;
	}
}

void Collectable::Render(sf::RenderWindow& window)
{
	sf::RectangleShape square;
	square.setOrigin(5, 5);
	square.setPosition(m_pos);
	square.setFillColor(m_curColour);
	square.setSize(m_squareSize);

	window.draw(square);
}
