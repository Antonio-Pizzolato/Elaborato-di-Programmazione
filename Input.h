//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_INPUT_H
#define MAIN_CPP_INPUT_H

class Input
{
public:

    /**
     * An enum denoting all possible input keys.
     */
    enum class KEY {
        KEY_LEFT,
        KEY_RIGHT,
        KEY_UP,
        KEY_DOWN,
        KEY_ATTACK,
        KEY_DASH,
        KEY_ESC,
        KEY_SPACE,
        KEY_I,
        KEY_P
    };

    /**
     * Checks if a given key is currently pressed.
     * @param keycode The key to check.
     * @return True if the given key is currently pressed.
     */
    static bool IsKeyPressed(KEY keycode);
};

#endif //MAIN_CPP_INPUT_H
