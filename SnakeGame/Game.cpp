#include "Game.h"

void Game::Run()
{
    sf::RenderWindow window(sf::VideoMode(900, 600), "C++ Snake ICA : U0018197");
    std::cout << "SnakeGame: Starting" << std::endl;

    LoadSounds();
    CreateBorders();
    CreateCollectables();
    CreateSnakes();

    m_scoreboard = new ScoreBoard(m_snakes);
    m_menu = new Menu();
    m_winScreen = new WinScreen();

    // Main loop that continues until we call window.close()
    while (window.isOpen())
    {
        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        CheckInputs();

        if(gameState == GameState::MENU)
        {
            Render(window);
        }
        else if(gameState == GameState::PLAYING)
        {
            CheckGameOver();
            Update();
            Render(window);
        }
        else if(gameState == GameState::GAMEOVER)
        {
            Render(window);
        }

    }
    ClearMemory();
}

void Game::Render(sf::RenderWindow& window)
{ 
    window.clear();

    for(Border* border: m_borders)
    {
        border->Render(window);
    }

    if(gameState == GameState::MENU)
    {
        m_menu->Render(window);
    }
    else if(gameState == GameState::PLAYING)
    {
        for (Collectable* collectable : m_collectables)
        {
            collectable->Render(window);
        }

        for (Snake* snake : m_snakes)
        {
            snake->Render(window);
        }

        m_scoreboard->Render(window);
    }
    else if(gameState == GameState::GAMEOVER)
    {
        m_winScreen->Render(window);
    }

    window.display();
}

void Game::LoadSounds()
{
    if(!m_menuMusicBuffer.loadFromFile("Sounds/menuMusic.wav"))
    {
        system("pause");
    }

    if(!m_musicBuffer.loadFromFile("Sounds/background_music.wav"))
    {
        system("pause");
    }

    if(!m_gameOverBuffer.loadFromFile("Sounds/GameOver.wav"))
    {
        system("pause");
    }

    m_menuMusicSFX.setBuffer(m_menuMusicBuffer);
    m_musicSFX.setBuffer(m_musicBuffer);
    m_gameOverSFX.setBuffer(m_gameOverBuffer);
}

void Game::ClearMemory()
{
    m_allSnakesSquares.clear();
    m_snakes.clear();
    m_borders.clear();
    m_collectables.clear();
    m_winners.clear();
}

