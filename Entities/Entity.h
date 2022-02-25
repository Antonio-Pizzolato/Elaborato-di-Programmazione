#ifndef SFML_TEMPLATE_ENTITY_H
#define SFML_TEMPLATE_ENTITY_H

#include "../Components/AnimationComponent.h"
#include "../Components/AttributeComponent.h"
#include "../Map/Level.h"
#include "../Util.h"

using namespace std;

class Entity {
protected:
    AnimationComponent *animationComponent;
    AttributeComponent *attributeComponent;
    /**
	 * The entities movement speed.
	 */
    float speed;
    /**
    * The object's sprite.
    */
    sf::Sprite sprite;

    /**
	 * A vector of all texture IDs.
	 */
    int textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];
    sf::Vector2f velocity;
public:
    /**
     * The animation speed of the image if applicable.
     * Value is frames per second.
     */
    int animationSpeed;
    /**
     * Used to determine if the given sprite is animated.
     */
    bool isAnimated;
    /**
     * The total number of frames the sprite has.
     */
    int frameCount;
    /**
     * The current frame of the sprite.
     */
    int currentFrame;
    /**
     * The width of each frame of the animated sprite if applicable.
     */
    int frameWidth;
    /**
     * The height of each frame of the animated sprite if applicable.
     */
    int frameHeight;
    /**
     * An aggregate of the time passed between draw calls.
     */
    float timeDelta;
    /**
     * The position of the object in the game window.
     */
    sf::Vector2f position;

    explicit Entity(int level = 0);
    virtual ~Entity();

    //Component functions
    void createAnimationComponent(sf::Texture &texture_sheet);
    void createAttributeComponent(PLAYER_CLASS playerClass);
    virtual void Update(float dt, Level &level) = 0;
    /**
     * Draws the object to the screen at its current position.
     * @param window The render window to draw the object to.
     * @param tileDelta The time, in MS, since the last draw call.
     */
    virtual void Draw(sf::RenderWindow &window, float timeDelta) = 0;
    /**
     * Sets the position of the object on screen. This is relative to the top-left of the game window.
     * @param position The new position of the player.
     */
    void SetPosition(sf::Vector2f position);
    /**
     * Returns the position of the object. This is relative to the top-left of the game window.
     * @return The position of the object
     */
    sf::Vector2f GetPosition() const;
    /**
     * Creates and sets the object sprite.
     * This function takes the location to a resource, and from that create a texture and sprite.
     * You can optionally specify animation properties. If set the frame dimensions will be calculated automatically.
     * If left blank, the whole resource will be used.
     * @param fileName The path to the resource that you wish to load, relative to the project.
     * @param frames The number of frames in the sprite. Defaults to 1.
     * @param frameSpeed The speed that the animation plays at. Defaults to 1.
     * @return true if the operation succeeded.
     */
    bool SetSprite(sf::Texture &texture, int frames = 1, int frameSpeed = 0);
    /**
     * Advances the sprite by a frame.
     */
    void NextFrame();

    bool CausesCollision(sf::Vector2f movement, Level &level);
};

#endif //SFML_TEMPLATE_ENTITY_H
