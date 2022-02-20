//
// Created by Antonio on 18/02/2022.
//

#include "Gold.h"

// Default constructor.
Gold::Gold()
{
    // Set gold value.
    goldValue = 1+ std::rand() % 2;
    /*std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, std::nextafter(9, 10));
    for (int i = 0; i < 3; ++i) {
        goldValue = dist(mt);
    }*/


    // Set the sprite.
    int textureID;
    if (goldValue < 9)
    {
        textureID = TextureManager::AddTexture("Resources/loot/gold/spr_pickup_gold_small.png");
    }
    else if (goldValue >= 16)
    {
        textureID = TextureManager::AddTexture("Resources/loot/gold/spr_pickup_gold_large.png");
    }
    else
    {
        textureID = TextureManager::AddTexture("Resources/loot/gold/spr_pickup_gold_medium.png");
    }

    // Set the sprite.
    SetSprite(TextureManager::GetTexture(textureID), false, 8, 12);

    // Set the item type.
    m_type = ITEM::GOLD;
}

//  Returns the amount of gold this pickup has.
int Gold::GetGoldValue() const
{
    return goldValue;
}
