#ifndef SFML_TEMPLATE_ENTITY_H
#define SFML_TEMPLATE_ENTITY_H

#include "../Components/AnimationComponent.h"
#include "../Components/AttributeComponent.h"
#include "../Map/Level.h"
#include "../Map/Object.h"
#include "../Util.h"

using namespace std;

class Entity : public Object{

private:


protected:

    AnimationComponent* animationComponent;
    AttributeComponent* attributeComponent;

    /**
	 * The entities movement speed.
	 */
    float m_speed;

    /**
	 * A vector of all texture IDs.
	 */
    int m_textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

    sf::Vector2f m_velocity;

    bool CausesCollision(sf::Vector2f movement, Level& level);

public:
    Entity(int level = 0);
    virtual ~Entity();

    //Component functions
    void setTexture(sf::Texture& texture);
    void createAnimationComponent(sf::Texture& texture_sheet);
    void createAttributeComponent(PLAYER_CLASS playerClass);

    void createSkillComponent();

    //Accessors
    virtual const sf::Vector2f& getPosition() const;
    virtual sf::Vector2f getCenter() const;
    virtual sf::Vector2i getGridPosition(const int gridSizeI) const;
    virtual sf::FloatRect getGlobalBounds() const;
    //virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
    //int GetHealth() const;

    //Modifiers
    virtual void setPosition(const float x, const float y);
    //Functions


    //Calculations
    virtual float getDistance(const Entity& entity) const;
    virtual float getSpriteDistance(const Entity& entity) const;

    virtual void Update(float dt) override;

};



#endif //SFML_TEMPLATE_ENTITY_H
