#include "Snake.h"

void Snake::LoadSounds()
{
	if (!m_eatBuffer.loadFromFile("Sounds/eat.wav"))
	{
		system("pause");
	}
	if (!m_powerUpBuffer.loadFromFile("Sounds/powerup.wav"))
	{
		system("pause");
	}
	if (!m_deathBuffer.loadFromFile("Sounds/death2.wav"))
	{
		system("pause");
	}
	if (!m_playerDeathBuffer.loadFromFile("Sounds/death3.wav"))
	{
		system("pause");
	}

	m_eatSFX.setBuffer(m_eatBuffer);
	m_powerUpSFX.setBuffer(m_powerUpBuffer);
	m_deathSFX.setBuffer(m_deathBuffer);
	m_playerDeathSFX.setBuffer(m_playerDeathBuffer);
	m_playerDeathSFX.setVolume(50);
	m_deathSFX.setVolume(50);
}

void Snake::Update(std::vector<Snake*> snakes, std::vector<Collectable*> collectables)
{
	m_snakes = snakes;
	m_collectables = collectables;

	if(m_mainClock.getElapsedTime().asMilliseconds() > 200)
	{
		if (m_isAlive)
		{
			ProcessSnake();
		}
		else //Snake is Dead
		{
			DeathSequence();
		}
		m_mainClock.restart();
	}
}

void Snake::ProcessSnake()
{
	if(m_isElectric)
	{
		CheckFXTimer();
	}

	if (m_isPlayer) 
	{

	}
	else
	{
		SnakeAISequence();
	}
	MoveSnake();
}

void Snake::MoveSnake()
{
	int tailIndex = m_snakeSquares.size() - 1;

	sf::Vector2f headPos = m_snakeSquares[0]->GetPos();
	sf::Vector2f newPos;
	SnakeSquare* temp = m_snakeSquares[0];

	switch (m_dir)
	{
	case Edirections::UP:
		headPos.y = headPos.y - m_squareSize.y;

		if (headPos.y < 5)//Check Border Collsion
		{
			headPos.y = 5;
			m_isAlive = false;
		}
		break;
	case Edirections::DOWN:
		headPos.y = headPos.y + m_squareSize.y;

		if (headPos.y > 595)//Check Border Collsion
		{
			headPos.y = 595;
			m_isAlive = false;
		}

		break;
	case Edirections::LEFT:
		headPos.x = headPos.x - m_squareSize.x;

		if ((headPos.x) <= 5)//Check Border Collsion
		{
			headPos.x = 5;
			m_isAlive = false;
		}

		break;
	case Edirections::RIGHT:
		headPos.x = headPos.x + m_squareSize.x;

		if (headPos.x > 795)//Check Border Collsion
		{
			headPos.x = 795;
			m_isAlive = false;
		}
		break;
	default:
		break;
	}

	newPos = sf::Vector2f(headPos.x, headPos.y);
	m_snakeSquares[tailIndex]->SetPos(newPos);

	//Set the tail to be the head and clear the empty space at the back
	m_snakeSquares.insert(m_snakeSquares.begin(), m_snakeSquares[tailIndex]);
	m_snakeSquares.pop_back();

	ProcessOverlaps(newPos);
}

