#include "Warrior.h"

Warrior::Warrior(float x, float y, sf::Texture &texture_sheet, PLAYER_CLASS m_class)
        : Player(x, y, texture_sheet, m_class) {



    createAnimationComponent(texture_sheet);
    createAttributeComponent(m_class);

    animationComponent->addAnimation("IDLE", 10.f, 0, 0, 3, 0, 100, 74);
    animationComponent->addAnimation("WALK_DOWN", 10.f, 1, 1, 6, 1, 100, 74);
    animationComponent->addAnimation("WALK_LEFT", 10.f, 1, 1, 6, 1, 100, 74);
    animationComponent->addAnimation("WALK_RIGHT", 10.f, 1, 1, 6, 1, 100, 74);
    animationComponent->addAnimation("WALK_UP", 10.f, 1, 1, 6, 1, 100, 74);
    animationComponent->addAnimation("ATTACK", 5.f, 0, 7, 3, 7, 100, 74);
    animationComponent->addAnimation("DASH", 10.f, 0, 2, 6, 2, 100, 74);


    sprite.setOrigin(sf::Vector2f(50,37));


}


Warrior::~Warrior() = default;

void Warrior::updateAttack(const float &dt)
{
    if (initAttack) {
        //Animate and check for animation end
        if (animationComponent->play("ATTACK", dt, true)) {

            initAttack = false;

        }
    }
    if(m_isDash){
        if (animationComponent->play("DASH", dt, true)) {

            m_isDash = false;


        }
    }
}

void Warrior::updateAnimation(const float &dt, ANIMATION_STATE animState)
{

    updateAttack(dt);

    if (animState == ANIMATION_STATE::IDLE_UP) {
        animationComponent->play("IDLE", dt);
    }
    else if (animState == ANIMATION_STATE::WALK_LEFT) {

        if (sprite.getScale().x > 0.f) {

            sprite.setScale(-1.f, 1.f);
        }

        animationComponent->play("WALK_LEFT", dt, m_speed,
                                 m_speed);
    } else if (animState == ANIMATION_STATE::WALK_RIGHT) {

        if (sprite.getScale().x < 0.f) {

            sprite.setScale(1.f, 1.f);
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






