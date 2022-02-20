//
// Created by Antonio on 18/02/2022.
//

#include "GUI.h"

//BUTTON

const float GUI::p2pX(const float perc, const sf::VideoMode& vm)
{
    //Converts a percentage value to pixels relative to the current resolution in the x-axis.
    return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float GUI::p2pY(const float perc, const sf::VideoMode& vm)
{
    //Converts a percentage value to pixels relative to the current resolution in the y-axis.
    return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const unsigned GUI::calcCharSize(const sf::VideoMode& vm, const unsigned modifier) {
    //Calculates the character size for text using the current resolution and a constant.
    return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

float GUI::p2pX(const float perc, sf::RenderWindow &window)
{
    //Converts a percentage value to pixels relative to the current resolution in the x-axis.
    return std::floor(static_cast<float>(window.getSize().x) * (perc / 100.f));
}

float GUI::p2pY(const float perc, sf::RenderWindow &window)
{
    //Converts a percentage value to pixels relative to the current resolution in the y-axis.
    return std::floor(static_cast<float>(window.getSize().y) * (perc / 100.f));
}

unsigned GUI::calcCharSize(sf::RenderWindow &window, const unsigned modifier) {
    //Calculates the character size for text using the current resolution and a constant.
    return static_cast<unsigned>((window.getSize().x + window.getSize().y) / modifier);
}


GUI::Button::Button(float x, float y, float width, float height, sf::Font *font, const std::string& text,
                    unsigned int character_size, sf::Color text_idle_color, sf::Color text_hover_color,
                    sf::Color text_active_color, sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
                    sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
                    short unsigned id) {

    buttonState = BTN_IDLE;
    this->id = id;

    shape.setPosition(sf::Vector2f(x,y));
    shape.setSize(sf::Vector2f(width,height));
    shape.setFillColor(idle_color);
    //this->shape.setOutlineThickness(5.f);
    //this->shape.setOutlineColor(outline_idle_color);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
            shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
            shape.getPosition().y
    );

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

GUI::Button::~Button() {

}

//Accessors
const bool GUI::Button::isPressed() const {

    if(buttonState == BTN_ACTIVE)
        return true;
    return false;
}

const std::string GUI::Button::getText() const {
    return text.getString();
}

const short unsigned &GUI::Button::getId() const {
    return id;
}


//Modifiers
void GUI::Button::setText(const std::string text) {
    this->text.setString(text);
}

void GUI::Button::setId(const short unsigned id) {
    this->id = id;
}


//Functions
void GUI::Button::updatePosition(sf::Vector2f position) {

    shape.setPosition(position);
    text.setPosition(
            shape.getPosition().x,
            shape.getPosition().y
    );
}

void GUI::Button::update(const sf::Vector2i& mousePosWindow) {
    /*Update the booleans for hover and pressed*/

    //Idle
    buttonState = BTN_IDLE;

    //Hover
    if(shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))){

        buttonState = BTN_HOVER;

        //Pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            buttonState = BTN_ACTIVE;
        }
    }

    switch (buttonState) {
        case BTN_IDLE:
            shape.setFillColor(idleColor);
            text.setFillColor(textIdleColor);
            shape.setOutlineColor(outlineIdleColor);
            break;
        case BTN_HOVER:
            shape.setFillColor(hoverColor);
            text.setFillColor(textHoverColor);
            shape.setOutlineColor(outlineHoverColor);
            break;
        case BTN_ACTIVE:
            shape.setFillColor(activeColor);
            text.setFillColor(textActiveColor);
            shape.setOutlineColor(outlineActiveColor);
            break;
        default:
            shape.setFillColor(sf::Color::Red);
            text.setFillColor(sf::Color::Blue);
            shape.setOutlineColor(sf::Color::Green);
            break;
    }
}


void GUI::Button::render(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);
}







//================================================================================================================

//DROP DOWN LIST

