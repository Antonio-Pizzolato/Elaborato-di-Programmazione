#include "Game.h"

//Constructors/Destructors
Game::Game(sf::RenderWindow* window) :
        m_window(*window),
        gameState(GAME_STATE::MAIN_MENU),
        playerClass(PLAYER_CLASS::WARRIOR),
        screenCenter({ 0, 0 }),
        isRunning(true),
        end(false),
        levelWasGenerated(false),
        keyTimeMax(0.3),
        goldTotal(0),
        projectileTextureID(0){

    // Enable VSync.
    m_window.setVerticalSyncEnabled(true);
    keyTimer.restart();

    // Calculate and store the center of the screen.
    screenCenter = { static_cast<float>(m_window.getSize().x) / 2.f, static_cast<float>(m_window.getSize().y) / 2.f };

    mainMenu = std::make_unique<MainMenu>(m_window, &font);
    characterSelection = std::make_unique<CharacterSelection>(m_window, &font);
    pauseMenu = std::make_unique<PauseMenu>(m_window, font);
    shop = std::make_unique<Shop>(m_window);

    level = Level(*window);

    font.loadFromFile("Fonts/Minecraft.ttf");

    achievements = new Achievements(&conditionAchievement);
    InitializePlayer(playerClass);




}
Game::~Game() {

    delete player;
    enemies.clear();
}

bool Game::getKeyTime()
{
    if (keyTimer.getElapsedTime().asSeconds() >= keyTimeMax)
    {
        keyTimer.restart();
        return true;
    }

    return false;
}

void Game::InitializePlayer(PLAYER_CLASS _playerClass)
{
    switch (_playerClass)
    {
        case PLAYER_CLASS::WIZARD:
            textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/Wizard/Wizard.png");

            player = new Wizard(500, 500, textures["PLAYER_SHEET"], PLAYER_CLASS::WIZARD);

            playerGui = new PlayerGUI(player, m_window, font);

            break;
        case PLAYER_CLASS::ARCHER:
            textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/Archer/Archer.png");

            player = new Archer(500, 500, textures["PLAYER_SHEET"], PLAYER_CLASS::ARCHER);

            playerGui = new PlayerGUI(player, m_window, font);
            break;
        case PLAYER_CLASS::WARRIOR:
            textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/texture_sheet.png");

            player = new Warrior(500, 500, textures["PLAYER_SHEET"], PLAYER_CLASS::WARRIOR);

            playerGui = new PlayerGUI(player, m_window, font);
            break;


    }




}



void Game::Initialize()
{


    switch (player->GetClass()) {

        case PLAYER_CLASS::WIZARD:
            projectileTextureID = TextureManager::AddTexture("Resources/Images/Sprites/Weapon/Projectile/spr_magic_ball.png");
            break;
        case PLAYER_CLASS::ARCHER:
            projectileTextureID = TextureManager::AddTexture("Resources/Images/Sprites/Weapon/Projectile/Arrow.png");
            break;
        default:
            projectileTextureID = TextureManager::AddTexture("Resources/Images/Sprites/Weapon/Projectile/spr_magic_ball.png");
            break;
    }

    GenerateLevel();
}

// Calculates the distance between two given points.
float Game::DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2)
{
    return (std::abs(static_cast<float>(sqrt(
            ((position1.x - position2.x) * (position1.x - position2.x)) +
            ((position1.y - position2.y) * (position1.y - position2.y))
    ))));
}

