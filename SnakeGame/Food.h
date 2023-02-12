#pragma once
#include <iostream>
#include "Collectable.h"
class Food :
    public Collectable
{
private:

public:
    Food(std::vector<sf::Vector2f> pos)
    {
        Randomise(pos);
        
        std::cout << m_amount;
        m_typeColour = sf::Color::White;
        SetColour(m_typeColour);
        m_type = Etype::FOOD;
    }
};

