#include "Game.h"

//Constructors/Destructors
Game::Game(sf::RenderWindow *window) :
        windows(*window),
        gameState(GAME_STATE::MAIN_MENU),
        playerClass(PLAYER_CLASS::WARRIOR),
        screenCenter({0, 0}),
        isRunning(true),
        end(false),
        levelWasGenerated(false),
        keyTimeMax(0.3),
        goldTotal(0),
        projectileTextureID(0) {

    // Enable VSync.
    windows.setVerticalSyncEnabled(true);
    keyTimer.restart();

    // Calculate and store the center of the screen.
    screenCenter = {static_cast<float>(windows.getSize().x) / 2.f, static_cast<float>(windows.getSize().y) / 2.f};

    mainMenu = std::make_unique<MainMenu>(windows, &font);
    characterSelection = std::make_unique<CharacterSelection>(windows, &font);
    pauseMenu = std::make_unique<PauseMenu>(windows, font);

    level = Level(*window);

    font.loadFromFile("Fonts/alagard.ttf");

    achievements = new Achievements(&conditionAchievement);
    InitializePlayer(playerClass);

}

Game::~Game() {

    delete player;
    enemies.clear();
}

bool Game::getKeyTime() {
    if (keyTimer.getElapsedTime().asSeconds() >= keyTimeMax) {
        keyTimer.restart();
        return true;
    }

    return false;
}

void Game::InitializePlayer(PLAYER_CLASS _playerClass) {
    switch (_playerClass) {
        case PLAYER_CLASS::WIZARD:
            textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/Wizard/Wizard.png");

            player = new Wizard(textures["PLAYER_SHEET"], PLAYER_CLASS::WIZARD);

            playerGui = new PlayerGUI(player, windows, font);

            break;
        case PLAYER_CLASS::ARCHER:
            textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/Archer/Archer.png");

            player = new Archer(textures["PLAYER_SHEET"], PLAYER_CLASS::ARCHER);

            playerGui = new PlayerGUI(player, windows, font);
            break;
        case PLAYER_CLASS::WARRIOR:
            textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/texture_sheet.png");

            player = new Warrior(textures["PLAYER_SHEET"], PLAYER_CLASS::WARRIOR);

            playerGui = new PlayerGUI(player, windows, font);
            break;


    }


}

void Game::Initialize() {


    switch (player->GetClass()) {

        case PLAYER_CLASS::WIZARD:
            projectileTextureID = TextureManager::AddTexture(
                    "Resources/Images/Sprites/Weapon/Projectile/spr_magic_ball.png");
            break;
        case PLAYER_CLASS::ARCHER:
            projectileTextureID = TextureManager::AddTexture("Resources/Images/Sprites/Weapon/Projectile/Arrow123.png");
            break;
        default:
            projectileTextureID = TextureManager::AddTexture(
                    "Resources/Images/Sprites/Weapon/Projectile/spr_magic_ball.png");
            break;
    }

    GenerateLevel();
}

// Calculates the distance between two given points.
float Game::DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2) {
    return (std::abs(static_cast<float>(sqrt(
            ((position1.x - position2.x) * (position1.x - position2.x)) +
            ((position1.y - position2.y) * (position1.y - position2.y))
    ))));
}

void Game::PopulateLevel() {
    for (int i = 0; i < MAX_ENEMY_SPAWN_COUNT; i++) {
        if (std::rand() % 2) {
            //Choose a random enemy type
            int enemyType = std::rand() % static_cast<int>(ENEMY::COUNT);

            SpawnEnemy(static_cast<ENEMY>(enemyType));
        }
    }
}

