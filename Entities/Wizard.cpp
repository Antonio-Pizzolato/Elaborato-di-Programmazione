//
// Created by Antonio on 18/02/2022.
//

#include "Wizard.h"


void Wizard::initVariables() {

}

void Wizard::initAnimations() {
    animationComponent->addAnimation("IDLE", 10.f, 0, 0, 5, 0, (96), (96));
    animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 1, 7, 1, 96, 96);
    animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 7, 1, 96, 96);
    animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 1, 7, 1, 96, 96);
    animationComponent->addAnimation("WALK_UP", 10.f, 0, 1, 7, 1, 96, 96);
    animationComponent->addAnimation("ATTACK", 3.f, 0, 2, 7, 2, 96, 96);

}

Wizard::Wizard(float x, float y, sf::Texture &texture_sheet, PLAYER_CLASS m_class)
        : Player(x, y, texture_sheet, m_class) {


    initVariables();



    createAnimationComponent(texture_sheet);
    createAttributeComponent(m_class);

    initAnimations();

    sprite.setOrigin(sf::Vector2f(40,50));
}

Wizard::~Wizard() {

}

void Wizard::updateAttack(const float &dt){
    if (initAttack) {

        //Animate and check for animation end
        if (animationComponent->play("ATTACK", dt, true)) {

            initAttack = false;

        }
    }
}

void Wizard::updateAnimation(const float &dt, ANIMATION_STATE animState) {

    updateAttack(dt);
    if (animState == ANIMATION_STATE::IDLE_UP) {
        animationComponent->play("IDLE", dt);
        sprite.setScale(1.2, 1.2);
    }
    else if (animState == ANIMATION_STATE::WALK_LEFT) {

        if (sprite.getScale().x > 0.f) {

            sprite.setScale(-1.2, 1.2);
        }

        animationComponent->play("WALK_LEFT", dt, m_speed,
                                       m_speed);
    } else if (animState == ANIMATION_STATE::WALK_RIGHT) {

        if (sprite.getScale().x < 0.f) {

            sprite.setScale(1.2, 1.2);
        }

        animationComponent->play("WALK_RIGHT", dt, m_speed,
                                       m_speed);
    } else if (animState == ANIMATION_STATE::WALK_UP) {
        animationComponent->play("WALK_UP", dt, m_speed,
                                       m_speed);
    } else if (animState == ANIMATION_STATE::WALK_DOWN) {
        animationComponent->play("WALK_DOWN", dt, m_speed,
                                       m_speed);
    }
}

