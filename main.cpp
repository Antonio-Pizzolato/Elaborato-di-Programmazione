//
// Created by Antonio on 22/07/2021.
//

#include"Game.h"

int main()
{
    // Create the main game object.
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Dungeon");
    Game game(&window);

    // Initialize and run the game object.
    game.Initialize();
    game.Run();    //gameLoop

    return 0;
}
