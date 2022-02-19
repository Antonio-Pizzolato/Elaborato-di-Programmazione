#ifndef MAIN_CPP_UTIL_H
#define MAIN_CPP_UTIL_H

// Game states.
enum class GAME_STATE {
    MAIN_MENU,
    CHARACTER_SELECT,
    PLAYING,
    GAME_OVER,
    PAUSED,
    INVENTORY,
    SHOP
};

// Spawn_able items.
enum class ITEM {
    GOLD,
    POTION
};

// Enemy types.
enum class ENEMY {
    SLIME,
    HUMANOID,
    COUNT
};

// Enemy humanoid types.
enum class HUMANOID {
    GOBLIN,
    SKELETON,
    COUNT
};

// Animation states.
enum class ANIMATION_STATE {
    WALK_UP,
    WALK_DOWN,
    WALK_RIGHT,
    WALK_LEFT,
    IDLE_UP,
    IDLE_DOWN,
    IDLE_RIGHT,
    IDLE_LEFT,
    COUNT
};

// Tiles.
enum class TILE {
    WALL_SINGLE,
    WALL_TOP_END,
    WALL_SIDE_RIGHT_END,
    WALL_BOTTOM_LEFT,
    WALL_BOTTOM_END,
    WALL_SIDE,
    WALL_TOP_LEFT,
    WALL_SIDE_LEFT_T,
    WALL_SIDE_LEFT_END,
    WALL_BOTTOM_RIGHT,
    WALL_TOP,
    WALL_BOTTOM_T,
    WALL_TOP_RIGHT,
    WALL_SIDE_RIGHT_T,
    WALL_TOP_T,
    WALL_INTERSECTION,
    WALL_DOOR_LOCKED,
    WALL_DOOR_UNLOCKED,
    WALL_ENTRANCE,
    FLOOR,
    FLOOR_ALT,
    EMPTY,
    COUNT
};

enum class PLAYER_CLASS {
    WARRIOR, WIZARD, ARCHER
};

// Potions.
enum class POTION {
    ATTACK,
    DEFENSE,
    STRENGTH,
    DEXTERITY,
    STAMINA,
    HP,
    COUNT
};

enum class Event{
    Kill,
    Die
};

#endif //MAIN_CPP_UTIL_H
