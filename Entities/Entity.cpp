#include "Entity.h"


Entity::Entity(int level)
        : animationComponent(nullptr),
          attributeComponent(nullptr), m_speed(0),
          m_velocity({0.f, 0.f}){

}

Entity::~Entity() {

    delete animationComponent;
    delete attributeComponent;
}

//Component functions
void Entity::setTexture(sf::Texture& texture) {
    m_sprite.setTexture(texture);
}


void Entity::createAnimationComponent(sf::Texture& texture_sheet) {
    animationComponent = new AnimationComponent(m_sprite, texture_sheet);
}

void Entity::createAttributeComponent(PLAYER_CLASS playerClass) {
    attributeComponent = new AttributeComponent(playerClass);
}

const sf::Vector2f &Entity::getPosition() const {

    return m_sprite.getPosition();
}


//Functions
void Entity::setPosition(const float x, const float y) {
    m_sprite.setPosition(x, y);

}


// Checks is the given movement will result in a collision.
bool Entity::CausesCollision(sf::Vector2f movement, Level& level)
{
    // Get the tiles that the four corners other player are overlapping with.
    Tile* overlappingTiles[4];
    sf::Vector2f newPosition = m_position + movement;

    // Top left.
    overlappingTiles[0] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y - 14.f));

    // Top right.
    overlappingTiles[1] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y - 14.f));

    // Bottom left.
    overlappingTiles[2] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y + 14.f));

    // Bottom right.
    overlappingTiles[3] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y + 14.f));

    // If any of the overlapping tiles are solid there was a collision.
    for (int i = 0; i < 4; i++)
    {
        if (level.IsSolid(overlappingTiles[i]->columnIndex, overlappingTiles[i]->rowIndex))
            return true;
    }

    // If we've not returned yet no collisions were found.
    return false;
}

















