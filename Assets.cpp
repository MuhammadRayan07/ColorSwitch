#include "Assets.h"
#include <iostream>

void AssetManager::loadTexture(
    const std::string& name,
    const std::string& filename)
{
    sf::Texture tex;
    if (!tex.loadFromFile(filename))
    {
        std::cout << "Failed to load: " << filename << "\n";
        exit(-1);
    }
    textures[name] = std::move(tex);
}

sf::Texture& AssetManager::getTexture(const std::string& name)
{
    return textures.at(name);
}