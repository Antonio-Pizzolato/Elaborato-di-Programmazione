#include "Archer.h"


Archer::Archer(sf::Texture &texture_sheet, PLAYER_CLASS m_class)
        : Player(texture_sheet, m_class) {
    createAnimationComponent(texture_sheet);
    createAttributeComponent(m_class);
    animationComponent->addAnimation("IDLE", 10.f, 0, 0, 9, 0, 100, 100);
    animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 1, 7, 1, 100, 100);
    animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 7, 1, 100, 100);
    animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 1, 7, 1, 100, 100);
    animationComponent->addAnimation("WALK_UP", 10.f, 0, 1, 7, 1, 100, 100);
    animationComponent->addAnimation("ATTACK", 3.f, 0, 2, 5, 2, 100, 100);
    sprite.setOrigin(sf::Vector2f(50, 50));
}

Archer::~Archer() = default;

void Archer::updateAttack(const float &dt) {
    if (initAttack) {
        //Animate and check for animation end
        if (animationComponent->play("ATTACK", dt, true)) {
            initAttack = false;
        }
    }
}

void Archer::updateAnimation(const float &dt, ANIMATION_STATE animState) {
    updateAttack(dt);
    if (animState == ANIMATION_STATE::IDLE_UP) {
        animationComponent->play("IDLE", dt);
        sprite.setScale(1.2, 1.2);
    }
    else if (animState == ANIMATION_STATE::WALK_LEFT) {
        if (sprite.getScale().x > 0.f) {
            sprite.setScale(-1.2, 1.2);
        }
        animationComponent->play("WALK_LEFT", dt, speed, speed);
    }
    else if (animState == ANIMATION_STATE::WALK_RIGHT) {
        if (sprite.getScale().x < 0.f) {
            sprite.setScale(1.2, 1.2);
        }
        animationComponent->play("WALK_RIGHT", dt, speed, speed);
    }
    else if (animState == ANIMATION_STATE::WALK_UP) {
        animationComponent->play("WALK_UP", dt, speed, speed);
    }
    else if (animState == ANIMATION_STATE::WALK_DOWN) {
        animationComponent->play("WALK_DOWN", dt, speed, speed);
    }
}