GUI::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index)
        : font(font), showList(false), keyTimeMax(1.f), keyTime(0.f)
{
    //unsigned nrOfElements = sizeof(list) / sizeof(std::string);
    activeElement = new GUI::Button(
            x, y, width, height,
            &this->font, list[default_index], 14,
            sf::Color(255, 255,255,150), sf::Color(255, 255, 255,200), sf::Color(20, 20, 20,50),
            sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
            sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));


    for(unsigned i = 0; i < nrOfElements; i++){
        this->list.push_back(
                new GUI::Button(
                        x, y + ((i+1) * height), width, height,
                        &this->font, list[i], 14,
                        sf::Color(255, 255,255,150), sf::Color(255, 255, 255,255), sf::Color(20, 20, 20,50),
                        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                        sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
                        i
                )
        );

    }




}

GUI::DropDownList::~DropDownList() {
    delete activeElement;
    for(size_t i = 0; i < list.size(); i++){

        delete list[i];
    }
}

//Accessors



const bool GUI::DropDownList::getKeyTime() {

    if(keyTime >= keyTimeMax){

        keyTime = 0.f;
        return true;
    }
    return false;
}

const unsigned short &GUI::DropDownList::getActiveElementId() const {
    return activeElement->getId();
}

//Functions
void GUI::DropDownList::updateKeyTime(const float& dt) {

    if(keyTime < keyTimeMax)
        keyTime += 10.f * dt;
}

void GUI::DropDownList::update(const sf::Vector2i &mousePosWindow, const float& dt) {

    updateKeyTime(dt);
    activeElement->update(mousePosWindow);

    //show and hide the list
    if(activeElement->isPressed() && getKeyTime()){

        if(showList)
            showList = false;
        else
            showList = true;
    }

    if(showList){
        for(auto &i : list){
            i->update(mousePosWindow);

            if(i->isPressed() && getKeyTime()){
                showList = false;
                activeElement->setText(i->getText());
                activeElement->setId(i->getId());
            }
        }
    }

}

void GUI::DropDownList::render(sf::RenderWindow &window) {

    activeElement->render(window);
    if(showList){
        for(auto &i : list){
            i->render(window);
        }
    }
}

//TEXTURE SELECTOR  ======================================================================================================

GUI::TextureSelector::TextureSelector(float x, float y, float width, float height,
                                      float gridSize, const sf::Texture *texture_sheet,
                                      sf::Font& font, std::string text)
        : keyTimeMax(1.f), keyTime(0.f){

    this->gridSize = gridSize;
    active = false;
    hidden = false;
    float offset = gridSize;

    bounds.setSize(sf::Vector2f(width, height));
    bounds.setPosition(x + offset, y);
    bounds.setFillColor(sf::Color(50, 50, 50, 100));
    bounds.setOutlineThickness(1.f);
    bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    sheet.setTexture(*texture_sheet);
    sheet.setPosition(x + offset, y);

    if(sheet.getGlobalBounds().width > bounds.getGlobalBounds().width){

        sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(bounds.getGlobalBounds().width), static_cast<int>(sheet.getGlobalBounds().height)));
    }
    if(sheet.getGlobalBounds().height > bounds.getGlobalBounds().height){
        sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(sheet.getGlobalBounds().width), static_cast<int>(bounds.getGlobalBounds().height)));
    }

    selector.setPosition(x + offset, y);
    selector.setSize(sf::Vector2f(gridSize, gridSize));
    selector.setFillColor(sf::Color::Transparent);
    selector.setOutlineThickness(1.f);
    selector.setOutlineColor(sf::Color::Red);

    textureRect.width = static_cast<int>(gridSize);
    textureRect.height = static_cast<int>(gridSize);

    hide_btn = new GUI::Button(x, y, 50.f, 50.f,
                                     &font, text, 16,
                                     sf::Color(255, 255,255,200), sf::Color(255, 255, 255,250), sf::Color(255, 255, 255,50),
                                     sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));


}

GUI::TextureSelector::~TextureSelector() {
    delete hide_btn;

}
//Accessors
const bool &GUI::TextureSelector::getActive() const {
    return active;
}

const sf::IntRect &GUI::TextureSelector::getTextureRect() const {
    return textureRect;
}

