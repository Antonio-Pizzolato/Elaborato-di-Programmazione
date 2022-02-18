//
// Created by Antonio on 22/07/2021.
//

#ifndef ELABORATO_DI_PROGRAMMAZIONE_GAME_H
#define ELABORATO_DI_PROGRAMMAZIONE_GAME_H

#include "Entities/Warrior.h"
#include "Entities/Wizard.h"
#include "Entities/Archer.h"
#include "Input.h"
#include "Systems/MainMenu.h"
#include "GUI/PauseMenu.h"
#include "Systems/Shop.h"
#include "Entities/Humanoid.h"
#include "Entities/Slime.h"
#include "Map/Items.h"
#include "Map/Gold.h"
#include "Map/Potion.h"
#include "GUI/PlayerGUI.h"
#include "Achievements.h"

static int const MAX_ITEM_SPAWN_COUNT = 50;
static int const MAX_ENEMY_SPAWN_COUNT = 10;


class Game {

private:

    ConditionAchievement conditionAchievement;
    Achievements *achievements;

    sf::RenderWindow& m_window;

    sf::Vector2i mousePosWindow;

    bool m_isRunning;
    bool m_levelWasGenerated;
    bool end;

    sf::Font font;
    sf::Vector2f m_screenCenter;
    std::ostringstream m_stringStream;
    std::string m_string;
    sf::Text m_text;

    std::map<std::string, sf::Texture> textures;
    Player* m_player;
    Level m_level;
    Tile* m_playerPreviousTile{};

    sf::Clock m_timestepClock;
    sf::Clock keyTimer;
    float keyTimeMax;

    std::vector<std::unique_ptr<Items>> m_items;
    std::vector<std::unique_ptr<Enemy>> m_enemies;
    std::vector<std::unique_ptr<Projectile>> projectile;
    int m_projectileTextureID;

    GAME_STATE m_gameState;
    PLAYER_CLASS m_playerClass;
    std::unique_ptr<MainMenu> mainMenu;
    std::unique_ptr<CharacterSelection> characterSelection;
    std::unique_ptr<Shop> shop;
    PlayerGUI* playerGui;
    std::unique_ptr<PauseMenu> pauseMenu;


    static float DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2);

    void PopulateLevel();
    void UpdateItems(sf::Vector2f playerPosition);
    void UpdateEnemies(sf::Vector2f playerPosition, float timeDelta, Level &level);
    void UpdateProjectiles(float timeDelta);
    void SpawnItem(ITEM itemType, sf::Vector2f position = { -1.f, -1.f });
    void SpawnEnemy(ENEMY enemyType, sf::Vector2f position = {-1.f, -1.f});
    void GenerateLevel();
public:

    int m_goldTotal;

    //Constructors/Destructors
    Game(sf::RenderWindow* window);
    virtual ~Game();

    bool getKeyTime();

    void DrawString(const std::string &text, sf::Vector2f position, unsigned int size = 10);
    void Initialize();
    void InitializePlayer(PLAYER_CLASS playerClass);
    void Run();
    void Update(float timeDelta);
    void Draw(float timeDelta);
};

#endif //ELABORATO_DI_PROGRAMMAZIONE_GAME_H
