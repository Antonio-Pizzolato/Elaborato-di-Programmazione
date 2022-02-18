#include "Player.h"


//Constructors/Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet, PLAYER_CLASS type)
        : m_class(type), initAttack(false), m_isAttacking(false), m_isDash(false),
          m_attackDelta(0.f), m_damageDelta(0.f),
          damageTimerMax(500), m_canTakeDamage(true),
          killNumber(0)
{

    m_speed = 200;

    // Create the player's aim sprite.
    int textureID = TextureManager::AddTexture("Resources/ui/53263.png");
    m_aimSprite.setTexture(TextureManager::GetTexture(textureID));
    m_aimSprite.setOrigin(sf::Vector2f(16.5f, 16.5f));
    m_aimSprite.setScale(0.15, 0.15);
}

Player::~Player() {


}


//Accessors
AttributeComponent *Player::getAttributeComponent()
{
    return this->attributeComponent;
}


std::string Player::toStringCharacterTab() const
{
    std::stringstream ss;
    const AttributeComponent* ac = this->attributeComponent;
    //const Weapon* w = this->weapon;

    ss << "Level: " << ac->level << "\n"
       << "Exp: " << ac->exp << "\n"
       << "Exp next: " << ac->expNext << "\n"

        /*<< "Weapon Level: " << w->getLevel() << "\n"
        << "Weapon Type: " << w->getType() << "\n"
        << "Weapon Value: " << w->getValue() << "\n"
        << "Weapon Range: " << w->getRange() << "\n"
        << "Weapon Damage Min: " << w->getDamageMin() + this->attributeComponent->damageMin << " (" << this->attributeComponent->damageMin << ")" << "\n"
        << "Weapon Damage Max: " << w->getDamageMax() + this->attributeComponent->damageMax << " (" << this->attributeComponent->damageMax << ")" << "\n"*/;

    return ss.str();
}


