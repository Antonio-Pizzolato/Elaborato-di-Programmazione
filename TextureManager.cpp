#include "TextureManager.h"

std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> TextureManager::textures;
int TextureManager::currentId = 0;

// Default Constructor.
TextureManager::TextureManager()
= default;

// Adds a texture to the manager, and returns its id in the map.
int TextureManager::AddTexture(const std::string &filePath) {
    // First check if the texture has already been created. If so, simply return that one.
    auto it = textures.find(filePath);

    if (it != textures.end()) {
        return it->second.first;
    }

    // At this point the texture doesn't exists, so we'll create and add it.
    currentId++;

    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filePath)) {
        return -1;
    }

    textures.insert(std::make_pair(filePath, std::make_pair(currentId, std::move(texture))));

    // Return the texture.
    return currentId;
}

// Removes a texture from the manager from a given id.
void TextureManager::RemoveTexture(int textureID) {
    for (auto it = textures.begin(); it != textures.end(); ++it) {
        if (it->second.first == textureID) {
            textures.erase(it->first);
        }
    }
}

// Gets a texture from the texture manager from an ID.
sf::Texture &TextureManager::GetTexture(int textureID) {
    for (auto &m_texture: textures) {
        if (m_texture.second.first == textureID) {
            return *m_texture.second.second;
        }
    }

}