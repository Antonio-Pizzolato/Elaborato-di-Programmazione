#ifndef ELABORATO_DI_PROGRAMMAZIONE_GAME_H
#define ELABORATO_DI_PROGRAMMAZIONE_GAME_H

#include "Entities/Warrior.h"
#include "Entities/Wizard.h"
#include "Entities/Archer.h"
#include "Input.h"
#include "Systems/MainMenu.h"
#include "GUI/PauseMenu.h"
#include "Systems/Shop.h"
#include "Entities/Enemy.h"
#include "Map/Items.h"
#include "GUI/PlayerGUI.h"
#include "Achievements.h"

static int const MAX_ENEMY_SPAWN_COUNT = 10;

class Game {

private:

    ConditionAchievement conditionAchievement;
    Achievements *achievements;

    sf::RenderWindow& windows;

    sf::Vector2i mousePosWindow;

    bool isRunning;
    bool levelWasGenerated;
    bool end;

    sf::Font font;
    sf::Vector2f screenCenter;
    std::ostringstream stringStream;
    std::string phrase;
    sf::Text word;

    std::map<std::string, sf::Texture> textures;
    Player* player;
    Level level;
    Tile* playerPreviousTile{};

    sf::Clock timeStepClock;
    sf::Clock keyTimer;
    float keyTimeMax;

    std::vector<std::unique_ptr<Items>> items;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Projectile>> projectile;
    int projectileTextureID;

    GAME_STATE gameState;
    PLAYER_CLASS playerClass;
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

    int goldTotal;

    //Constructors/Destructors
    explicit Game(sf::RenderWindow* window);
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
