#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp";
#include "SnakeSquare.h";
#include "Collectable.h";

class Snake
{
private:
	bool m_isAlive = true;
	bool m_isPlayer = false;
	bool m_isVanished = false;
	bool m_isElectric = false;

	int m_score = 0;

	sf::Vector2f m_pos;
	sf::Vector2f m_squareSize;
	sf::Color m_colour;

	sf::Clock m_mainClock;
	sf::Clock m_electricClock;
	sf::Clock m_deathClock;

	std::vector<SnakeSquare*> m_snakeSquares;

	std::vector<Snake*> m_snakes;
	std::vector<Collectable*> m_collectables;

	//AI
	float m_AI_xDist;
	float m_AI_yDist;

	//Sound
	sf::SoundBuffer m_eatBuffer;
	sf::SoundBuffer m_powerUpBuffer;
	sf::SoundBuffer m_deathBuffer;
	sf::SoundBuffer m_playerDeathBuffer;

	sf::Sound m_eatSFX;
	sf::Sound m_powerUpSFX;
	sf::Sound m_deathSFX;
	sf::Sound m_playerDeathSFX;

public:

	std::vector<SnakeSquare*> m_allSnakeSquares;

	enum Edirections
	{
		UP, //0
		DOWN, //1
		LEFT, //2
		RIGHT //3
	};

	Edirections m_dir = Edirections::LEFT;

	Snake(sf::Vector2f pos, sf::Color colour, sf::Vector2f squareSize, bool isPlayer)
	{
		m_isPlayer = isPlayer;
		m_pos = pos;
		m_colour = colour;
		m_squareSize = squareSize;

		m_score = 1;
		m_snakeSquares.push_back(new SnakeSquare(m_pos, m_colour, m_squareSize));

		LoadSounds();
	}

	void LoadSounds();
	void Update(std::vector<Snake*> snakes, std::vector<Collectable*> collectables);
	void ProcessSnake();
	void MoveSnake();
	void ProcessOverlaps(sf::Vector2f newPos);
	bool CheckBodyCollision(Snake* snake);
	bool CheckCollision(sf::Vector2f checkPos, Snake* snake, float checkRange);
	void Grow();
	void DeathSequence();
	void Die();
	void Reset();

	int GetLength();
	int GetScore();
	bool GetIsAlive();
	Edirections GetDir();
	std::vector<SnakeSquare*> GetSnakeSquares();
	sf::Color GetColour();
	void SetIsElectric(bool state);
	void CheckFXTimer();


	//AI
	void SnakeAISequence();
	void FindBestCollectable();
	void CalculateDir();
	sf::Vector2f CalculateNextMove();
	bool CheckPotentialCollisions(sf::Vector2f checkPos);


	void ChangeDirection(Edirections dir);
	void Render(sf::RenderWindow& window);

};