void Game::SpawnEnemy(ENEMY enemyType, sf::Vector2f position) {
    // Spawn location of enemy.
    sf::Vector2f spawnLocation;

    // Choose a random, unused spawn location.
    if ((position.x >= 0.f) || (position.y >= 0.f)) {
        spawnLocation = position;
    } else {
        spawnLocation = level.GetRandomSpawnLocation();
    }
    // Create the enemy.
    int roomNumber = level.GetRoomNumber() + 1;
    int FloorNumber = level.GetFloorNumber();
    int _level = roomNumber * FloorNumber;
    std::unique_ptr<Enemy> enemy;
    switch (enemyType) {
        case ENEMY::SLIME:
            enemy = std::make_unique<Enemy>(_level, ENEMY::SLIME);
            break;
        case ENEMY::HUMANOID:
            enemy = std::make_unique<Enemy>(_level, ENEMY::HUMANOID);
            break;
        case ENEMY::RAT:
            enemy = std::make_unique<Enemy>(_level, ENEMY::RAT);
            break;
        default:
            enemy = std::make_unique<Enemy>(_level, ENEMY::SLIME);
            break;
    }
    // Set spawn position.
    enemy->SetPosition(spawnLocation);

    // Add to list of all enemies.
    enemies.push_back(std::move(enemy));
}

void Game::SpawnItem(ITEM itemType, sf::Vector2f position) {
    // Choose a random, unused spawn location.
    sf::Vector2f spawnLocation;
    if ((position.x >= 0.f) || (position.y >= 0.f)) {
        spawnLocation = position;
    } else {
        spawnLocation = level.GetRandomSpawnLocation();
    }

    std::unique_ptr<Items> item;
    // Check which type of object is being spawned.
    item = std::make_unique<Items>(itemType);

    // Set the item position.
    item->SetPosition(spawnLocation);

    // Add the item to the list of all items.
    items.push_back(std::move(item));
}


void Game::Run() {

    float currentTime = timeStepClock.restart().asSeconds();
    while (isRunning) {
        // Check if the game was closed.
        sf::Event event{};
        if (windows.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                windows.close();
                return;
            }
            else if ((Input::IsKeyPressed(Input::KEY::KEY_ESC)) && getKeyTime()) {
                if (gameState == GAME_STATE::PAUSED)
                    gameState = GAME_STATE::PLAYING;
                else
                    gameState = GAME_STATE::PAUSED;
            }
        }
        float newTime = timeStepClock.getElapsedTime().asSeconds();
        float frameTime = std::max(0.f, newTime - currentTime);
        currentTime = newTime;

        if (!levelWasGenerated) {
            Update(frameTime);

            // Draw all items in the level.
            Draw(frameTime);
        } else {
            levelWasGenerated = false;
        }
    }

    // Shut the game down.
    windows.close();
}

