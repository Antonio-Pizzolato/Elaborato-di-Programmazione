//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_ENEMY_H
#define MAIN_CPP_ENEMY_H


#include "Entity.h"
#include "../Components/EnemyAttributeComponent.h"
#include "../Map/Level.h"

static const int ENEMY_MAX_DAMAGE = 25;
static const float ENEMY_DEXTERITY_DAMAGE_SCALE = 0.025f;
static const float ENEMY_ATTACK_DAMAGE_SCALE = 0.15f;
static const float ENEMY_TAKEN_DAMAGE_REDUCTION_SCALE = 0.15f;
static const int ENEMY_PATHFINDING_STEP_COST = 10;


class Enemy : public Entity
{
public:
    /**
     * Default constructor.
     */
    Enemy(int level = 0);
    ~Enemy() override;

    void createEnemyAttributeComponent(int level, ENEMY enemy);
    /**
     * Overrides the default Update function in Enemy
     */
    void Update(float timeDelta, Level &level);

    /**
     * Applies the given amount of damage to the enemy.
     * @param damage The amount of damage to deal to the enemy.
     */
    void Damage(int damage);

    /**
     * Checks if the enemy has taken enough damage that they are now dead.
     * @return True if the enemy is dead.
     */
    bool IsDead();

    /**
     * Calculate an amount of damage to an enemy.
     * @return Dealt damage to an enemy.
     */
    int CalculateDamage();

    /**
     * Recalculates the target position of the enemy.
     */
    void UpdatePathfinding(Level& level, sf::Vector2f playerPosition);
private:
    /**
     * The target positions of the enemy.
     */
    std::vector<sf::Vector2f> m_targetPositions;

    EnemyAttributeComponent* enemyAttributeComponent;

    /**
     * The current target of the enemy.
     */
    sf::Vector2f m_currentTarget;

};



#endif //MAIN_CPP_ENEMY_H