void Game::CheckInputs()
{
    if(gameState == GameState::PLAYING)
    {
        if (m_menuMusicSFX.getStatus() == sf::SoundSource::Status::Playing)
        {
            m_menuMusicSFX.stop();
        }

        //PLAYER 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (m_snakes[0]->GetLength() == 1 || m_snakes[0]->GetDir() != Snake::Edirections::DOWN))
        {
            m_snakes[0]->ChangeDirection(Snake::Edirections::UP);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (m_snakes[0]->GetLength() == 1 || m_snakes[0]->GetDir() != Snake::Edirections::UP))
        {
            m_snakes[0]->ChangeDirection(Snake::Edirections::DOWN);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (m_snakes[0]->GetLength() == 1 || m_snakes[0]->GetDir() != Snake::Edirections::RIGHT))
        {
            m_snakes[0]->ChangeDirection(Snake::Edirections::LEFT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (m_snakes[0]->GetLength() == 1 || m_snakes[0]->GetDir() != Snake::Edirections::LEFT))
        {
            m_snakes[0]->ChangeDirection(Snake::Edirections::RIGHT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            ResetGame();
            gameState = GameState::MENU;
        }
    }
    else if(gameState == GameState::MENU)
    {
        if(m_menuMusicSFX.getStatus() == sf::SoundSource::Status::Stopped)
        {
            m_menuMusicSFX.play();
        }

        if (m_musicSFX.getStatus() == sf::SoundSource::Status::Playing)
        {
            m_musicSFX.stop();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            ResetGame();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            exit(3);
        }
    }
    else if(gameState == GameState::GAMEOVER)
    {
        if (m_musicSFX.getStatus() == sf::SoundSource::Status::Playing)
        {
            m_musicSFX.stop();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {    
            gameState = GameState::MENU;
        }
    }

}

void Game::Update()
{
    m_collectablePositions.clear();

    if(m_musicSFX.getStatus() == sf::SoundSource::Status::Stopped)
    {
        m_musicSFX.play();
        m_musicSFX.setVolume(40);
    }

    for (Snake* snake : m_snakes) //Update Snakes
    {
        snake->Update(m_snakes, m_collectables);
    }

    for (Collectable* collectable : m_collectables) // Update Collectables
    {
        collectable->Update(m_collectablePositions);
        m_collectablePositions.push_back(collectable->GetPos());
    }
}

void Game::CreateBorders()
{
    m_borders.push_back(new Border(sf::Vector2f(100, 600), sf::Vector2f(750, 300), sf::Color(43, 47, 47))); //Right Border
    m_borders.push_back(new Border(sf::Vector2f(100, 600), sf::Vector2f(850, 300), sf::Color(43, 47, 47)));
 
    m_borders.push_back(new Border(sf::Vector2f(25, 600), sf::Vector2f(12.5, 300), sf::Color(43, 47, 47))); // LeftBorder
    m_borders.push_back(new Border(sf::Vector2f(800, 25), sf::Vector2f(400, 587.5), sf::Color(43, 47, 47))); // BottomBorder
    m_borders.push_back(new Border(sf::Vector2f(800, 25), sf::Vector2f(400, 12.5), sf::Color(43, 47, 47))); // TopBorder

    m_borders.push_back(new Border(sf::Vector2f(155, 370), sf::Vector2f(800, 390), sf::Color(23, 27, 27)));
    m_borders.push_back(new Border(sf::Vector2f(155, 30), sf::Vector2f(800, 43), sf::Color(23, 27, 27)));
    m_borders.push_back(new Border(sf::Vector2f(155, 40), sf::Vector2f(800, 160), sf::Color(23, 27, 27)));
}

void Game::CreateSnakes()
{
    for (size_t i = 0; i < m_numSnakes; i++)
    {
        sf::Vector2f randomPos = sf::Vector2f((rand() % 60) * 10 + 50, (rand() % 50) * 10 + 50);
        sf::Color randomColour = sf::Color(rand() % 255, rand() % 255, rand() % 255);

        if (i >= m_numPlayers)
        {
            m_snakes.push_back(new Snake(randomPos, randomColour, m_snakeSize, false)); // Snake is not a player
        }
        else
        {
            m_snakes.push_back(new Snake(randomPos, randomColour, m_snakeSize, true)); //Snake is a player
        }
    }
}

void Game::CreateCollectables()
{
    for (size_t i = 0; i < m_numCollectables; i++)
    {
        if(i < m_numFood)
        {
            m_collectables.push_back(new Food(m_collectablePositions));
        }
        else
        {
            m_collectables.push_back(new Battery(m_collectablePositions));
        }
        m_collectablePositions.push_back(m_collectables[i]->GetPos());
    }
}

void Game::CheckGameOver()
{
    if (m_gameTimer.getElapsedTime().asSeconds() > 91)
    {
        ProcessWinner(NULL);
    }

    int numSnakesAlive = m_snakes.size();
    Snake* winSnake = NULL;

    for (Snake* snake : m_snakes)
    {
        if (!snake->GetIsAlive())
        {
            numSnakesAlive--;
        }
    }

    if(numSnakesAlive <= 1)
    {
        for (Snake* snake : m_snakes)
        {
            if (snake->GetIsAlive())
            {
                winSnake = snake;
            }
        }
        ProcessWinner(winSnake);
    }
}

void Game::ProcessWinner(Snake* snake)
{
    if(snake != NULL)
    {
        m_winners.push_back(snake);
    }
    else
    {
        int bestScore = 0;

        for (Snake* snake : m_snakes) //Find best score
        {
            if(bestScore < snake->GetScore())
            {
                bestScore = snake->GetScore();
            }
        }
        for (Snake* snake : m_snakes) // Compare best score with the snakes
        {
            if (bestScore == snake->GetScore() && snake->GetIsAlive())
            {
                m_winners.push_back(snake);
            }
        }

    }

    m_winScreen->SetWinners(m_winners);
    m_gameOverSFX.play();
    gameState = GameState::GAMEOVER;
}

void Game::ResetGame()
{
    for (Snake* snake : m_snakes)
    {
        snake->Reset();
    }

    m_winners.clear();
    m_clock.restart();
    m_gameTimer.restart();
    m_scoreboard->ResetClock();
    gameState = GameState::PLAYING;
}