void Game::Update(float timeDelta) {
    // Check what state the game is in.
    switch (gameState) {
        case GAME_STATE::MAIN_MENU: {
            mousePosWindow = sf::Mouse::getPosition(windows);
            mainMenu->Update(mousePosWindow, &gameState, &isRunning);
            break;
        }

        case GAME_STATE::CHARACTER_SELECT:
            mousePosWindow = sf::Mouse::getPosition(windows);
            characterSelection->Update(mousePosWindow, &gameState, &player);
            player->SetPosition(level.SpawnLocation());
            switch (player->GetClass()) {

                case PLAYER_CLASS::WIZARD:
                    projectileTextureID = TextureManager::AddTexture(
                            "Resources/Images/Sprites/Weapon/Projectile/spr_magic_ball.png");
                    break;
                case PLAYER_CLASS::ARCHER:
                    projectileTextureID = TextureManager::AddTexture(
                            "Resources/Images/Sprites/Weapon/Projectile/Arrow123.png");
                    break;
                default:
                    projectileTextureID = TextureManager::AddTexture(
                            "Resources/Images/Sprites/Weapon/Projectile/spr_magic_ball.png");
                    break;
            }

            playerGui = new PlayerGUI(player, windows, font);
            break;

        case GAME_STATE::PLAYING: {
            // First check if the player is at the exit. If so there's no need to update anything.
            Tile &playerTile = *level.GetTile(player->GetPosition());

            if (enemies.empty()) {
                level.UnlockDoor();
            }

            if (playerTile.type == TILE::WALL_DOOR_UNLOCKED) {

                // Clear all current items.
                items.clear();

                // Clear all current enemies.
                enemies.clear();

                // Generate a new room.
                GenerateLevel();
            } else {
                // Update the player.
                playerGui->update();

                player->Update(timeDelta, level);

                if (player->IsAttacking()) {
                    if (player->GetClass() == PLAYER_CLASS::WARRIOR) {
                        auto enemyIterator = enemies.begin();
                        while (enemyIterator != enemies.end()) {
                            // Create a bool, so we can check if an enemy was deleted.
                            bool enemyWasDeleted = false;

                            // Get the enemy object from the iterator.
                            Enemy &enemy = **enemyIterator;

                            if (DistanceBetweenPoints(enemy.GetPosition(), player->GetPosition()) < ATTACK_DISTANCE) {
                                // Damage the enemy.
                                enemy.Damage(player->getDamage());
                                if (enemy.IsDead()) {

                                    // Get the enemy position.
                                    sf::Vector2f position = enemy.GetPosition();

                                    // Spawn loot.
                                    for (int i = 0; i < 2; i++) {
                                        position.x += std::rand() % 31 - 15;
                                        position.y += std::rand() % 31 - 15;

                                        int potion = std::rand() % 2;
                                        SpawnItem(static_cast<ITEM>(potion), position);

                                    }
                                    for (int i = 0; i < 3; i++) {
                                        position.x += std::rand() % 31 - 25;
                                        position.y += std::rand() % 31 - 25;

                                        SpawnItem(static_cast<ITEM>(0), position);

                                    }

                                    player->gainExp(enemy.enemyAttributeComponent->exp, player->GetClass());
                                    player->killNumber += 1;
                                    conditionAchievement.setConditions(player->killNumber, goldTotal);

                                    // Delete enemy.
                                    enemyIterator = enemies.erase(enemyIterator);
                                    enemyWasDeleted = true;

                                }
                            }
                            // If the enemy was not deleted, update it and increment the iterator.
                            if (!enemyWasDeleted) {
                                enemy.Update(timeDelta, level);
                                ++enemyIterator;
                            }

                        }
                    } else if (player->GetClass() == PLAYER_CLASS::ARCHER ||
                               player->GetClass() == PLAYER_CLASS::WIZARD)//mana cost
                    {
                        sf::Vector2f target(static_cast<float>(sf::Mouse::getPosition().x),
                                            static_cast<float>(sf::Mouse::getPosition().y));
                        std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(
                                TextureManager::GetTexture(projectileTextureID), player->GetPosition(),
                                player->GetPosition(),
                                target);
                        projectile.push_back(std::move(proj));

                    }
                }

                if (player->isDead()) {
                    gameState = GAME_STATE::PAUSED;   //death
                }

                // Update all items.
                UpdateItems(player->GetPosition());

                // Update all projectiles.
                UpdateProjectiles(timeDelta);

                // Update all enemies.
                UpdateEnemies(player->GetPosition(), timeDelta, level);


                //Update achievement
                achievements->updateLifetime(timeDelta);


                Tile *playerCurrentTile = level.GetTile(player->GetPosition());
                if (playerPreviousTile != playerCurrentTile) {
                    // Store the new tile.
                    playerPreviousTile = playerCurrentTile;

                    // Update path finding for all enemies if within range of the player.
                    for (const auto &enemy: enemies) {
                        if (DistanceBetweenPoints(enemy->GetPosition(), player->GetPosition()) < ENEMY_AGGRO) {
                            enemy->UpdatePathfinding(level, player->GetPosition());
                        }
                    }

                }
            }


        }
            break;

        case GAME_STATE::PAUSED:
            mousePosWindow = sf::Mouse::getPosition(windows);
            pauseMenu->update(windows, mousePosWindow, &gameState);
            break;

        case GAME_STATE::GAME_OVER:
            projectile.clear();
            projectileTextureID = 0;
            enemies.clear();
            items.clear();
            break;
    }
}

void Game::DrawString(const string &text, sf::Vector2f position, unsigned int size) {
    // Clear the old data.
    stringStream.str(std::string());
    phrase.clear();

    stringStream << text;
    phrase = stringStream.str();

    word.setString(phrase);
    word.setFont(font);
    word.setCharacterSize(size);
    word.setPosition(position.x - (word.getLocalBounds().width / 2.f),
                     position.y - (word.getLocalBounds().height / 2.f));

    windows.draw(word);
}

