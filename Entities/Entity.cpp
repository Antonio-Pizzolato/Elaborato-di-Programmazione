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

sf::Vector2f Entity::getCenter() const {
    return m_sprite.getPosition() + sf::Vector2f(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
}

sf::Vector2i Entity::getGridPosition(const int gridSizeI) const {
    return sf::Vector2i(static_cast<int>(m_sprite.getPosition().x) / gridSizeI,
                        static_cast<int>(m_sprite.getPosition().y) / gridSizeI);
}

sf::FloatRect Entity::getGlobalBounds() const {
    return m_sprite.getGlobalBounds();
}

/*const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const {
    if(hitboxComponent && movementComponent){
        return hitboxComponent->getNextPosition(movementComponent->getVelocity() * dt);
    }
    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}*/

//Functions
void Entity::setPosition(const float x, const float y) {
    m_sprite.setPosition(x, y);

}






float Entity::getDistance(const Entity& entity) const
{
    return sqrt(pow(getCenter().x - entity.getCenter().x, 2) + pow(getCenter().y - entity.getCenter().y, 2));
}

float Entity::getSpriteDistance(const Entity& entity) const
{
    //return sqrt(pow(getSpriteCenter().x - entity.getSpriteCenter().x, 2) + pow(getSpriteCenter().y - entity.getSpriteCenter().y, 2));
}

// Override the default Object::Update function.
void Entity::Update(float timeDelta)
{
    // Choose animation state.
    auto animState = ANIMATION_STATE::IDLE_UP;

    if ((m_velocity.x != 0) || (m_velocity.y != 0))
    {
        if (std::abs(m_velocity.x) > std::abs(m_velocity.y))
        {
            if (m_velocity.x <= 0)
            {
                animState = ANIMATION_STATE::WALK_LEFT;
            }
            else
            {
                animState = ANIMATION_STATE::WALK_RIGHT;
            }
        }
        else
        {
            if (m_velocity.y <= 0)
            {
                animState = ANIMATION_STATE::WALK_UP;
            }
            else
            {
                animState = ANIMATION_STATE::WALK_DOWN;
            }
        }
    }


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

















