#include "Player.h"


//Constructors/Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet, PLAYER_CLASS type)
        : classType(type), initAttack(false), isAttacking(false), isDash(false),
          attackDelta(0.f), damageDelta(0.f),
          damageTimerMax(500), canTakeDamage(true),
          killNumber(0)
{

    speed = 200;

    // Create the player's aim sprite.
    int textureID = TextureManager::AddTexture("Resources/ui/53263.png");
    aimSprite.setTexture(TextureManager::GetTexture(textureID));
    aimSprite.setOrigin(sf::Vector2f(16.5f, 16.5f));
    aimSprite.setScale(0.15, 0.15);
}

Player::~Player() = default;


//Accessors
AttributeComponent *Player::getAttributeComponent()
{
    return attributeComponent;
}



bool Player::getDamageTimer()
{
    if(damageTimer.getElapsedTime().asMilliseconds() >= damageTimerMax)
    {
        damageTimer.restart();
        return true;
    }

    return false;
}

int Player::getDamage() const
{

    return attributeComponent->damageMax;
}

// Checks if the player can take damage.
bool Player::CanTakeDamage() const
{
    return canTakeDamage;
}

// Apply the given amount of damage to the player.
void Player::Damage(int damage)
{
    int applied_damage = static_cast<int>(damage - attributeComponent->defence);
    if(applied_damage < 0)
        applied_damage = 0;
    loseHp(applied_damage);

    canTakeDamage = false;
}

// Returns the player's class.
PLAYER_CLASS Player::GetClass() const
{
    return classType;
}

// Checks if the player is attacking.
bool Player::IsAttacking()
{
    if (isAttacking)
    {
        isAttacking = false;
        attackDelta = 0.f;
        return true;
    }
    else
    {
        return false;
    }
}


//Functions
void Player::loseHp(int hp)
{
    attributeComponent->loseHp(hp);
}

void Player::gainHp(int hp) {
    attributeComponent->gainHp(hp);
}

void Player::loseExp(int exp) {
    attributeComponent->loseExp(exp);
}

void Player::gainExp(int exp, PLAYER_CLASS playerClass) {
    attributeComponent->gainExp(exp, playerClass);
}

bool Player::isDead() const {
    if (attributeComponent) {
        return attributeComponent->isDead();
    }
    return false;
}



void Player::Update(float timeDelta, Level &level) {
    // Calculate movement speed based on the timeDelta since the last update.
    sf::Vector2f movementSpeed(0.f, 0.f);
    sf::Vector2f previousPosition = position;

    auto animState = ANIMATION_STATE::IDLE_UP;


    if (Input::IsKeyPressed(Input::KEY::KEY_LEFT))
    {
        // Set movement speed.
        movementSpeed.x = -speed * timeDelta;

        // Chose animation state.
        animState = ANIMATION_STATE::WALK_LEFT;

    }
    else if (Input::IsKeyPressed(Input::KEY::KEY_RIGHT))
    {
        // Set movement speed.
        movementSpeed.x = speed * timeDelta;

        // Chose animation state.
        animState = ANIMATION_STATE::WALK_RIGHT;
    }

    if (Input::IsKeyPressed(Input::KEY::KEY_UP))
    {
        // Set movement speed.
        movementSpeed.y = -speed * timeDelta;

        // Chose animation state.
        animState = ANIMATION_STATE::WALK_UP;


    }
    else if (Input::IsKeyPressed(Input::KEY::KEY_DOWN))
    {
        // Set movement speed.
        movementSpeed.y = speed * timeDelta;

        // Chose animation state.
        animState = ANIMATION_STATE::WALK_DOWN;
    }

    // Calculate horizontal movement.
    if (CausesCollision(sf::Vector2f(movementSpeed.x, 0.0f), level))
    {
        position.x = previousPosition.x;
    }
    else
    {
        position.x += movementSpeed.x;
    }

    // Calculate horizontal movement.
    if (CausesCollision(sf::Vector2f(0.0f, movementSpeed.y), level))
    {
        position.y = previousPosition.y;
    }
    else
    {
        position.y += movementSpeed.y;
    }

    // update the sprite position
    sprite.setPosition(position);

    // Calculate aim based on mouse.
    sf::Vector2i mousePos = sf::Mouse::getPosition();
    aimSprite.setPosition((float)mousePos.x, (float)mousePos.y);

    // Check if shooting.
    if ((attackDelta += timeDelta) > 0.25f)
    {
        if (Input::IsKeyPressed(Input::KEY::KEY_ATTACK))
        {
            // Mark player as attacking.
            isAttacking = true;
            initAttack = true;
        }
    }

    if (Input::IsKeyPressed(Input::KEY::KEY_DASH))
    {
        // Mark player as attacking.
        isDash = true;
        canTakeDamage = false;
    }



    updateAnimation(timeDelta, animState);

    // Determine if the player can take damage.
    if (!canTakeDamage)
    {
        if ((damageDelta += timeDelta) > 3.f)
        {
            canTakeDamage = true;
            damageDelta = 0.f;
        }
    }

}

// Returns a reference to the player's aim sprite.
sf::Sprite& Player::GetAimSprite()
{
    return aimSprite;
}

void Player::Draw(sf::RenderWindow &window, float _timeDelta) {

    window.draw(sprite);

}




















