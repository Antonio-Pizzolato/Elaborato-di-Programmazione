//
// Created by Antonio on 22/07/2021.
//

#ifndef ELABORATO_DI_PROGRAMMAZIONE_GUI_H
#define ELABORATO_DI_PROGRAMMAZIONE_GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>
#include <vector>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace GUI{

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
               sf::Font *font, std::string text,unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
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
        void update(const sf::Vector2i& mousePosWindow);
        void render(sf::RenderTarget& target);
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
        void render(sf::RenderTarget& target);
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
        void render(sf::RenderTarget& target);
    };
}

#endif //ELABORATO_DI_PROGRAMMAZIONE_GUI_H
