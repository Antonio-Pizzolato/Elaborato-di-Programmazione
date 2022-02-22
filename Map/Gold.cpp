#include "Gold.h"

// Default constructor.
Gold::Gold()
{
    // Set gold value.
    int range = 30 - 1 + 1;
    int num = rand() % range + 1;
    goldValue = num;



    // Set the sprite.
    int textureID;
    if (goldValue < 9)
    {
        textureID = TextureManager::AddTexture("Resources/loot/gold/spr_pickup_gold_small.png");
    }
    else if (goldValue >= 25)
    {
        textureID = TextureManager::AddTexture("Resources/loot/gold/Gold_Purse1.png");
    }
    else
    {
        textureID = TextureManager::AddTexture("Resources/loot/gold/spr_pickup_gold_medium.png");
    }

    // Set the sprite.
    SetSprite(TextureManager::GetTexture(textureID), true, 4, 9);

    // Set the item type.
    m_type = ITEM::GOLD;
}

//  Returns the amount of gold this pickup has.
int Gold::GetGoldValue() const
{
    return goldValue;
}
