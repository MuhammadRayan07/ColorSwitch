#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "AnimatedBall.h"

enum class Screen
{
    MainMenu,
    PlayMenu,
    CreatorsMenu,
    HighscoreMenu,
    AboutMenu
};

class Menu
{
private:
    sf::Texture logoTex, playTex, starTex, plusTex;
    sf::Texture creatorsTex, highTex, aboutTex;
    sf::Texture creatorPageTex, detailsTex;
    std::optional<sf::Sprite> logo, play, star, plus, plus2;
    std::optional<sf::Sprite> creators, high, about;
    std::optional<sf::Sprite> creatorPage, details;

    AnimatedBall leftBall;
    AnimatedBall rightBall;

    Screen currentScreen;
    bool   wantsClose;

    bool clicked(const sf::Sprite& s, sf::Vector2f mouse) const;

    static void setupSprite(sf::Sprite& s, float scaleX, float scaleY,
        float posX, float posY);
public:
    Menu();

    void handleEvent(const sf::Event& event);
    void update(float dt, float t);
    void draw(sf::RenderWindow& window);

    bool shouldClose() const { return wantsClose; }


};