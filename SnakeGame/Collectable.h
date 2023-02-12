#pragma once
#include <SFML/Graphics.hpp>


class Collectable
{
protected:
	bool m_isActive = true;
	bool m_isRenewing = false;

	int m_amount = 1;

	sf::Clock m_clock;

	sf::Vector2f m_pos;
	sf::Vector2f m_squareSize = sf::Vector2f(10, 10);
	std::vector<sf::Vector2f> m_takenPositions;
	sf::Color m_typeColour;
	sf::Color m_curColour = sf::Color::White;
public:
	enum Etype
	{
		FOOD,
		BATTERY
	};

	Etype m_type;

	void Update(std::vector<sf::Vector2f> positions);
	void Renew();
	void Randomise(std::vector<sf::Vector2f> positions);
	
	int GetAmount();
	sf::Vector2f GetPos();
	sf::Vector2f GetSize();
	bool GetActive();
	Etype GetType();

	void SetColour(sf::Color colour);
	void SetActive(bool isActive);
	
	void Render(sf::RenderWindow& window);
};

