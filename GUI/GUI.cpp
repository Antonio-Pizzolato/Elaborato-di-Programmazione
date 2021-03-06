#include "GUI.h"

//BUTTON
float GUI::p2pX(const float perc, sf::RenderWindow &window) {
    //Converts a percentage value to pixels relative to the current resolution in the x-axis.
    return std::floor(static_cast<float>(window.getSize().x) * (perc / 100.f));
}

float GUI::p2pY(const float perc, sf::RenderWindow &window) {
    //Converts a percentage value to pixels relative to the current resolution in the y-axis.
    return std::floor(static_cast<float>(window.getSize().y) * (perc / 100.f));
}

unsigned GUI::calcCharSize(sf::RenderWindow &window, const unsigned modifier) {
    //Calculates the character size for word using the current resolution and a constant.
    return static_cast<unsigned>((window.getSize().x + window.getSize().y) / modifier);
}

GUI::Button::Button(float x, float y, float width, float height, sf::Font *_font, const std::string &text, unsigned int character_size, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color idle_color, sf::Color hover_color, sf::Color active_color, sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color) {
    buttonState = BTN_IDLE;
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(idle_color);
    font = _font;
    word.setFont(*font);
    word.setString(text);
    word.setFillColor(text_idle_color);
    word.setCharacterSize(character_size);
    word.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - word.getGlobalBounds().width / 2.f, shape.getPosition().y);
    textIdleColor = text_idle_color;
    textHoverColor = text_hover_color;
    textActiveColor = text_active_color;
    idleColor = idle_color;
    hoverColor = hover_color;
    activeColor = active_color;
    outlineIdleColor = outline_idle_color;
    outlineHoverColor = outline_hover_color;
    outlineActiveColor = outline_active_color;
}

GUI::Button::~Button() = default;

//Accessors
bool GUI::Button::isPressed() const {
    if (buttonState == BTN_ACTIVE)
        return true;
    return false;
}

//Functions
void GUI::Button::update(const sf::Vector2i &mousePosWindow) {
    /*Update the booleans for hover and pressed*/
    //Idle
    buttonState = BTN_IDLE;
    //Hover
    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
        buttonState = BTN_HOVER;
        //Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            buttonState = BTN_ACTIVE;
        }
    }
    switch (buttonState) {
        case BTN_IDLE:
            shape.setFillColor(idleColor);
            word.setFillColor(textIdleColor);
            shape.setOutlineColor(outlineIdleColor);
            break;
        case BTN_HOVER:
            shape.setFillColor(hoverColor);
            word.setFillColor(textHoverColor);
            shape.setOutlineColor(outlineHoverColor);
            break;
        case BTN_ACTIVE:
            shape.setFillColor(activeColor);
            word.setFillColor(textActiveColor);
            shape.setOutlineColor(outlineActiveColor);
            break;
    }
}

void GUI::Button::render(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(word);
}

// PROGRESSBAR ============================================================================= PROGRESSBAR
GUI::ProgressBar::ProgressBar(float _x, float _y, float _width, float _height, sf::Color inner_color, unsigned character_size, sf::RenderWindow &window, sf::Font *font) {
    float width = GUI::p2pX(_width, window);
    float height = GUI::p2pY(_height, window);
    float x = GUI::p2pX(_x, window);
    float y = GUI::p2pY(_y, window);
    maxWidth = width;
    back.setSize(sf::Vector2f(width, height));
    back.setFillColor(sf::Color(50, 50, 50, 200));
    back.setPosition(x, y);
    inner.setSize(sf::Vector2f(width, height));
    inner.setFillColor(inner_color);
    inner.setPosition(back.getPosition());
    if (font) {
        text.setFont(*font);
        text.setCharacterSize(GUI::calcCharSize(window, character_size));
        text.setPosition(inner.getPosition().x + GUI::p2pX(0.53f, window), inner.getPosition().y + GUI::p2pY(0.5f, window));
    }
}

GUI::ProgressBar::~ProgressBar() = default;

//Functions
void GUI::ProgressBar::update(const int current_value, const int max_value) {
    float percent = static_cast<float>(current_value) / static_cast<float>(max_value);
    inner.setSize(sf::Vector2f(static_cast<float>(std::floor(maxWidth * percent)),inner.getSize().y));
    barString = std::to_string(current_value) + " / " + std::to_string(max_value);
    text.setString(barString);
}

void GUI::ProgressBar::render(sf::RenderWindow &window) {
    window.draw(back);
    window.draw(inner);
    window.draw(text);
}