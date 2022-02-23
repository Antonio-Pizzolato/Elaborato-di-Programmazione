//
// Created by Antonio on 18/02/2022.
//

#ifndef MAIN_CPP_TEXTTAGSYSTEM_H
#define MAIN_CPP_TEXTTAGSYSTEM_H


#include "../GUI/GUI.h"

enum TAGTYPES { DEFAULT_TAG, NEGATIVE_TAG, POSITIVE_TAG, EXPERIENCE_TAG, ENVIRONMETAL_TAG};

class TextTagSystem
{
private:
    class TextTag
    {
    private:
        sf::Text text;
        float dirY;
        float dirX;
        float lifetime;
        float speed;
        float acceleration;
        sf::Vector2f velocity;
        int fadeValue;
        bool reverse;

    public:
        TextTag(sf::Font& font, std::string text,
                float pos_x, float pos_y,
                float dir_x, float dir_y,
                sf::Color color,
                unsigned char_size,
                float lifetime, bool reverse, float speed,
                float acceleration, int fade_value)
        {
            this->text.setFont(font);
            this->text.setPosition(pos_x, pos_y);
            this->text.setFillColor(color);
            this->text.setCharacterSize(char_size);
            this->text.setString(text);

            dirX = dir_x;
            dirY = dir_y;
            this->lifetime = lifetime;
            this->speed = speed;
            this->acceleration = acceleration;
            fadeValue = fade_value;
            this->reverse	= reverse;

            if (this->reverse)
            {
                velocity.x = dirX * this->speed;
                velocity.y = dirY * this->speed;
            }
        }

        TextTag(TextTag* tag, float pos_x, float pos_y, std::string str)
        {
            text = tag->text;
            text.setString(str);
            text.setPosition(pos_x, pos_y);

            dirX = tag->dirX;
            dirY = tag->dirY;
            lifetime = tag->lifetime;
            speed = tag->speed;
            acceleration = tag->acceleration;
            fadeValue = tag->fadeValue;
            reverse = tag->reverse;
            velocity = tag->velocity;
        }

        ~TextTag()
        = default;

        //Accessor
        inline const bool isExpired() const{ return lifetime <= 0.f; }

        //Function
        void update(float dt)
        {
            if (lifetime > 0.f)
            {
                //Update the lifetime
                lifetime -= 100.f * dt;

                //Accelerate
                if (acceleration > 0.f)
                {
                    if (reverse)
                    {
                        velocity.x -= dirX * acceleration * dt;
                        velocity.y -= dirY * acceleration * dt;

                        if (std::abs(velocity.x) < 0.f)
                            velocity.x = 0.f;

                        if (std::abs(velocity.y) < 0.f)
                            velocity.y = 0.f;

                        text.move(velocity * dt);
                    }
                    else
                    {
                        velocity.x += dirX * acceleration * dt;
                        velocity.y += dirY * acceleration * dt;

                        if (std::abs(velocity.x) > speed)
                            velocity.x = dirX * speed;

                        if (std::abs(velocity.y) > speed)
                            velocity.y = dirY * speed;

                        text.move(velocity * dt);
                    }
                }
                else
                {
                    //Move the tag
                    text.move(dirX * speed * dt, dirY * speed * dt);
                }

                if (fadeValue > 0 && text.getFillColor().a >= fadeValue)
                {
                    text.setFillColor
                            (
                                    sf::Color(
                                            text.getFillColor().r,
                                            text.getFillColor().g,
                                            text.getFillColor().b,
                                            text.getFillColor().a - fadeValue
                                    )
                            );
                }
            }
        }

        void render(sf::RenderTarget& target)
        {
            target.draw(text);
        }
    };

    sf::Font font;
    std::map<unsigned, TextTag*> tagTemplates;
    std::vector<TextTag*> tags;

    //Private functions
    void initVariables();
    void initFonts(std::string font_file);
    void initTagTemplates();

public:
    TextTagSystem(std::string font_file);
    virtual ~TextTagSystem();

    //Functions
    void addTextTag(unsigned tag_type, float pos_x, float pos_y, std::string str, std::string prefix, std::string postfix);
    void addTextTag(unsigned tag_type, float pos_x, float pos_y, int i, std::string prefix, std::string postfix);
    void addTextTag(unsigned tag_type, float pos_x, float pos_y, float f, std::string prefix, std::string postfix);

    void update(float timeDelta);
    void render(sf::RenderTarget & target);
};


#endif //MAIN_CPP_TEXTTAGSYSTEM_H
