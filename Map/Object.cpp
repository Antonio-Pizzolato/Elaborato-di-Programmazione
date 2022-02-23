#include "Object.h"

// Default constructor.
Object::Object() :
        position{0.f, 0.f },
        animationSpeed(0),
        isAnimated(false),
        frameCount(0),
        currentFrame(0),
        frameWidth(0),
        frameHeight(0),
        timeDelta(0)
{
}

// Gives the object the given sprite.
bool Object::SetSprite(sf::Texture& texture, int frames, int frameSpeed)
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
        // Set sprite as non-animated.
        isAnimated = false;
    }

    // Set the origin of the sprite.
    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);

    return true;
}

// Returns the object's sprite.
sf::Sprite& Object::GetSprite()
{
    return sprite;
}

// Sets the position of the object.
void Object::SetPosition(sf::Vector2f _position)
{
    position.x = _position.x;
    position.y = _position.y;
    sprite.setPosition(position.x, position.y);
}

// Returns the position of the object.
sf::Vector2f Object::GetPosition() const
{
    return position;
}

// Gets the current animation state of the object.
bool Object::IsAnimated() const
{
    return isAnimated;
}

// Sets the animation state of the object.
void Object::SetAnimated(bool _isAnimated)
{
    isAnimated = _isAnimated;

    if (isAnimated)
    {
        currentFrame = 0;
    }
    else
    {
        // set the texture rect of the first frame
        sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    }
}

// Draws the object to the given render window.
void Object::Draw(sf::RenderWindow &window, float _timeDelta)
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
void Object::NextFrame()
{
    // check if we reached the last frame
    if (currentFrame == (frameCount - 1))
        currentFrame = 0;
    else
        currentFrame++;

    // update the texture rect
    sprite.setTextureRect(sf::IntRect(frameWidth * currentFrame, 0, frameWidth, frameHeight));
}

Object::~Object() = default;;
