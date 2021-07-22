
#include "SettingState.h"

void SettingState::initVariables() {

    this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingState::initBackground() {

    this->background.setSize
            (sf::Vector2f
                     (
                             static_cast<float>(this->window->getSize().x),
                             static_cast<float>(this->window->getSize().y)
                     )
            );

    if(!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.jpg")){
        throw "ERROR::SETTING_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);
}


void SettingState::initFonts() {
    if(!this->font.loadFromFile("Fonts/Dosis-Light.ttf")){
        throw("ERROR::SETTING_STATE::COULD NOT LOAD FONT");
    }
}

void SettingState::initKeybinds() {


    std::ifstream ifs("Config/mainmenustate_keybinds.ini");

    if(ifs.is_open()){
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2){
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();

}

void SettingState::initGUI() {

    this->buttons["BACK"] = new GUI::Button(1400.f, 880.f, 250.f, 65.f,
                                            &this->font, "Back",50,
                                            sf::Color(70, 70,70,200), sf::Color(250, 250, 250,250), sf::Color(20, 20, 20,50),
                                            sf::Color(70, 70,70,0), sf::Color(150, 150, 150,0), sf::Color(20, 20, 20,0));

    this->buttons["APPLY"] = new GUI::Button(1200.f, 880.f, 250.f, 65.f,
                                             &this->font, "Apply",50,
                                             sf::Color(70, 70,70,200), sf::Color(250, 250, 250,250), sf::Color(20, 20, 20,50),
                                             sf::Color(70, 70,70,0), sf::Color(150, 150, 150,0), sf::Color(20, 20, 20,0));

    std::vector<std::string> modes_str;

    for(auto &i : this->modes){
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }

    this->dropDownLists["RESOLUTION"] = new GUI::DropDownList(800, 450, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingState::initText() {

    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(sf::Vector2f(100.f, 450.f));
    this->optionsText.setCharacterSize(30);
    this->optionsText.setFillColor(sf::Color(255, 255, 255, 200 ));

    this->optionsText.setString(
            "Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n  "
    );
}


//Constructor
SettingState::SettingState(StateData* state_data)
        : State(state_data){

    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initGUI();
    this->initText();

}

SettingState::~SettingState() {

    auto it = this->buttons.begin();
    for(it = this->buttons.begin(); it != this->buttons.end(); ++it){
        delete it->second;
    }

    auto it2 = this->dropDownLists.begin();
    for(it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2){
        delete it2->second;
    }

}

//Accessors

//Functions
void SettingState::updateInput(const float &dt) {



}

void SettingState::updateGUI(const float &dt) {

    /*Updates all the GUI elements in the state and handles their functionality.*/
    //Buttons
    for(auto &it : this->buttons){
        it.second->update(this->mousePosWindow);
    }
    //Button functionality
    //Quit the game
    if(this->buttons["BACK"]->isPressed()){
        this->endState();
    }

    //Apply selected settings
    if(this->buttons["APPLY"]->isPressed()){

        //Test remove later
        this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
        this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
    }

    //DropDownList
    for(auto &it : this->dropDownLists){
        it.second->update(this->mousePosWindow, dt);
    }

    //DropDownList functionality


}

void SettingState::update(const float &dt) {

    this->updateMousePositions();
    this->updateInput(dt);
    this->updateGUI(dt);


}

void SettingState::renderGUI(sf::RenderTarget &target) {

    for(auto &it : this->buttons){
        it.second->render(target);
    }

    for(auto &it : this->dropDownLists){
        it.second->render(target);
    }
}

void SettingState::render(sf::RenderTarget* target) {

    if(!target)
        target = this->window;

    target->draw(this->background);

    this->renderGUI(*target);

    target->draw(this->optionsText);

    //REMOVE LATER
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());

    target->draw(mouseText);

}


