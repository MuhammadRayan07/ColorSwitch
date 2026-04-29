#pragma once
#include <SFML/Graphics.hpp>
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
public:
    Menu();
    ~Menu();

    void handleEvent(const sf::Event& event);
    void update(float dt, float t);
    void draw(sf::RenderWindow& window);

    bool shouldClose() const { return wantsClose; }

private:
    sf::Texture logoTex, playTex, starTex, plusTex;
    sf::Texture creatorsTex, highTex, aboutTex;
    sf::Texture creatorPageTex, detailsTex;
    sf::Sprite* logo;
    sf::Sprite* play;
    sf::Sprite* star;
    sf::Sprite* plus;
    sf::Sprite* plus2;
    sf::Sprite* creators;
    sf::Sprite* high;
    sf::Sprite* about;
    sf::Sprite* creatorPage;
    sf::Sprite* details;

    AnimatedBall leftBall;
    AnimatedBall rightBall;

    Screen currentScreen;
    bool   wantsClose;

    void   centerOrigin(sf::Sprite* s);
    bool   clicked(sf::Sprite* s, sf::Vector2f mouse);
};