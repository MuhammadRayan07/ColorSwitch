#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedBall.h"
#include "Game.h"
enum class Screen
{
    MainMenu,
    PlayMenu,
    CreatorsMenu,
    HighscoreMenu,
    AboutMenu,
    GameScreen
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
    float easySpeed = 90.f;
    float mediumSpeed = 160.f;
    float hardSpeed = 240.f;
    float currentTime;
    //Game.h members
    Ball* gameBall;
    Camera* gameCamera;
    Shape** shapes;
    int      shapeCount;
    int      shapeCapacity;
    int score = 0;
    float    lastSpawnY;
    float    gravity;
    float    jumpStrength;

    sf::Texture logoTex, playTex, starTex, plusTex;
    sf::Texture creatorsTex, highTex, aboutTex;
    sf::Texture creatorPageTex, detailsTex;
    sf::Texture easyTex, mediumTex, hardTex;
    sf::Texture ringTex;

    sf::Sprite* ring1;
    sf::Sprite* ring2;
    sf::Sprite* easyMenu;
    sf::Sprite* mediumMenu;
    sf::Sprite* hardMenu;
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
    AnimatedBall leftBall2;   
    AnimatedBall rightBall2;

    Screen currentScreen;
    bool   wantsClose;

    void   centerOrigin(sf::Sprite* s);
    bool   clicked(sf::Sprite* s, sf::Vector2f mouse);
    void startGame();
    void cleanupGame();
};