bool Player::getDamageTimer()
{
    if(this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
    {
        this->damageTimer.restart();
        return true;
    }

    return false;
}

int Player::getDamage() const
{
    /*return rand() % (
            (this->attributeComponent->damageMax + this->weapon->getDamageMax())
            - (this->attributeComponent->damageMin + this->weapon->getDamageMin()) + 1)
           + (this->attributeComponent->damageMin + this->weapon->getDamageMin());*/

    return attributeComponent->damageMax;
}

// Checks if the player can take damage.
bool Player::CanTakeDamage() const
{
    return m_canTakeDamage;
}

// Apply the given amount of damage to the player.
void Player::Damage(int damage)
{
    int applied_damage = static_cast<int>(damage - attributeComponent->defence);
    if(applied_damage < 0)
        applied_damage = 0;
    loseHp(applied_damage);

    m_canTakeDamage = false;
}

// Returns the player's class.
PLAYER_CLASS Player::GetClass() const
{
    return m_class;
}

// Checks if the player is attacking.
bool Player::IsAttacking()
{
    if (m_isAttacking)
    {
        m_isAttacking = false;
        m_attackDelta = 0.f;
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
    this->attributeComponent->loseHp(hp);
}

void Player::gainHp(int hp) {
    this->attributeComponent->gainHp(hp);
}

void Player::loseExp(int exp) {
    this->attributeComponent->loseExp(exp);
}

void Player::gainExp(int exp, PLAYER_CLASS playerClass) {
    this->attributeComponent->gainExp(exp, playerClass);
}

bool Player::isDead() const {
    if (this->attributeComponent) {
        return this->attributeComponent->isDead();
    }
    return false;
}


void Player::updateAnimation(const float &dt, ANIMATION_STATE animState) {

    if (animState == ANIMATION_STATE::IDLE_UP) {
        this->animationComponent->play("IDLE", dt);
    }
    else if (animState == ANIMATION_STATE::WALK_LEFT) {

        /*if(this->sprite.getScale().x > 0.f){
            this->sprite.setOrigin(100.f, 0.f);
            this->sprite.setScale(-1.f, 1.f);
        }*/

        this->animationComponent->play("WALK_LEFT", dt, m_speed, m_speed);
    }
    else if(animState == ANIMATION_STATE::WALK_RIGHT){

        /*if(this->sprite.getScale().x < 0.f){
            this->sprite.setOrigin(0.f, 0.f);
            this->sprite.setScale(1.f, 1.f);
        }*/

        this->animationComponent->play("WALK_RIGHT", dt, m_speed, m_speed);
    }
    else if(animState == ANIMATION_STATE::WALK_UP){
        this->animationComponent->play("WALK_UP", dt, m_speed, m_speed);
    }
    else if(animState == ANIMATION_STATE::WALK_DOWN){
        this->animationComponent->play("WALK_DOWN", dt, m_speed, m_speed);
    }
}
void Player::Update(float timeDelta, Level &level) {
    // Calculate movement speed based on the timeDelta since the last update.
    sf::Vector2f movementSpeed(0.f, 0.f);
    sf::Vector2f previousPosition = m_position;

    auto animState = ANIMATION_STATE::IDLE_UP;


    if (Input::IsKeyPressed(Input::KEY::KEY_LEFT))
    {
        // Set movement speed.
        movementSpeed.x = -m_speed * timeDelta;

        // Chose animation state.
        animState = ANIMATION_STATE::WALK_LEFT;

    }
    else if (Input::IsKeyPressed(Input::KEY::KEY_RIGHT))
    {
        // Set movement speed.
        movementSpeed.x = m_speed * timeDelta;

        // Chose animation state.
        animState = ANIMATION_STATE::WALK_RIGHT;
    }

    if (Input::IsKeyPressed(Input::KEY::KEY_UP))
    {
        // Set movement speed.
        movementSpeed.y = -m_speed * timeDelta;

        // Chose animation state.
        animState = ANIMATION_STATE::WALK_UP;


    }
    else if (Input::IsKeyPressed(Input::KEY::KEY_DOWN))
    {
        // Set movement speed.
        movementSpeed.y = m_speed * timeDelta;

        // Chose animation state.
        animState = ANIMATION_STATE::WALK_DOWN;
    }

    // Calculate horizontal movement.
    if (CausesCollision(sf::Vector2f(movementSpeed.x, 0.0f), level))
    {
        m_position.x = previousPosition.x;
    }
    else
    {
        m_position.x += movementSpeed.x;
    }

    // Calculate horizontal movement.
    if (CausesCollision(sf::Vector2f(0.0f, movementSpeed.y), level))
    {
        m_position.y = previousPosition.y;
    }
    else
    {
        m_position.y += movementSpeed.y;
    }

    // update the sprite position
    m_sprite.setPosition(m_position);

    // Calculate aim based on mouse.
    sf::Vector2i mousePos = sf::Mouse::getPosition();
    m_aimSprite.setPosition((float)mousePos.x, (float)mousePos.y);

    // Check if shooting.
    if ((m_attackDelta += timeDelta) > 0.25f)
    {
        if (Input::IsKeyPressed(Input::KEY::KEY_ATTACK))
        {
            // Mark player as attacking.
            m_isAttacking = true;
            initAttack = true;
        }
    }

    if (Input::IsKeyPressed(Input::KEY::KEY_DASH))
    {
        // Mark player as attacking.
        m_isDash = true;
        m_canTakeDamage = false;
    }



    this->updateAnimation(timeDelta, animState);

    // Determine if the player can take damage.
    if (!m_canTakeDamage)
    {
        if ((m_damageDelta += timeDelta) > 3.f)
        {
            m_canTakeDamage = true;
            m_damageDelta = 0.f;
        }
    }

}

// Returns a reference to the player's aim sprite.
sf::Sprite& Player::GetAimSprite()
{
    return m_aimSprite;
}

void Player::render(sf::RenderWindow &window) {


    window.draw(m_sprite);


}




