void Snake::ProcessOverlaps(sf::Vector2f newPos)
{
	if (m_isAlive)
	{
		for (Collectable* collectable : m_collectables) //Check Overlaps with Collectables
		{
			if ((collectable->GetPos() == m_snakeSquares[0]->GetPos()) && collectable->GetActive())
			{
				collectable->SetActive(false);
				if (collectable->GetType() == Collectable::Etype::FOOD)
				{
					for (size_t i = 0; i < collectable->GetAmount(); i++)
					{
						this->Grow();
					}
					m_eatSFX.play();
				}
				else
				{
					m_powerUpSFX.play();
					m_isElectric = true;
					m_electricClock.restart();
				}
			}
		}

		for (Snake* snake : m_snakes) //Check Overlaps with Snakes
		{
			if (snake->CheckCollision(newPos, snake, 5))
			{
				if(m_isPlayer)
				{
					m_playerDeathSFX.play();
				}
				else
				{
					m_deathSFX.play();
				}
				
				Die();
			}
		}


		for (Snake* snake : m_snakes) //Check Overlaps with Snakes
		{
			if(snake != this && snake->m_isElectric)
			{
				if (CheckBodyCollision(snake))
				{
					if (m_isPlayer)
					{
						m_playerDeathSFX.play();
					}
					else
					{
						m_deathSFX.play();
					}
					Die();
				}
			}
		}
	}
}

bool Snake::CheckBodyCollision(Snake* snake)
{
	std::vector<SnakeSquare*> snakeSquares = snake->GetSnakeSquares();

	for(SnakeSquare* snakeSquare : snakeSquares)
	{
		if(CheckCollision(snakeSquare->GetPos(), snake, 25))
		{
			return true;
		}
	}
	return false;
}

bool Snake::CheckCollision(sf::Vector2f checkPos, Snake* snake, float checkRange) //Only need to check collision with the head
{
	if (checkPos.x <= 30 || checkPos.x >= 700) {
		return true;
	}

	if (checkPos.y <= 30 || checkPos.y >= 570) {
		return true;
	}
	
	int headCollision = 0;
	
	for (SnakeSquare* snakeSquare : m_snakeSquares)
	{
		sf::Vector2f snakeSquarePos = snakeSquare->GetPos();
		if (((snakeSquarePos.x >= checkPos.x - checkRange) && (snakeSquarePos.x <= checkPos.x + checkRange)) &&
			((snakeSquarePos.y >= checkPos.y - checkRange) && (snakeSquarePos.y <= checkPos.y + checkRange)))
		{
			if (checkPos == m_snakeSquares[0]->GetPos() && this == snake)
			{
				headCollision++;
			}
			else
			{
				return true;
			}
		}
		
		if (headCollision > 1)
		{
			return true;
		}
	}
	return false; //There is no collision
}

void Snake::Grow()
{
	sf::Vector2f tailPos = m_snakeSquares[0]->GetPos();
	sf::Vector2f newPos;

	switch (m_dir)
	{
	case Edirections::UP:
		newPos = sf::Vector2f(tailPos.x, tailPos.y + m_squareSize.y);
		break;
	case Edirections::DOWN:
		newPos = sf::Vector2f(tailPos.x, tailPos.y - m_squareSize.y);
		break;
	case Edirections::LEFT:
		newPos = sf::Vector2f(tailPos.x + m_squareSize.x, tailPos.y);
		break;
	case Edirections::RIGHT:
		newPos = sf::Vector2f(tailPos.x - m_squareSize.x, tailPos.y);
		break;
	default:
		break;
	}
	m_snakeSquares.push_back(new SnakeSquare(newPos, m_colour, m_squareSize));

	m_score++;
}

void Snake::DeathSequence()
{
	if (!m_isVanished)
	{
		if (m_deathClock.getElapsedTime().asMilliseconds() > 100)
		{
			m_snakeSquares.pop_back();
			m_deathClock.restart();
			if (m_snakeSquares.size() < 1)
			{
				m_isVanished = true;
			}
			m_score--;
		}
	}
	else
	{
		Die();
	}
}

void Snake::Die()
{
	m_isAlive = false;
}

void Snake::Reset()
{
	std::cout << "RESET";

	while(m_snakeSquares.size() != 0)
	{
		m_snakeSquares.pop_back();
	}

	m_snakeSquares.push_back(new SnakeSquare(m_pos, m_colour, m_squareSize));
	m_score = 1;

	m_isAlive = true;
	m_isVanished = false;
	m_isElectric = false;
}

