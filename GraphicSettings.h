//
// Created by Antonio on 22/07/2021.
//

#ifndef ELABORATO_DI_PROGRAMMAZIONE_GRAPHICSETTINGS_H
#define ELABORATO_DI_PROGRAMMAZIONE_GRAPHICSETTINGS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <stack>
#include <fstream>

class GraphicsSettings{

public:
    GraphicsSettings();

    //Variables
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    //Functions
    void saveToFile(const std::string path);
    void loadFromFile(const std::string path);
};

#endif //ELABORATO_DI_PROGRAMMAZIONE_GRAPHICSETTINGS_H