// Draw the current game scene.
void Game::Draw(float timeDelta) {
    // Clear the screen.
    windows.clear(sf::Color(3, 3, 3, 225));        // Gray

    // Check what state the game is in.
    switch (gameState) {
        case GAME_STATE::MAIN_MENU:
            mainMenu->Draw(windows);
            break;

        case GAME_STATE::CHARACTER_SELECT:
            characterSelection->Draw(windows);
            break;

        case GAME_STATE::PLAYING: {
            // Set the main game view.

            // Draw the level.
            level.Draw(windows, timeDelta);

            // Draw all objects.
            for (const auto &item: items) {
                item->Draw(windows, timeDelta);
            }

            // Draw all enemies.
            for (const auto &enemy: enemies) {
                enemy->Draw(windows, timeDelta);
            }

            // Draw all projectiles
            for (const auto &proj: projectile) {
                windows.draw(proj->GetSprite());
            }

            // Hide the mouse cursor.
            windows.setMouseCursorVisible(false);

            // Draw player aim.
            windows.draw(player->GetAimSprite());

            // Draw the player.
            playerGui->render(windows);
            player->Draw(windows, timeDelta);

            // Draw gold total.
            std::string goldString;

            if (goldTotal > 99999) {
                goldString = std::to_string(goldTotal);
            } else if (goldTotal > 9999) {
                goldString = "0" + std::to_string(goldTotal);
            } else if (goldTotal > 999) {
                goldString = "00" + std::to_string(goldTotal);
            } else if (goldTotal > 99) {
                goldString = "000" + std::to_string(goldTotal);
            } else if (goldTotal > 9) {
                goldString = "0000" + std::to_string(goldTotal);
            } else {
                goldString = "00000" + std::to_string(goldTotal);
            }

            //draw gold in the top right of the screen
            DrawString(goldString, sf::Vector2f(screenCenter.x + 875.f, 40.f), 40);

            //draw player attributes in the top right of the screen
            std::string vitality;
            vitality = "vitality = " + std::to_string(player->getAttributeComponent()->vitality);
            DrawString(vitality, sf::Vector2f(screenCenter.x + 835.f, 80.f), 40);

            std::string strength;
            strength = "strength = " + std::to_string(player->getAttributeComponent()->strength);
            DrawString(strength, sf::Vector2f(screenCenter.x + 820.f, 120.f), 40);

            std::string dex;
            dex = "dexterity = " + std::to_string(player->getAttributeComponent()->dexterity);
            DrawString(dex, sf::Vector2f(screenCenter.x + 815.f, 160.f), 40);

            std::string agility;
            agility = "agility = " + std::to_string(player->getAttributeComponent()->agility);
            DrawString(agility, sf::Vector2f(screenCenter.x + 843.f, 200.f), 40);

            std::string intel;
            intel = "intelligence = " + std::to_string(player->getAttributeComponent()->intelligence);
            DrawString(intel, sf::Vector2f(screenCenter.x + 793.f, 240.f), 40);

            achievements->render(windows);

        }
            break;


        case GAME_STATE::PAUSED:
            pauseMenu->render(windows);
            // Hide the mouse cursor.
            windows.setMouseCursorVisible(true);
            break;

        case GAME_STATE::GAME_OVER:
            break;

    }
    // Present the back-buffer to the screen.
    windows.display();
}

void Game::GenerateLevel() {
    // Generate a new level.
    level.GenerateLevel();

    // Populate the level with items.
    PopulateLevel();

    // Moves the player to the start.
    player->SetPosition(level.SpawnLocation());
    /*if(enemies.empty()){
        level.UnlockDoor();
    }*/

}

