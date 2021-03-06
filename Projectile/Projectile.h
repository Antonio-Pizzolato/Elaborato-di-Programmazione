#ifndef MAIN_CPP_PROJECTILE_H
#define MAIN_CPP_PROJECTILE_H

#include "../Map/Object.h"

class Projectile : public Object {
public:
    /**
     * The velocity of the projectile.
     */
    sf::Vector2f velocity;

    /**
      * Default constructor.
      * @param texture The texture of the projectile.
      * @param origin The location that the projectile should be created at.
      * @param screenCenter The center of the screen. Used to calculate direction.
      * @param target The target location of the projectile.
      */
    Projectile(sf::Texture &texture, sf::Vector2f origin, sf::Vector2f screenCenter, sf::Vector2f target);

    /**
        * Override of the update function.
        * @param timeDelta The time in seconds since the last update.
        */
    void Update(float timeDelta) override;
};

#endif //MAIN_CPP_PROJECTILE_H
