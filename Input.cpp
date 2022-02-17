#include "Input.h"
#include "TextureManager.h"


// Returns true if the given key is pressed.
bool Input::IsKeyPressed(KEY keycode)
{
    switch (keycode)
    {
        case Input::KEY::KEY_LEFT:
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
            {
                return true;
            }
            break;

        case Input::KEY::KEY_RIGHT:
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
            {
                return true;
            }
            break;

        case Input::KEY::KEY_UP:
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
            {
                return true;
            }
            break;

        case Input::KEY::KEY_DOWN:
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
            {
                return true;
            }
            break;

        case Input::KEY::KEY_ATTACK:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                return true;
            }
            break;

        case Input::KEY::KEY_DASH:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                return true;
            }
            break;

        case Input::KEY::KEY_ESC:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                return true;
            }
            break;

        case Input::KEY::KEY_SPACE:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                return true;
            }
            break;
        case Input::KEY::KEY_I:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                return true;
            }
            break;
        case Input::KEY::KEY_P:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                return true;
            }
            break;
    }

    return false;
}