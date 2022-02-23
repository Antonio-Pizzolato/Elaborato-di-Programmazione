#include "Projectile.h"

#include <cmath>

Projectile::Projectile(sf::Texture& texture, sf::Vector2f origin, sf::Vector2f screenCenter, sf::Vector2f target)
{
    // Create the sprite.
    SetSprite(texture);

    // Set the sprite position.
    sprite.setPosition(origin);

    // Set the position.
    position = origin;

    if (origin.x > target.x && origin.y - target.y < -10 && origin.y - target.y > 10) {

        sprite.setScale(-1, 1);
    }
    else if (origin.x < target.x && origin.y - target.y < -10 && origin.y - target.y > 10) {

        sprite.setScale(1, 1);
    }
    else if(origin.y < target.y){
        sprite.rotate(90);
    }
    else if(origin.y > target.y){
        sprite.rotate(-90);
    }



    // Calculate the velocity of the object.
    velocity = target - screenCenter;

    float length = std::sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    velocity.x /= length;
    velocity.y /= length;
}

// Update the projectile.
void Projectile::Update(float timeDelta)
{
    // Update rotation.
    //sprite.setRotation(sprite.getRotation() + (400.f * timeDelta));

    // Update position.
    sprite.setPosition(sprite.getPosition().x + (velocity.x * (500 * timeDelta)), sprite.getPosition().y + (velocity.y * (500 * timeDelta)));
    position = sprite.getPosition();
}