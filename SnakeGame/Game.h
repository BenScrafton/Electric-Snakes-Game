#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp";
#include "Snake.h";
#include "Collectable.h";
#include "Food.h";
#include "Battery.h";
#include "Border.h";
#include "ScoreBoard.h";
#include "Menu.h";
#include "WinScreen.h";

class Game
{
private:	
	int m_numSnakes = 6;
	int m_numCollectables = 10;
	int m_numFood = 9;
	int m_numPlayers = 1;

	bool m_gameOver;

	sf::Vector2f m_snakeSize = sf::Vector2f(10, 10);

	std::vector<Snake*> m_snakes;
	std::vector<SnakeSquare*> m_allSnakesSquares;
	std::vector<Collectable*> m_collectables;
	std::vector<Border*> m_borders;
	std::vector<sf::Vector2f> m_collectablePositions;
	std::vector<Snake*> m_winners;

	sf::Clock m_clock;
	sf::Clock m_gameTimer;
	ScoreBoard* m_scoreboard;
	Menu* m_menu;
	WinScreen* m_winScreen;

	//Sound
	sf::SoundBuffer m_musicBuffer;
	sf::SoundBuffer m_menuMusicBuffer;
	sf::SoundBuffer m_gameOverBuffer;

	sf::Sound m_musicSFX;
	sf::Sound m_menuMusicSFX;
	sf::Sound m_gameOverSFX;

public:
	enum GameState
	{
		MENU,
		PLAYING,
		GAMEOVER
	};

	GameState gameState = MENU;

	void Run();
	void Render(sf::RenderWindow& window);
	void LoadSounds();
	void ClearMemory();

	void CheckInputs();
	void Update();
	void CheckCollisions();
	void SetAllSnakeSquares();
	void CreateBorders();
	void CreateSnakes();
	void CreateCollectables();
	void CheckGameOver();
	void ProcessWinner(Snake* snake);
	void ResetGame();
};

