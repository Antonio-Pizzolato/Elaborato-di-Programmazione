#include "Player.h"

//Initializer functions
void Player::initVariables() {
    this->attacking = false;
}

void Player::initComponents() {

}

//Constructors/Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet) {

    this->initVariables();

    this->setPosition(x, y);

    this->createHitboxComponent(this->sprite, 30.f, 14.f, 40.f, 60.f);
    this->createMovementComponent(350.f, 15.f, 5.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 3, 0, 100, 74);
    this->animationComponent->addAnimation("WALK", 6.f, 1, 1, 6, 1, 100, 74);
    this->animationComponent->addAnimation("ATTACK", 5.f, 0, 6, 6, 6, 100, 74);
}

Player::~Player() {

}

//Functions

void Player::updateAttack() {

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        this->attacking = true;
    }
}

void Player::updateAnimation(const float &dt) {
    if(this->attacking){
        //Set origin depending on direction
        if(this->sprite.getScale().x > 0.f) { //Facing left
            this->sprite.setOrigin(0.f, 0.f);
        }
        else{  //Facing right
            this->sprite.setOrigin(100.f + 0, 0.f);
        }
        //Animate and check for animation end
        if(this->animationComponent->play("ATTACK", dt, true)){

            this->attacking = false;

            if(this->sprite.getScale().x > 0.f) { //Facing left
                this->sprite.setOrigin(0.f, 0.f);
            }
            else{  //Facing right
                this->sprite.setOrigin(100.f + 0, 0.f);
            }
        }
    }
    if(this->movementComponent->getState(IDLE)){
        this->animationComponent->play("IDLE", dt);
    }
    else if(this->movementComponent->getState(MOVING_LEFT)){

        if(this->sprite.getScale().x > 0.f){
            this->sprite.setOrigin(100.f, 0.f);
            this->sprite.setScale(-1.f, 1.f);
        }

        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    }
    else if(this->movementComponent->getState(MOVING_RIGHT)){

        if(this->sprite.getScale().x < 0.f){
            this->sprite.setOrigin(0.f, 0.f);
            this->sprite.setScale(1.f, 1.f);
        }

        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    }
    else if(this->movementComponent->getState(MOVING_UP)){
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }
    else if(this->movementComponent->getState(MOVING_DOWN)){
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }
}

void Player::update(const float &dt) {

    this->movementComponent->update(dt);

    this->updateAttack();

    this->updateAnimation(dt);

    this->hitboxComponent->update();
}







