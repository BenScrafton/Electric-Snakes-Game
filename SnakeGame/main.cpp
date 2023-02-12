#include <iostream>
#include "Game.h";

int main()
{
    srand(time(NULL));
    Game game;
    game.Run();

    std::cout << "SnakeGame: Finished" << std::endl;
    return 0;
}
