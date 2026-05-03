#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedBall.h"
#include "Ball.h"
#include "Camera.h"
#include "Shape.h"
#include "CircleShapeObj.h"
#include "RectangleShapeObj.h"
#include "TriangleShapeObj.h"
#include "HorizontalLine.h"
#include "PlusShape.h"
#include "StarCollectible.h"
#include "GameUtils.h"
#include "Globals.h"
#include "Rotation.h"
#include "Collision.h"
#include"difficulty.h"
#include <SFML/Audio.hpp>
#include "ScoreManager.h"

enum class Screen
{
    MainMenu,
    PlayMenu,
    CreatorsMenu,
    HighscoreMenu,
    AboutMenu,
    GameScreen,
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
    ScoreManager scoreManager;
    float easySpeed = 90.f;
    float mediumSpeed = 160.f;
    float hardSpeed = 240.f;
    float currentTime = 0.f;
    bool isGameOver = false;
    bool ballHasLaunched = false;
    bool gameStarted = false;        
    bool gameOverMusicPlayed = false;

    // game members
    Ball* gameBall;
    Camera* gameCamera;
    Shape** shapes;
    int        shapeCount;
    int        shapeCapacity;
    float      lastSpawnY;
    float      rotationSpeed;
    float      gravity;
    float      jumpStrength;
    Difficulty currentDifficulty;

    sf::Texture logoTex, playTex, starTex, plusTex;
    sf::Texture creatorsTex, highTex, aboutTex;
    sf::Texture creatorPageTex, detailsTex;
    sf::Texture easyTex, mediumTex, hardTex;
    sf::Texture ringTex;
    sf::Texture highScoreMenuTex;
    sf::Texture gameOverTex, homeTex, continueTex;
    sf::Font    font;
    sf::Text* scoreText;
    sf::Text* highScoreText;

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
    sf::Sprite* highScoreMenu;
    sf::Sprite* bigRing;
    sf::Sprite* bigRing2;
    sf::Sprite* bigRing3;
    sf::Sprite* bigRing4;
    sf::Sprite* bigRing5;
    sf::Sprite* gameOver;
    sf::Sprite* homeBtn;
    sf::Sprite* continueBtn;

    AnimatedBall leftBall;
    AnimatedBall rightBall;
    AnimatedBall leftBall2;
    AnimatedBall rightBall2;

    sf::Music       homeMusic;
    sf::Music       gameOverMusic;
    sf::SoundBuffer bounceBuffer;
    sf::SoundBuffer buttonBuffer;
    sf::Sound* bounceSound;
    sf::Sound* buttonSound;

    Screen currentScreen;
    bool   wantsClose;

    void centerOrigin(sf::Sprite* s);
    bool clicked(sf::Sprite* s, sf::Vector2f mouse);
    void startGame(Difficulty diff);
    void cleanupGame();
};