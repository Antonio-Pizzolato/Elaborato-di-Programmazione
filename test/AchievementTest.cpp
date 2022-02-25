#include "gtest/gtest.h"
#include "../Achievements.h"

TEST(AchievementTest, UnlockAchievement){
    float dt = 8;
    ConditionAchievement conditionAchievement;
    auto achievements = new Achievements(&conditionAchievement);
    conditionAchievement.setConditions(3, 15);
    ASSERT_TRUE(achievements->getKill());
    ASSERT_TRUE(achievements->getGainGold());
    achievements->updateLifetime(dt);
    ASSERT_FALSE(achievements->getExpired());
}

