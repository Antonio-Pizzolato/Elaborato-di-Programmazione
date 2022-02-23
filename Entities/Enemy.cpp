#include "Enemy.h"

// Default constructor.
Enemy::Enemy(int level, ENEMY enemy_class) : enemyAttributeComponent(nullptr)
{

    if(enemy_class == ENEMY::SLIME)
    {
        frameCount = 4;
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("Resources/enemies/slime/slimesprite.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("Resources/enemies/slime/slimesprite.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("Resources/enemies/slime/slimesprite.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("Resources/enemies/slime/slimesprite1.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("Resources/enemies/slime/slimesprite.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("Resources/enemies/slime/slimesprite.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("Resources/enemies/slime/slimesprite.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("Resources/enemies/slime/slimesprite1.png");

        // Set initial sprite.
        SetSprite(TextureManager::GetTexture(textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)]), frameCount, 6);

        // Set a random color for the slime sprite.
        sf::Uint8 r, g, b, a;
        r = static_cast<sf::Uint8>(std::rand() % 256);
        g = static_cast<sf::Uint8>(std::rand() % 256);
        b = static_cast<sf::Uint8>(std::rand() % 256);
        a = static_cast<sf::Uint8>((std::rand() % 156) + 100);

        sf::Color color(r, g, b, a);
        sprite.setColor(color);

        createEnemyAttributeComponent(level, ENEMY::SLIME);
    }
    else if(enemy_class == ENEMY::HUMANOID)
    {
        // Generate a humanoid type.
        auto humanoidType = static_cast<HUMANOID>(std::rand() % static_cast<int>(HUMANOID::COUNT));
        std::string enemyName;

        // Set enemy specific variables.
        switch (humanoidType)
        {
            case HUMANOID::GOBLIN:
                enemyName = "goblin";
                break;
            case HUMANOID::SKELETON:
                enemyName = "skeleton";
                break;
            default:
                enemyName = "skeleton";
                break;
        }

        frameCount = 8;

        // Load textures.
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("Resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_up.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("Resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_down.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("Resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_right.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("Resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_left.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("Resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_up.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("Resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_down.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("Resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_right.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("Resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_left.png");

        // Set initial sprite.
        SetSprite(TextureManager::GetTexture(textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)]), frameCount, 12);

        createEnemyAttributeComponent(level, ENEMY::HUMANOID);
    }
    else if(enemy_class == ENEMY::RAT)
    {
        frameCount = 4;
        // Load textures.
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("Resources/enemies/Rat/rat_walkup.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("Resources/enemies/Rat/rat_walkdown.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("Resources/enemies/Rat/rat_walkright.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("Resources/enemies/Rat/rat_walkleft.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("Resources/enemies/Rat/rat_idle.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("Resources/enemies/Rat/rat_idle.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("Resources/enemies/Rat/rat_idle.png");
        textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("Resources/enemies/Rat/rat_idle.png");

        // Set initial sprite.
        SetSprite(TextureManager::GetTexture(textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)]), frameCount, 12);

        createEnemyAttributeComponent(level, ENEMY::RAT);

    }


    // Set speed.
    speed = rand() % 51 + 150;
}

Enemy::~Enemy() {
    delete enemyAttributeComponent;
}

void Enemy::createEnemyAttributeComponent(int level, ENEMY enemy) {
    enemyAttributeComponent = new EnemyAttributeComponent(level, enemy);
}

// Overrides the default Update function of Entity.
void Enemy::Update(float timeDelta, Level &level)
{
    sf::Vector2f previousPosition = position;

    // Move towards current target location.
    if (!targetPositions.empty())
    {
        sf::Vector2f targetLocation = targetPositions.front();
        velocity = sf::Vector2f(targetLocation.x - position.x, targetLocation.y - position.y);

        if (std::abs(velocity.x) < 10.f && std::abs(velocity.y) < 10.f)
        {
            targetPositions.erase(targetPositions.begin());
        }
        else
        {
            float length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

            // Calculate horizontal movement.
            if (CausesCollision(sf::Vector2f(velocity.x, 0.0f), level))
            {
                position.x = previousPosition.x;
            }
            else
            {
                velocity.x /= length;
                position.x += velocity.x * (speed * timeDelta);
            }

            // Calculate horizontal movement.
            if (CausesCollision(sf::Vector2f(0.0f, velocity.y), level))
            {
                position.y = previousPosition.y;
            }
            else
            {
                velocity.y /= length;
                position.y += velocity.y * (speed * timeDelta);
            }

            sprite.setPosition(position);
        }
    }
    else
    {
        velocity.x = 0.f;
        velocity.y = 0.f;
    }

    // Choose animation state.
    auto animState = ANIMATION_STATE::IDLE_UP;

    if ((velocity.x != 0) || (velocity.y != 0))
    {
        if (std::abs(velocity.x) > std::abs(velocity.y))
        {
            if (velocity.x <= 0)
            {
                animState = ANIMATION_STATE::WALK_LEFT;
                SetSprite(TextureManager::GetTexture(textureIDs[static_cast<int>(animState)]), frameCount, 6);
            }
            else
            {
                animState = ANIMATION_STATE::WALK_RIGHT;
                SetSprite(TextureManager::GetTexture(textureIDs[static_cast<int>(animState)]), frameCount, 6);
            }
        }
        else
        {
            if (velocity.y <= 0)
            {
                animState = ANIMATION_STATE::WALK_UP;
                SetSprite(TextureManager::GetTexture(textureIDs[static_cast<int>(animState)]), frameCount, 6);
            }
            else
            {
                animState = ANIMATION_STATE::WALK_DOWN;
                SetSprite(TextureManager::GetTexture(textureIDs[static_cast<int>(animState)]), frameCount, 6);
            }
        }
    }

}

// Draws the object to the given render window.
void Enemy::Draw(sf::RenderWindow &window, float _timeDelta)
{
    // check if the sprite is animated
    if (isAnimated)
    {
        // add the elapsed time since the last draw call to the aggregate
        timeDelta += _timeDelta;

        // check if the frame should be updated
        if (timeDelta >= (1.f / animationSpeed))
        {
            NextFrame();
            timeDelta = 0;
        }
    }

    window.draw(sprite);
}

// Applies the given amount of damage to the enemy.
void Enemy::Damage(int damage)
{
    int applied_damage = static_cast<int>(damage - (ENEMY_TAKEN_DAMAGE_REDUCTION_SCALE));
    enemyAttributeComponent->hp -= applied_damage > 0 ? applied_damage : 0;
}

// Checks if the enemy has taken enough damage that they are now dead.
bool Enemy::IsDead()
{
    return (enemyAttributeComponent->hp <= 0);
}

// Calculate an amount of damage to an enemy.
int Enemy::CalculateDamage()
{
    float damage_scale(1.f);
    damage_scale += ENEMY_DEXTERITY_DAMAGE_SCALE;

    float damage = (std::rand() % (ENEMY_MAX_DAMAGE + 1)) + (ENEMY_ATTACK_DAMAGE_SCALE * enemyAttributeComponent->damageMax);
    return static_cast<int>(damage * damage_scale);
}


// Updates the target position of the enemy.
void Enemy::UpdatePathfinding(Level &level, sf::Vector2f playerPosition)
{
    // Reset all nodes.
    level.ResetNodes();

    // Store the start and goal nodes.
    Tile* startNode = level.GetTile(position);
    Tile* goalNode = level.GetTile(playerPosition);

    // Check we have a valid path to find. If not we can just end the
    // function as there's no path to find.
    if (startNode == goalNode)
    {
        targetPositions.clear();
        return;
    }

    // Step 1: Calculate the Manhattan distance for each tile on the level.
    for (int i = 0; i < level.GetSize().x; i++)
    {
        for (int j = 0; j < level.GetSize().y; j++)
        {
            Tile* node = level.GetTile(i, j);
            int heightOffset = std::abs(node->rowIndex - goalNode->rowIndex);
            int widthOffset = std::abs(node->columnIndex - goalNode->columnIndex);
            node->H = heightOffset + widthOffset;
        }
    }

    std::vector<Tile*> openList;
    std::vector<Tile*> closedList;
    std::vector<Tile*> pathList;
    std::vector<Tile*>::iterator position;
    Tile* currentNode = nullptr;

    openList.push_back(startNode);
    while(!openList.empty())
    {
        // Step 2: Find the node in the open list with the lowest F value and mark it as current.
        int lowestF = INT_MAX;
        for (Tile* tile: openList)
        {
            if (tile->F < lowestF)
            {
                lowestF = tile->F;
                currentNode = tile;
            }
        }

        // Remove the current node from the open list and add it to the closed list.
        position = std::find(openList.begin(), openList.end(), currentNode);
        if (position != openList.end()) openList.erase(position);
        closedList.push_back(currentNode);

        // Step 3: Find all adjacent tiles
        std::vector<Tile*> adjacentTiles;
        Tile* node;

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                node = level.GetTile(currentNode->columnIndex + i, currentNode->rowIndex + j);
                if ((node != nullptr) && (level.IsFloor(*node)) && (node != currentNode))
                {
                    adjacentTiles.push_back(node);
                }
            }
        }

        // For all adjacent nodes.
        for (Tile* adjacentNode: adjacentTiles)
        {
            if (adjacentNode == goalNode)
            {
                // Parent the goal node to current.
                adjacentNode->parentNode = currentNode;

                // Store the current path.
                while (adjacentNode->parentNode != nullptr)
                {
                    pathList.push_back(adjacentNode);
                    adjacentNode = adjacentNode->parentNode;
                }

                // Empty the open list and break out of our for loop.
                openList.clear();
                break;
            }
            else
            {
                // If the node is not in the closed list.
                position = std::find(closedList.begin(), closedList.end(), adjacentNode);
                if (position == closedList.end())
                {
                    // If the node is not in the open list.
                    position = std::find(openList.begin(), openList.end(), adjacentNode);
                    if (position == openList.end())
                    {
                        // Add the node to the open list.
                        openList.push_back(adjacentNode);

                        // Set the parent of the node to the current node.
                        adjacentNode->parentNode = currentNode;

                        // Calculate G (total movement cost so far) cost.
                        adjacentNode->G = currentNode->G + ENEMY_PATHFINDING_STEP_COST;

                        // Calculate the F (total movement cost + heuristic) cost.
                        adjacentNode->F = adjacentNode->G + adjacentNode->H;
                    }
                    else
                    {
                        // Check if this path is quicker that the other.
                        int tempG = currentNode->G + ENEMY_PATHFINDING_STEP_COST;

                        // Check if tempG is faster than the other. I.e, whether it's
                        // faster to go A->C->B that A->C.
                        if (tempG < adjacentNode->G)
                        {
                            // Re-parent node to this one.
                            adjacentNode->parentNode = currentNode;
                        }
                    }
                }
            }
        }
    }
    // Clear the vector of target positions.
    targetPositions.clear();

    // Store the node locations as the enemies target locations.
    for (Tile* tile : pathList)
    {
        targetPositions.push_back(level.GetActualTileLocation(tile->columnIndex, tile->rowIndex));
    }

    // Reverse the target position as we read them from goal to origin, we need them the other way around.
    std::reverse(targetPositions.begin(), targetPositions.end());
}

