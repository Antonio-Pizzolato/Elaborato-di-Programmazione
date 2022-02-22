#include "Potion.h"


Potion::Potion() {
    hpPotionValue = 1 + std::rand() % 10;
    int textureID=TextureManager::AddTexture("Resources/Images/Inventory/Small_Health_Potions.png");
    SetSprite(TextureManager::GetTexture(textureID), false, 4, 12);

    // Set the item type.
    m_type = ITEM::POTION;
}

int Potion::GetHpValue() const {
    return hpPotionValue;
}