void Game::UpdateEnemies(sf::Vector2f playerPosition, float timeDelta, Level &level) {
    // Store player tile.
    Tile *playerTile = level.GetTile(player->GetPosition());

    auto enemyIterator = enemies.begin();
    while (enemyIterator != enemies.end()) {
        // Create a bool so we can check if an enemy was deleted.
        bool enemyWasDeleted = false;

        // Get the enemy object from the iterator.
        Enemy &enemy = **enemyIterator;

        // Get the tile that the enemy is on.
        Tile *enemyTile = level.GetTile(enemy.GetPosition());

        // Check for collisions with projectiles.
        auto projectilesIterator = projectile.begin();
        while (projectilesIterator != projectile.end()) {
            // Get the projectile object from the iterator.
            Projectile &projectiles = **projectilesIterator;

            // If the enemy and projectile occupy the same tile they have collided.
            if (enemyTile == level.GetTile(projectiles.GetPosition())) {
                // Delete the projectile.
                projectilesIterator = projectile.erase(projectilesIterator);

                // Damage the enemy.
                enemy.Damage(player->getDamage());

                // If the enemy is dead remove it.
                if (enemy.IsDead()) {
                    // Get the enemy position.
                    sf::Vector2f position = enemy.GetPosition();

                    // Spawn loot.
                    for (int i = 0; i < 2; i++) {
                        position.x += std::rand() % 31 - 15;
                        position.y += std::rand() % 31 - 15;

                        int potion = std::rand() % 2;
                        SpawnItem(static_cast<ITEM>(potion), position);

                    }
                    for (int i = 0; i < 3; i++) {
                        position.x += std::rand() % 31 - 25;
                        position.y += std::rand() % 31 - 25;

                        SpawnItem(static_cast<ITEM>(0), position);

                    }

                    player->gainExp(enemy.enemyAttributeComponent->exp, player->GetClass());
                    player->killNumber += 1;

                    // Delete enemy.
                    enemyIterator = enemies.erase(enemyIterator);
                    enemyWasDeleted = true;


                    // Since the enemy is dead we no longer need to check projectiles.
                    projectilesIterator = projectile.end();
                }
            } else {
                // Move to the next projectile.
                ++projectilesIterator;
            }
        }

        // If the enemy was not deleted, update it and increment the iterator.
        if (!enemyWasDeleted) {
            enemy.Update(timeDelta, level);
            ++enemyIterator;
        }

        // Check for collision with player.
        if (enemyTile == playerTile) {
            if (player->CanTakeDamage()) {
                player->Damage(enemy.CalculateDamage());
            }
        }
    }
}

void Game::UpdateProjectiles(float timeDelta) {
    auto projectileIterator = projectile.begin();
    while (projectileIterator != projectile.end()) {
        // Get the projectile object from the iterator.
        Projectile &projectiles = **projectileIterator;

        // Get the tile that the projectile is on.
        TILE projectileTileType = level.GetTile(projectiles.GetPosition())->type;

        // If the tile the projectile is on is not floor, delete it.
        if ((projectileTileType != TILE::FLOOR) && (projectileTileType != TILE::FLOOR_ALT)) {
            projectileIterator = projectile.erase(projectileIterator);
        } else {
            // Update the projectile and move to the next one.
            projectiles.Update(timeDelta);
            ++projectileIterator;
        }
    }
}

void Game::UpdateItems(sf::Vector2f playerPosition) {
    // Update all items.
    auto itemIterator = items.begin();
    while (itemIterator != items.end()) {

        // Get the item from the iterator.
        Items &item = **itemIterator;

        // Check if the player is within pickup range of the item.
        if (DistanceBetweenPoints(item.GetPosition(), playerPosition) < PICKUP_DISTANCE) {
            switch (item.GetType()) {
                case ITEM::GOLD: {
                    // Get the amount of gold.
                    int goldValue = dynamic_cast<Items &>(item).GetValue();

                    // Add to the gold total.
                    goldTotal += goldValue;

                    conditionAchievement.setConditions(player->killNumber, goldTotal);
                }
                    break;

                case ITEM::POTION: {
                    // Cast to heart and get health.
                    auto potion = dynamic_cast<Items &>(item).GetValue();
                    player->gainHp(potion);
                }
                    break;

            }

            // Finally, delete the object.
            itemIterator = items.erase(itemIterator);

        } else {
            // Increment iterator.
            ++itemIterator;
        }
    }
}















