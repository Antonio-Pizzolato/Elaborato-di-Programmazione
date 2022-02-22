#include "Entity.h"

Entity::Entity(int level)
        : animationComponent(nullptr),
          attributeComponent(nullptr), m_speed(0),
          m_velocity({0.f, 0.f}),
          position{ 0.f, 0.f },
          animationSpeed(0),
          isAnimated(false),
          frameCount(0),
          currentFrame(0),
          frameWidth(0),
          frameHeight(0),
          timeDelta(0){

}

Entity::~Entity() {

    delete animationComponent;
    delete attributeComponent;
}

//Component functions


void Entity::createAnimationComponent(sf::Texture& texture_sheet) {
    animationComponent = new AnimationComponent(sprite, texture_sheet);
}

void Entity::createAttributeComponent(PLAYER_CLASS playerClass) {
    attributeComponent = new AttributeComponent(playerClass);
}




//Functions


// Checks is the given movement will result in a collision.
bool Entity::CausesCollision(sf::Vector2f movement, Level& level)
{
    // Get the tiles that the four corners other player are overlapping with.
    Tile* overlappingTiles[4];
    sf::Vector2f newPosition = position + movement;

    // Top left.
    overlappingTiles[0] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y - 14.f));

    // Top right.
    overlappingTiles[1] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y - 14.f));

    // Bottom left.
    overlappingTiles[2] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y + 14.f));

    // Bottom right.
    overlappingTiles[3] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y + 14.f));

    // If any of the overlapping tiles are solid there was a collision.
    for (auto & overlappingTile : overlappingTiles)
    {
        if (level.IsSolid(overlappingTile->columnIndex, overlappingTile->rowIndex))
            return true;
    }

    // If we've not returned yet no collisions were found.
    return false;
}


// Gives the object the given sprite.
bool Entity::SetSprite(sf::Texture& texture, bool isSmooth, int frames, int frameSpeed)
{
    // Create a sprite from the loaded texture.
    sprite.setTexture(texture);

    // Set animation speed.
    animationSpeed = frameSpeed;

    // Store the number of frames.
    frameCount = frames;

    // Calculate frame dimensions.
    sf::Vector2u texSize = sprite.getTexture()->getSize();
    frameWidth = texSize.x / frameCount;
    frameHeight = texSize.y;

    // Check if animated or static.
    if (frames > 1)
    {
        // Set sprite as animated.
        isAnimated = true;

        // Set the texture rect of the first frame.
        sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    }
    else
    {
        // Set sprite as non animated.
        isAnimated = false;
    }

    // Set the origin of the sprite.
    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);

    return true;
}



// Sets the position of the object.
void Entity::SetPosition(sf::Vector2f _position)
{
    position.x = _position.x;
    position.y = _position.y;
    sprite.setPosition(_position.x, _position.y);
}

// Returns the position of the object.
sf::Vector2f Entity::GetPosition() const
{
    return position;
}





// Draws the object to the given render window.
void Entity::Draw(sf::RenderWindow &window, float _timeDelta)
{
    // check if the sprite is animated
    if (isAnimated)
    {
        // add the elapsed time since the last draw call to the aggregate
        timeDelta += _timeDelta;

        // check if the frame should be updated
        if (timeDelta >= (1.f / animationSpeed))
        {
            NextFrame();
            timeDelta = 0;
        }
    }

    window.draw(sprite);
}

// Advances the sprite forward a frame.
void Entity::NextFrame()
{
    // check if we reached the last frame
    if (currentFrame == (frameCount - 1))
        currentFrame = 0;
    else
        currentFrame++;

    // update the texture rect
    sprite.setTextureRect(sf::IntRect(frameWidth * currentFrame, 0, frameWidth, frameHeight));
}








