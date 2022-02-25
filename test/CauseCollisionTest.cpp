#include "gtest/gtest.h"
#include "../Entities/Warrior.h"

class WarriorSuite : public ::testing::Test {

protected:
    void SetUp() override {

    }
    Player* warrior;
    sf::RenderWindow window;
    Level level;
};

TEST_F(WarriorSuite, CauseCollisionTest){

}

