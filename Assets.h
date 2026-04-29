#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetManager
{
private:
    std::map<std::string, sf::Texture> textures;

public:
    void loadTexture(const std::string& name, const std::string& filename);
    sf::Texture& getTexture(const std::string& name);
};