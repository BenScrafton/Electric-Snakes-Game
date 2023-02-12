#pragma once
#include "Collectable.h"
class Battery :
    public Collectable
{
private:
public:
    Battery(std::vector<sf::Vector2f> pos)
    {
        Randomise(pos);
        m_typeColour = sf::Color::Cyan;
        SetColour(m_typeColour);
        m_type = Etype::BATTERY;
    }
};

