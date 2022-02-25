#include "gtest/gtest.h"
#include "../Achievements.h"


TEST(AchievementTest, UnlockAchievement){

    ConditionAchievement conditionAchievement;
    auto achievements = new Achievements(&conditionAchievement);
    achievements->update(3, 15);
    ASSERT_TRUE(achievements->getKill());

}

