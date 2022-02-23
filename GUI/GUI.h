#ifndef MAIN_CPP_GUI_H
#define MAIN_CPP_GUI_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>
#include <vector>
#include <cmath>
#include<fstream>
#include<stack>
#include<map>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace GUI{

    float p2pX( float perc, sf::RenderWindow &window);
    float p2pY( float perc, sf::RenderWindow &window);
    unsigned calcCharSize(sf::RenderWindow &window,  unsigned modifier = 60);

    class Button {
    private:
        short unsigned buttonState;
        short unsigned id;

        sf::RectangleShape shape;
        sf::Font *font;
        sf::Text text;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Color outlineIdleColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;


    public:
        Button(float x, float y, float width, float height,
               sf::Font *font, const std::string& text,unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color = sf::Color::Red, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
               short unsigned id = 0);
        ~Button();

        //Accessors
        bool isPressed() const;
        std::string getText() const;
        const short unsigned& getId() const;

        //Modifiers
        void setText(const std::string& text);
        void setId(short unsigned id);

        //Functions
        void updatePosition(sf::Vector2f position);
        void update(const sf::Vector2i& mousePosWindow);
        void render(sf::RenderWindow &window);
    };

    class ProgressBar
    {
    private:
        std::string barString;
        sf::Text text;
        float maxWidth;
        sf::RectangleShape back;
        sf::RectangleShape inner;

    public:
        ProgressBar(float x, float y, float width, float height,
                    sf::Color inner_color, unsigned character_size,
                    sf::RenderWindow &window, sf::Font* font = nullptr);
        ~ProgressBar();

        //Functions
        void update(int current_value, int max_value);
        void render(sf::RenderWindow &window);
    };



    class Slot {
    private:
        short unsigned buttonState;

        sf::Sprite shape;


    public:
        Slot(float x, float y, const sf::Texture& texture);
        ~Slot();

        //Accessors
        bool isPressed() const;

        //Modifiers

        //Functions
        void update(const sf::Vector2i& mousePosWindow);
        void render(sf::RenderWindow &window);
    };
}



#endif //MAIN_CPP_GUI_H
