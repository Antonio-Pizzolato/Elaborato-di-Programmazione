#ifndef MAIN_CPP_TEXTUREMANAGER_H
#define MAIN_CPP_TEXTUREMANAGER_H


#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include "memory"
#include "cmath"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Util.h"

class TextureManager {
public:
    /**
     * Default constructor.
     */
    TextureManager();

    /**
     * Adds a texture to the manager and returns its id in the map.
     * @param The path to the image to load.
     * @return The id to the texture created, or the id in the map if it already exists.
     */
    static int AddTexture(const std::string &filePath);

    /**
     * Removes a texture from the manager from a given id.
     * @param textureID The id of the texture to be removed.
     */
    static void RemoveTexture(int textureID);

    /**
     * Gets a texture from the texture manager from an ID.
     * @param textureId The id of the texture to return.
     * @return A const reference to the texture.
    */
    static sf::Texture &GetTexture(int textureId);

private:
    /**
     * A map of each texture name with its ID.
     */
    static std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> textures;

    /**
     * The current key value.
     */
    static int currentId;
};


#endif //MAIN_CPP_TEXTUREMANAGER_H