int Snake::GetLength()
{
	return m_snakeSquares.size();
}

int Snake::GetScore()
{
	return m_score;
}

bool Snake::GetIsAlive()
{
	return m_isAlive;
}

Snake::Edirections Snake::GetDir()
{
	return m_dir;
}

std::vector<SnakeSquare*> Snake::GetSnakeSquares()
{
	return m_snakeSquares;
}

sf::Color Snake::GetColour()
{
	return m_colour;
}

void Snake::SetIsElectric(bool state)
{
	m_isElectric = state;
}

void Snake::CheckFXTimer()
{
	if(m_electricClock.getElapsedTime().asSeconds() > 5)
	{
		m_isElectric = false;
	}
}

void Snake::SnakeAISequence()
{
	FindBestCollectable();
	CalculateDir();
}

void Snake::FindBestCollectable()
{
	float m_AI_bestDist = 10000000;

	for (Collectable* collectable : m_collectables)
	{
		float curDist;
		float xDist = collectable->GetPos().x - m_snakeSquares[0]->GetPos().x;
		float yDist = collectable->GetPos().y - m_snakeSquares[0]->GetPos().y;
		
		curDist = sqrt((xDist*xDist) + (yDist*yDist));

		if (curDist < m_AI_bestDist && collectable->GetActive())
		{
			m_AI_bestDist = curDist;
			m_AI_xDist = xDist;
			m_AI_yDist = yDist;
		}
	}
}

void Snake::CalculateDir()
{
	//BEST POSSIBLE DIR
	if(abs(m_AI_xDist) > abs(m_AI_yDist))
	{
		if(m_AI_xDist < 0) //LEFT
		{
			m_dir = Edirections::LEFT;
		}
		else//RIGHT
		{
			m_dir = Edirections::RIGHT;
		}
	}
	else
	{
		if (m_AI_yDist < 0) //LEFT
		{
			m_dir = Edirections::UP;
		}
		else//RIGHT
		{
			m_dir = Edirections::DOWN;
		}
	}

	if(CheckPotentialCollisions(CalculateNextMove()))
	{
		for (int i = 0; i < 4; i++)
		{
			m_dir = (Edirections)i;

			if(!CheckPotentialCollisions(CalculateNextMove()))
			{
				return;	
			}
		}
	}
}

sf::Vector2f Snake::CalculateNextMove()
{
	sf::Vector2f nextMove = m_snakeSquares[0]->GetPos();

	switch (m_dir)
	{
	case Snake::UP:
		nextMove.y -= m_squareSize.y;
		break;
	case Snake::DOWN:
		nextMove.y += m_squareSize.y;
		break;
	case Snake::LEFT:
		nextMove.x -= m_squareSize.x;
		break;
	case Snake::RIGHT:
		nextMove.x += m_squareSize.x;
		break;
	default:
		break;
	}

	return nextMove;
}

bool Snake::CheckPotentialCollisions(sf::Vector2f checkPos)
{
	if (checkPos.x <= 10 || checkPos.x >= 790) 
	{
		return true;
	}

	if (checkPos.y >= 590 || checkPos.y <= 10) 
	{
		return true;
	}

	for (Snake* snake : m_snakes)
	{
		int range = 5;
		if ((snake->m_isElectric) && (snake != this))
		{
			range = 25;
		}

		if (snake->CheckCollision(checkPos, NULL, range))
		{
			return true;
		}
	}
	return false;
}

void Snake::ChangeDirection(Edirections dir)
{
	m_dir = dir;
}

void Snake::Render(sf::RenderWindow& window)
{
	if(m_isElectric)
	{
		for (SnakeSquare* snakeSquare : m_snakeSquares)
		{
			snakeSquare->RenderElectricFX(window);
		}
	}


	for (SnakeSquare* snakeSquare : m_snakeSquares)
	{
		snakeSquare->RenderSnakeSquare(window);
	}
}