//Functions
const bool GUI::TextureSelector::getKeyTime() {

    if(keyTime >= keyTimeMax){

        keyTime = 0.f;
        return true;
    }
    return false;
}

void GUI::TextureSelector::updateKeyTime(const float &dt) {

    if(keyTime < keyTimeMax)
        keyTime += 10.f * dt;
}

void GUI::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt) {

    updateKeyTime(dt);

    hide_btn->update(mousePosWindow);

    if(hide_btn->isPressed() && getKeyTime()){
        if(hidden)
            hidden = false;
        else
            hidden = true;
    }

    if(!hidden)
    {
        active = false;

        if(bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
        {
            active = true;


            mousePosGrid.x = (mousePosWindow.x - static_cast<int>(bounds.getPosition().x)) / static_cast<unsigned>(gridSize);
            mousePosGrid.y = (mousePosWindow.y - static_cast<int>(bounds.getPosition().y)) / static_cast<unsigned>(gridSize);

            selector.setPosition(
                    bounds.getPosition().x + this->mousePosGrid.x * gridSize,
                    bounds.getPosition().y + this->mousePosGrid.y * gridSize
            );

            //Update texture rectangle
            textureRect.left = static_cast<int>(selector.getPosition().x - bounds.getPosition().x);
            textureRect.top = static_cast<int>(selector.getPosition().y - bounds.getPosition().y);
        }
    }
}

void GUI::TextureSelector::render(sf::RenderWindow &window) {



    if(!hidden){
        window.draw(bounds);
        window.draw(sheet);

        if(active)
            window.draw(selector);
    }

    hide_btn->render(window);

}

// PROGRESSBAR ============================================================================= PROGRESSBAR

GUI::ProgressBar::ProgressBar(float _x, float _y, float _width, float _height,
                              sf::Color inner_color, unsigned character_size,
                              sf::RenderWindow &window, sf::Font* font)
{
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

    if (font)
    {
        text.setFont(*font);
        text.setCharacterSize(GUI::calcCharSize(window, character_size));
        text.setPosition(
                inner.getPosition().x + GUI::p2pX(0.53f, window),
                inner.getPosition().y + GUI::p2pY(0.5f, window)
        );
    }
}

GUI::ProgressBar::~ProgressBar()
= default;

//Functions
void GUI::ProgressBar::update(const int current_value, const int max_value)
{
    float percent = static_cast<float>(current_value) / static_cast<float>(max_value);

    inner.setSize(
            sf::Vector2f(
                    static_cast<float>(std::floor(maxWidth * percent)),
                    inner.getSize().y
            )
    );

    barString = std::to_string(current_value) + " / " + std::to_string(max_value);
    text.setString(barString);
}

void GUI::ProgressBar::render(sf::RenderWindow &window)
{
    window.draw(back);
    window.draw(inner);
    window.draw(text);
}



// SLOT ============================================================================= SLOT

GUI::Slot::Slot(float x, float y, const sf::Texture& texture){

    buttonState = BTN_IDLE;

    shape.setPosition(sf::Vector2f(x,y));
    shape.setTexture(texture);

}

GUI::Slot::~Slot() = default;

//Accessors
bool GUI::Slot::isPressed() const {

    if(buttonState == BTN_ACTIVE)
        return true;
    return false;
}


//Modifiers


//Functions

void GUI::Slot::update(const sf::Vector2i& mousePosWindow) {
    /*Update the booleans for hover and pressed*/

    //Idle
    buttonState = BTN_IDLE;

    //Hover
    if(shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))){

        buttonState = BTN_HOVER;

        //Pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            buttonState = BTN_ACTIVE;
        }
    }

    switch (buttonState) {
        case BTN_IDLE:
            break;
        case BTN_HOVER:
            shape.setColor(sf::Color::Blue);
            break;
        case BTN_ACTIVE:
            shape.setColor(sf::Color::Red);
            break;
        default:
            break;
    }
}


void GUI::Slot::render(sf::RenderWindow &window) {
    window.draw(shape);
}
