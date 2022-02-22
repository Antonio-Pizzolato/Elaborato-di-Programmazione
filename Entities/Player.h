#ifndef SFML_TEMPLATE_PLAYER_H
#define SFML_TEMPLATE_PLAYER_H

#include "Entity.h"
#include "../Projectile/Projectile.h"
#include "../Input.h"


class Player :
        public Entity {
protected:
    //Variables
    PLAYER_CLASS m_class;


    bool initAttack;
    bool m_isAttacking;
    bool m_isDash;

    sf::Clock damageTimer;
    sf::Int32 damageTimerMax;
    float m_damageDelta;

    /**
     * The sprite for the player's aim cross hair.
     */
    sf::Sprite m_aimSprite;

    /**
     * The time since the player's last attack.
     */
    float m_attackDelta;


    /**
     * Can the player take damage.
     */
    bool m_canTakeDamage;



public:
    Player(float x, float y, sf::Texture& texture_sheet, PLAYER_CLASS m_class);
    virtual ~Player();

    //Accessors
    AttributeComponent* getAttributeComponent();
    //Weapon* getWeapon() const;


    std::string toStringCharacterTab() const;


    bool getDamageTimer();

    /**
     * Gets the player's aim sprite.
     * return The player's aim sprite.
     */
    sf::Sprite& GetAimSprite();

    /**
     * Checks if the player can take damage.
     * @return True if the player can take damage.
     */
    bool CanTakeDamage() const;

    /**
     * Apply the given amount of damage to the player.
     * @param damage The amount of damage to deal to the player.
     */
    void Damage(int damage);
    int getDamage() const;
    PLAYER_CLASS GetClass() const;
    bool IsAttacking();

    //Modifier


    //Functions
    void loseHp(int hp);
    void gainHp(int hp);
    void loseExp(int exp);
    void gainExp(int exp, PLAYER_CLASS playerClass);

    virtual bool isDead() const;

    virtual void updateAttack(const float& dt) = 0;
    virtual void updateAnimation(const float& dt, ANIMATION_STATE animState);
    void Update(float timeDelta, Level& level) override;
    virtual void render(sf::RenderWindow &window);


    int killNumber;
};


#endif //SFML_TEMPLATE_PLAYER_H
