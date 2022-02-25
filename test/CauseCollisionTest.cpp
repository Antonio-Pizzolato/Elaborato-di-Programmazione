#include "gtest/gtest.h"
#include "../Entities/Warrior.h"

class WarriorSuite : public ::testing::Test {

protected:
    void SetUp() override {
        sf::Texture texture;
        texture.loadFromFile("Resources/Images/Sprites/Player/texture_sheet.png");
        level = Level(window);
        warrior = new Warrior(texture, PLAYER_CLASS::WARRIOR);
    }
    Player* warrior;
    sf::RenderWindow window;
    Level level;
};

TEST_F(WarriorSuite, CauseCollisionTest) {
    level.GenerateLevel();
    warrior->SetPosition(level.SpawnLocation());
    warrior->SetUp();
    for (int x = 0; x < 5; x++) {
        warrior->Update(10, level);
        EXPECT_EQ(warrior->GetPreviousPosition(), warrior->GetPosition());
    }
}

