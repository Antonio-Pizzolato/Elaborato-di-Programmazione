//
// Created by Antonio on 18/02/2022.
//

#include "Archer.h"

void Archer::initVariables() {

    //arrow_sheet.loadFromFile("Resources/Images/Sprites/Weapon/Projectile/Arrow.png");
}

void Archer::initAnimations()
{
    this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 9, 0, (100), (100));
    this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 1, 7, 1, 100, 100);
    this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 7, 1, 100, 100);
    this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 1, 7, 1, 100, 100);
    this->animationComponent->addAnimation("WALK_UP", 10.f, 0, 1, 7, 1, 100, 100);
    this->animationComponent->addAnimation("ATTACK", 3.f, 0, 2, 5, 2, 100, 100);

}


Archer::Archer(float x, float y, sf::Texture &texture_sheet, PLAYER_CLASS m_class)
        : Player(x, y, texture_sheet, m_class) {

    this->initVariables();


    this->createAnimationComponent(texture_sheet);
    this->createAttributeComponent(m_class);

    this->initAnimations();

    m_sprite.setOrigin(sf::Vector2f(50,50));

}


Archer::~Archer() {

}


void Archer::updateAttack(const float &dt)
{
    if (initAttack) {

        //Animate and check for animation end
        if (this->animationComponent->play("ATTACK", dt, true)) {

            initAttack = false;

        }
    }
}

void Archer::updateAnimation(const float &dt, ANIMATION_STATE animState)
{
    updateAttack(dt);
    if (animState == ANIMATION_STATE::IDLE_UP) {
        this->animationComponent->play("IDLE", dt);
        m_sprite.setScale(1.2, 1.2);
    }
    else if (animState == ANIMATION_STATE::WALK_LEFT) {

        if (this->m_sprite.getScale().x > 0.f) {

            this->m_sprite.setScale(-1.2, 1.2);
        }

        this->animationComponent->play("WALK_LEFT", dt, m_speed,
                                       m_speed);
    } else if (animState == ANIMATION_STATE::WALK_RIGHT) {

        if (this->m_sprite.getScale().x < 0.f) {

            this->m_sprite.setScale(1.2, 1.2);
        }

        this->animationComponent->play("WALK_RIGHT", dt, m_speed,
                                       m_speed);
    } else if (animState == ANIMATION_STATE::WALK_UP) {
        this->animationComponent->play("WALK_UP", dt, m_speed,
                                       m_speed);
    } else if (animState == ANIMATION_STATE::WALK_DOWN) {
        this->animationComponent->play("WALK_DOWN", dt, m_speed,
                                       m_speed);
    }
}

