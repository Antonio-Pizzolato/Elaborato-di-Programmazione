#include "Items.h"

// Default constructor.
Items::Items(ITEM itemType) {
    int textureID;
    if (itemType == ITEM::GOLD) {
        // Set gold value.
        int range = 30 - 1 + 1;
        int num = rand() % range + 1;
        goldValue = num;
        // Set the sprite.
        if (goldValue < 9) {
            textureID = TextureManager::AddTexture("Resources/loot/gold/spr_pickup_gold_small.png");
        }
        else if (goldValue >= 25) {
            textureID = TextureManager::AddTexture("Resources/loot/gold/Gold_Purse1.png");
        }
        else {
            textureID = TextureManager::AddTexture("Resources/loot/gold/spr_pickup_gold_medium.png");
        }
        // Set the sprite.
        SetSprite(TextureManager::GetTexture(textureID), 4, 9);
        // Set the item type.
        type = itemType;
    }
    else {
        hpPotionValue = 1 + std::rand() % 10;
        textureID = TextureManager::AddTexture("Resources/Images/Inventory/Small_Health_Potions.png");
        SetSprite(TextureManager::GetTexture(textureID), 4, 12);
        // Set the item type.
        type = itemType;
    }
}

// Gets the item type.
ITEM Items::GetType() const {
    return type;
}

int Items::GetValue() const {
    if (type == ITEM::GOLD) {
        return goldValue;
    }
    else
        return hpPotionValue;
}

void Items::Update(float _timeDelta) {

}