void Game::PopulateLevel() {
    for(int i = 0; i < MAX_ENEMY_SPAWN_COUNT; i++){
        if(std::rand() % 2){
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
    if ((position.x >= 0.f) || (position.y >= 0.f))
    {
        spawnLocation = position;
    }
    else {
        spawnLocation = level.GetRandomSpawnLocation();
    }
    // Create the enemy.
    int roomNumber = level.GetRoomNumber()+1;
    int FloorNumber = level.GetFloorNumber();
    int _level = roomNumber*FloorNumber;
    std::unique_ptr<Enemy> enemy;
    switch (enemyType)
    {
        case ENEMY::SLIME:
            enemy = std::make_unique<Slime>(_level);
            break;
        case ENEMY::HUMANOID:
            enemy = std::make_unique<Humanoid>(_level);
            break;
        default:
            enemy = std::make_unique<Slime>(_level);
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
    if ((position.x >= 0.f) || (position.y >= 0.f))
    {
        spawnLocation = position;
    }
    else {
        spawnLocation = level.GetRandomSpawnLocation();
    }

    std::unique_ptr<Items> item;
    // Check which type of object is being spawned.
    switch (itemType)
    {
        case ITEM::POTION:
            item = std::make_unique<Potion>();
            break;
        case ITEM::GOLD:
            item = std::make_unique<Gold>();
            break;
        default:
            item = std::make_unique<Potion>();
            break;
    }

    // Set the item position.
    item->SetPosition(spawnLocation);

    // Add the item to the list of all items.
    items.push_back(std::move(item));
}


void Game::Run() {

    float currentTime = timeStepClock.restart().asSeconds();
    while (isRunning)
    {
        // Check if the game was closed.
        sf::Event event{};
        if (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
                return;
            }
            else if((Input::IsKeyPressed(Input::KEY::KEY_I)) && getKeyTime()){
                if(gameState == GAME_STATE::INVENTORY)
                    gameState = GAME_STATE::PLAYING;
                else
                    gameState = GAME_STATE::INVENTORY;

            }
            else if((Input::IsKeyPressed(Input::KEY::KEY_P)) && getKeyTime()){
                if(gameState == GAME_STATE::SHOP)
                    gameState = GAME_STATE::PLAYING;
                else
                    gameState = GAME_STATE::SHOP;
            }
            else if((Input::IsKeyPressed(Input::KEY::KEY_ESC)) && getKeyTime()){
                if(gameState == GAME_STATE::PAUSED)
                    gameState = GAME_STATE::PLAYING;
                else
                    gameState = GAME_STATE::PAUSED;
            }
        }
        float newTime = timeStepClock.getElapsedTime().asSeconds();
        float frameTime = std::max(0.f, newTime - currentTime);
        currentTime = newTime;

        if (!levelWasGenerated)
        {
            Update(frameTime);

            // Draw all items in the level.
            Draw(frameTime);
        }
        else
        {
            levelWasGenerated = false;
        }
    }

    // Shut the game down.
    m_window.close();
}

void Game::Update(float timeDelta)
{
    // Check what state the game is in.
    switch (gameState)
    {
        case GAME_STATE::MAIN_MENU: {
            mousePosWindow = sf::Mouse::getPosition(m_window);
            mainMenu->Update(mousePosWindow, &gameState, &isRunning);
            break;
        }

        case GAME_STATE::CHARACTER_SELECT:
            mousePosWindow = sf::Mouse::getPosition(m_window);
            characterSelection->Update(mousePosWindow, &gameState, &player);
            player->SetPosition(level.SpawnLocation());
            playerGui = new PlayerGUI(player, m_window, font);
            break;

        case GAME_STATE::PLAYING:
        {
            // First check if the player is at the exit. If so there's no need to update anything.
            Tile& playerTile = *level.GetTile(player->GetPosition());

            if(enemies.empty()){
                level.UnlockDoor();
            }

            if (playerTile.type == TILE::WALL_DOOR_UNLOCKED)
            {

                // Clear all current items.
                items.clear();

                // Clear all current enemies.
                enemies.clear();

                // Generate a new room.
                GenerateLevel();
            }
            else {
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

                            if (DistanceBetweenPoints(enemy.GetPosition(), player->getPosition()) < 80.f) {
                                // Damage the enemy.
                                enemy.Damage(player->getDamage());
                                if (enemy.IsDead()) {

                                    // Get the enemy position.
                                    sf::Vector2f position = enemy.GetPosition();

                                    // Spawn loot.
                                    for (int i = 0; i < 3; i++) {
                                        position.x += std::rand() % 31 - 15;
                                        position.y += std::rand() % 31 - 15;

                                        int itemType = rand() % 2;
                                        SpawnItem(static_cast<ITEM>(itemType), position);
                                    }

                                    player->gainExp(20, player->GetClass());
                                    player->killNumber += 1;


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
                    }
                    else if (player->GetClass() == PLAYER_CLASS::ARCHER ||
                             player->GetClass() == PLAYER_CLASS::WIZARD)//mana cost
                    {
                        sf::Vector2f target(static_cast<float>(sf::Mouse::getPosition().x),
                                            static_cast<float>(sf::Mouse::getPosition().y));
                        std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(
                                TextureManager::GetTexture(projectileTextureID), player->getPosition(), player->getPosition(),
                                target);
                        projectile.push_back(std::move(proj));


                        // Reduce player mana.
                        //player->SetMana(player.GetMana() - 2);
                    }
                }

                /*if(player->isDead()){
                    gameState = GAME_STATE::MAIN_MENU;   //death
                }*/

                // Update all items.
                UpdateItems(player->GetPosition());

                // Update all projectiles.
                UpdateProjectiles(timeDelta);

                // Update all enemies.
                UpdateEnemies(player->GetPosition(), timeDelta, level);


                //Update achievement
                achievements->update(timeDelta);

                conditionAchievement.setConditions(player->killNumber, goldTotal);

                Tile *playerCurrentTile = level.GetTile(player->GetPosition());
                if (playerPreviousTile != playerCurrentTile) {
                    // Store the new tile.
                    playerPreviousTile = playerCurrentTile;

                    // Update path finding for all enemies if within range of the player.
                    for (const auto &enemy: enemies) {
                        if (DistanceBetweenPoints(enemy->GetPosition(), player->GetPosition()) < 200.f) {
                            enemy->UpdatePathfinding(level, player->GetPosition());
                        }
                    }

                }
            }


        }
            break;

        case GAME_STATE::SHOP:{
            mousePosWindow = sf::Mouse::getPosition(m_window);
            shop->Update(mousePosWindow);
        }
            break;

        case GAME_STATE::PAUSED:
            mousePosWindow = sf::Mouse::getPosition(m_window);
            pauseMenu->update(m_window, mousePosWindow, &gameState);
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
    m_string.clear();

    stringStream << text;
    m_string = stringStream.str();

    m_text.setString(m_string);
    m_text.setFont(font);
    m_text.setCharacterSize(size);
    m_text.setPosition(position.x - (m_text.getLocalBounds().width / 2.f), position.y - (m_text.getLocalBounds().height / 2.f));

    m_window.draw(m_text);
}

// Draw the current game scene.
void Game::Draw(float timeDelta)
{
    // Clear the screen.
    m_window.clear(sf::Color(3, 3, 3, 225));		// Gray

    // Check what state the game is in.
    switch (gameState)
    {
        case GAME_STATE::MAIN_MENU:
            mainMenu->Draw(m_window);
            break;

        case GAME_STATE::CHARACTER_SELECT:
            characterSelection->Draw(m_window);
            break;

        case GAME_STATE::PLAYING:
        {
            // Set the main game view.
            //m_window.setView(m_views[static_cast<int>(VIEW::MAIN)]);

            // Draw the level.
            level.Draw(m_window, timeDelta);

            // Draw all objects.
            for (const auto& item : items)
            {
                item->Draw(m_window, timeDelta);
            }

            // Draw all enemies.
            for (const auto& enemy : enemies)
            {
                enemy->Draw(m_window, timeDelta);
            }

            // Draw all projectiles
            for (const auto &proj : projectile) {
                m_window.draw(proj->GetSprite());
            }

            // Hide the mouse cursor.
            m_window.setMouseCursorVisible(false);

            // Draw player aim.
            m_window.draw(player->GetAimSprite());

            // Draw the player.
            playerGui->render(m_window);
            player->Draw(m_window, timeDelta);

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

            DrawString(goldString, sf::Vector2f(screenCenter.x + 220.f, 40.f), 40);

            std::string hp;
            hp = std::to_string(player->getAttributeComponent()->damageMax);
            DrawString(hp, sf::Vector2f(screenCenter.x + 220.f, 80.f), 40);

            achievements->render(m_window);

        }
            break;


        case GAME_STATE::PAUSED:
            pauseMenu->render(m_window);
            // Hide the mouse cursor.
            m_window.setMouseCursorVisible(true);
            break;

        case GAME_STATE::SHOP:{
            shop->Draw(m_window);
            // Hide the mouse cursor.
            m_window.setMouseCursorVisible(true);
        }
            break;

        case GAME_STATE::GAME_OVER:
            break;

    }
    // Present the back-buffer to the screen.
    m_window.display();
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
        Enemy& enemy = **enemyIterator;

        // Get the tile that the enemy is on.
        Tile* enemyTile = level.GetTile(enemy.GetPosition());

        // Check for collisions with projectiles.
        auto projectilesIterator = projectile.begin();
        while (projectilesIterator != projectile.end())
        {
            // Get the projectile object from the iterator.
            Projectile& projectiles = **projectilesIterator;

            // If the enemy and projectile occupy the same tile they have collided.
            if (enemyTile == level.GetTile(projectiles.GetPosition()))
            {
                // Delete the projectile.
                projectilesIterator = projectile.erase(projectilesIterator);

                // Damage the enemy.
                enemy.Damage(player->getDamage());

                // If the enemy is dead remove it.
                if (enemy.IsDead())
                {
                    // Get the enemy position.
                    sf::Vector2f position = enemy.GetPosition();

                    // Spawn loot.
                    for (int i = 0; i < 5; i++)
                    {
                        position.x += std::rand() % 31 - 15;
                        position.y += std::rand() % 31 - 15;

                        int itemType = std::rand() % 2;
                        SpawnItem(static_cast<ITEM>(itemType), position);
                    }

                    player->gainExp(20, player->GetClass());

                    // Delete enemy.
                    enemyIterator = enemies.erase(enemyIterator);
                    enemyWasDeleted = true;

                    // If we have an active goal decrement killGoal.
                    /*if (m_activeGoal)
                    {
                        --m_killGoal;
                    }*/

                    // Since the enemy is dead we no longer need to check projectiles.
                    projectilesIterator = projectile.end();
                }
            }
            else
            {
                // Move to the next projectile.
                ++projectilesIterator;
            }
        }

        // If the enemy was not deleted, update it and increment the iterator.
        if (!enemyWasDeleted)
        {
            enemy.Update(timeDelta, level);
            ++enemyIterator;
        }

        // Check for collision with player.
        if (enemyTile == playerTile)
        {
            if (player->CanTakeDamage())
            {
                player->Damage(enemy.CalculateDamage());
            }
        }
    }
}

void Game::UpdateProjectiles(float timeDelta) {
    auto projectileIterator = projectile.begin();
    while (projectileIterator != projectile.end())
    {
        // Get the projectile object from the iterator.
        Projectile& projectiles = **projectileIterator;

        // Get the tile that the projectile is on.
        TILE projectileTileType = level.GetTile(projectiles.GetPosition())->type;

        // If the tile the projectile is on is not floor, delete it.
        if ((projectileTileType != TILE::FLOOR) && (projectileTileType != TILE::FLOOR_ALT))
        {
            projectileIterator = projectile.erase(projectileIterator);
        }
        else
        {
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
        if (DistanceBetweenPoints(item.GetPosition(), playerPosition) < 40.f) {
            switch (item.GetType()) {
                case ITEM::GOLD: {
                    // Get the amount of gold.
                    int goldValue = dynamic_cast<Gold &>(item).GetGoldValue();

                    // Add to the gold total.
                    goldTotal += goldValue;

                    // Check if we have an active level goal.
                    /*if (m_activeGoal)
                    {
                        m_goldGoal -= goldValue;
                    }*/
                }
                    break;

                case ITEM::POTION:
                {
                    // Cast to heart and get health.
                    auto potion = dynamic_cast<Potion &>(item).GetHpValue();
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















