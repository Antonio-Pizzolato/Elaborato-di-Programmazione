//
// Created by Antonio on 18/02/2022.
//

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

    const float p2pX(const float perc, const sf::VideoMode& vm);
    const float p2pY(const float perc, const sf::VideoMode& vm);
    const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);

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
        const bool isPressed() const;
        const std::string getText() const;
        const short unsigned& getId() const;

        //Modifiers
        void setText(const std::string text);
        void setId(const short unsigned id);

        //Functions
        void updatePosition(sf::Vector2f position);
        void update(const sf::Vector2i& mousePosWindow);
        void render(sf::RenderWindow &window);
    };

    class DropDownList{
    private:
        float keyTime;
        float keyTimeMax;
        sf::Font& font;
        GUI::Button* activeElement;
        std::vector<GUI::Button*> list;
        bool showList;


    public:
        DropDownList(float x, float y, float width, float height,
                     sf::Font& font, std::string list[],
                     unsigned nrOfElements, unsigned default_index = 0);
        ~DropDownList();

        //Accessors
        const unsigned short& getActiveElementId() const;

        //Functions
        const bool getKeyTime();
        void updateKeyTime(const float& dt);
        void update(const sf::Vector2i &mousePosWindow, const float& dt);
        void render(sf::RenderWindow &window);
    };

    class TextureSelector{
    private:
        float keyTime;
        const float keyTimeMax;
        float gridSize;
        bool active;
        bool hidden;
        GUI::Button* hide_btn;

        sf::RectangleShape bounds;
        sf::Sprite sheet;
        sf::RectangleShape selector;
        sf::Vector2u mousePosGrid;
        sf::IntRect textureRect;

    public:
        TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text);
        ~TextureSelector();

        //Accessors
        const bool& getActive() const;
        const sf::IntRect& getTextureRect() const;

        //Functions
        const bool getKeyTime();
        void updateKeyTime(const float& dt);
        void update(const sf::Vector2i& mousePosWindow, const float& dt);
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

        //Accessors

        //Modifiers

        //Functions
        void update(const int current_value, const int max_value);
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
