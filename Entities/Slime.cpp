//
// Created by Antonio on 18/02/2022.
//

#include "Slime.h"


// Default constructor.
Slime::Slime(int level)
{
    // Load textures.
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture(/*"Resources/enemies/slime/spr_slime_walk_up.png"*/"Resources/enemies/slime/slimesprite.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture(/*"Resources/enemies/slime/spr_slime_walk_down.png"*/"Resources/enemies/slime/slimesprite.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture(/*"Resources/enemies/slime/spr_slime_walk_right.png"*/"Resources/enemies/slime/slimesprite.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture(/*"Resources/enemies/slime/spr_slime_walk_left.png"*/"Resources/enemies/slime/slimesprite1.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture(/*"Resources/enemies/slime/spr_slime_idle_up.png"*/"Resources/enemies/slime/slimesprite.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture(/*"Resources/enemies/slime/spr_slime_idle_down.png"*/"Resources/enemies/slime/slimesprite.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture(/*"Resources/enemies/slime/spr_slime_idle_right.png"*/"Resources/enemies/slime/slimesprite.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture(/*"Resources/enemies/slime/spr_slime_idle_left.png"*/"Resources/enemies/slime/slimesprite1.png");

    // Set initial sprite.
    SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)]), false, 4, 6);

    // Set a random color for the slime sprite.
    /*sf::Uint8 r, g, b, a;
    r = static_cast<sf::Uint8>(std::rand() % 256);
    g = static_cast<sf::Uint8>(std::rand() % 256);
    b = static_cast<sf::Uint8>(std::rand() % 256);
    a = static_cast<sf::Uint8>((std::rand() % 156) + 100);

    sf::Color color(r, g, b, a);
    m_sprite.setColor(color);*/

    createEnemyAttributeComponent(level, ENEMY::SLIME);
}