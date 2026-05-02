#include "Menus.h"
#include"Rotation.h"
#include "Collision.h"
#include <iostream>
#include <cmath>
#include "Rotation.h"
#include "Collision.h"
#include <fstream>
bool spacePressed = false;
Menu::Menu()
    : leftBall(180.f, sf::Color(255, 0, 180))
    , rightBall(630.f, sf::Color(0, 220, 255))
    , leftBall2(80.f, sf::Color(255, 0, 0))
    , rightBall2(720.f, sf::Color(255, 255, 0))
    , currentScreen(Screen::MainMenu)
    , wantsClose(false)
    , gameBall(nullptr)
    , gameCamera(nullptr)
    , shapes(nullptr)
    , shapeCount(0)
    , shapeCapacity(0)
    , lastSpawnY(0.f)
    , gravity(0.f)
    , jumpStrength(0.f)
{
    loadHighScore();
    if (!logoTex.loadFromFile("ColorSwitchSprites/Colorswitch.png") ||
        !playTex.loadFromFile("ColorSwitchSprites/Play.png") ||
        !starTex.loadFromFile("ColorSwitchSprites/Star.png") ||
        !plusTex.loadFromFile("ColorSwitchSprites/Plus.png") ||
        !creatorsTex.loadFromFile("ColorSwitchSprites/Creators.png") ||
        !highTex.loadFromFile("ColorSwitchSprites/Highscore.png") ||
        !aboutTex.loadFromFile("ColorSwitchSprites/About.png") ||
        !creatorPageTex.loadFromFile("ColorSwitchSprites/Creatorsmenu.png") ||
        !detailsTex.loadFromFile("ColorSwitchSprites/Aboutmenu.png") ||
        !easyTex.loadFromFile("ColorSwitchSprites/Easymenu.png") ||
        !mediumTex.loadFromFile("ColorSwitchSprites/Mediummenu.png") ||
        !hardTex.loadFromFile("ColorSwitchSprites/Hardmenu.png")||
        !ringTex.loadFromFile("ColorSwitchSprites/Ring.png")||
        !highScoreMenuTex.loadFromFile("ColorSwitchSprites/Hs.png"))
    {
        std::cout << "Failed loading textures\n";
    }
    if (!font.openFromFile("ColorSwitchSprites/arial.ttf"))
    {
        std::cout << "Font not loaded\n";
    }

    scoreText = new sf::Text(font);
    highScoreText = new sf::Text(font);

    scoreText->setFont(font);
    scoreText->setCharacterSize(30);
    scoreText->setFillColor(sf::Color::White);
    scoreText->setPosition({ 10.f, 10.f });

    highScoreText->setFont(font);
    highScoreText->setCharacterSize(150);
    highScoreText->setFillColor(sf::Color::Magenta);
    highScoreText->setPosition({ 360.f, 490.f }); // adjust for menu
    logo = new sf::Sprite(logoTex);
    play = new sf::Sprite(playTex);
    star = new sf::Sprite(starTex);
    plus = new sf::Sprite(plusTex);
    plus2 = new sf::Sprite(plusTex);
    creators = new sf::Sprite(creatorsTex);
    high = new sf::Sprite(highTex);
    about = new sf::Sprite(aboutTex);
    creatorPage = new sf::Sprite(creatorPageTex);
    details = new sf::Sprite(detailsTex);
    easyMenu = new sf::Sprite(easyTex);
    mediumMenu = new sf::Sprite(mediumTex);
    hardMenu = new sf::Sprite(hardTex);
    ring1 = new sf::Sprite(ringTex);
    ring2 = new sf::Sprite(ringTex);
    highScoreMenu = new sf::Sprite(highScoreMenuTex);
    bigRing = new sf::Sprite(ringTex);   
    bigRing2 = new sf::Sprite(ringTex);
    bigRing3 = new sf::Sprite(ringTex);
    bigRing4 = new sf::Sprite(ringTex);
    bigRing5 = new sf::Sprite(ringTex);
    centerOrigin(highScoreMenu);
    centerOrigin(bigRing);
    centerOrigin(bigRing2);
    centerOrigin(bigRing3);
    centerOrigin(bigRing4);
    centerOrigin(bigRing5);

    centerOrigin(ring1);
    centerOrigin(ring2);
    centerOrigin(logo);
    centerOrigin(play);
    centerOrigin(star);
    centerOrigin(plus);
    centerOrigin(plus2);
    centerOrigin(creators);
    centerOrigin(high);
    centerOrigin(about);
    centerOrigin(creatorPage);
    centerOrigin(details);
    centerOrigin(easyMenu);
    centerOrigin(mediumMenu);
    centerOrigin(hardMenu);

    logo->setScale({ 0.70f, 0.70f });
    play->setScale({ 0.70f, 0.70f });
    star->setScale({ 0.40f, 0.40f });
    plus->setScale({ 0.60f, 0.60f });
    plus2->setScale({ 0.60f, 0.60f });
    creators->setScale({ 0.40f, 0.40f });
    high->setScale({ 0.40f, 0.40f });
    about->setScale({ 0.40f, 0.40f });
    creatorPage->setScale({ 0.80f, 0.80f });
    details->setScale({ 0.85f, 0.85f });
    easyMenu->setScale({ 0.63f, 0.63f });
    mediumMenu->setScale({ 0.62f, 0.62f });
    hardMenu->setScale({ 0.60f, 0.60f });
    ring1->setScale({ 0.15f, 0.15f });
    ring2->setScale({ 0.15f, 0.15f });
    highScoreMenu->setScale({ 0.6f, 0.6f });
    bigRing->setScale({ 0.98f, 0.98f }); 
    bigRing2->setScale({ 0.7f, 0.7f }); 
    bigRing3->setScale({ 0.7f, 0.7f }); 
    bigRing4->setScale({ 0.7f, 0.7f }); 
    bigRing5->setScale({ 0.7f, 0.7f });

    logo->setPosition({ 400.f, 150.f });
    play->setPosition({ 400.f, 450.f });
    star->setPosition({ 400.f, 275.f });
    creators->setPosition({ 400.f, 660.f });
    high->setPosition({ 405.f, 740.f });
    about->setPosition({ 400.f, 820.f });
    creatorPage->setPosition({ 400.f, 450.f });
    details->setPosition({ 360.f, 450.f });
    easyMenu->setPosition({ 400.f, 400.f });
    mediumMenu->setPosition({ 390.f, 580.f });
    hardMenu->setPosition({ 400.f, 760.f });
    highScoreMenu->setPosition({ 400.f, 190.f });
    bigRing->setPosition({ 400.f, 575.f });   
    bigRing2->setPosition({ -50.0f, 457.f });
    bigRing3->setPosition({ 830.f, 429.f });
    bigRing4->setPosition({ 60.f, 905.f });
    bigRing5->setPosition({ 738.f, 880.f });
}
//filehandling
void Menu::loadHighScore() 
{
    std::ifstream file("highscore.txt");

    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
    else
    {
        highScore = 0; // first time run
    }
}

void Menu::saveHighScore()
{
    std::ofstream file("highscore.txt");

    if (file.is_open())
    {
        file << highScore;
        file.close();
    }
}

Menu::~Menu()
{
    delete logo;
    delete play;
    delete star;
    delete plus;
    delete plus2;
    delete creators;
    delete high;
    delete about;
    delete creatorPage;
    delete details;
    delete easyMenu;
    delete mediumMenu;
    delete hardMenu;
    delete ring1;
    delete ring2;
    delete highScoreMenu;
    delete bigRing;
    delete bigRing2;
    delete bigRing3;
    delete bigRing4;
    delete bigRing5;
    delete scoreText;
    delete highScoreText;
    cleanupGame();
}
void Menu::startGame()
{
    score = 0;
    cleanupGame();

    const int width = 800;
    const int height = 900;
    const float groundY = 880.f;
    const float gap = 700.f;
    const float centerX = width / 2.f;
    const float baseY = 100.f;

    gravity = 0.5f;
    jumpStrength = -10.f;

    gameBall = new Ball(10.f, centerX, groundY);
    gameCamera = new Camera((float)width, (float)height);
    shapeCapacity = 10;
    shapeCount = 0;
    shapes = new Shape * [shapeCapacity];
    lastSpawnY = baseY;

    for (int i = 0; i < 5; i++)
    {
        spawnShape(shapes, shapeCount, shapeCapacity, centerX, lastSpawnY, width);
        lastSpawnY -= gap;
    }
}
void Menu::cleanupGame()
{
    if (shapes != nullptr)
    {
        for (int i = 0; i < shapeCount; i++)
            delete shapes[i];
        delete[] shapes;
        shapes = nullptr;
    }

    if (gameBall != nullptr)
    {
        delete gameBall;
        gameBall = nullptr;
    }

    if (gameCamera != nullptr)
    {
        delete gameCamera;
        gameCamera = nullptr;
    }

    shapeCount = 0;
    shapeCapacity = 0;
}
void Menu::centerOrigin(sf::Sprite* s)
{
    auto size = s->getTexture().getSize();
    s->setOrigin({ size.x / 2.f, size.y / 2.f });
}

bool Menu::clicked(sf::Sprite* s, sf::Vector2f mouse)
{
    return s->getGlobalBounds().contains(mouse);
}

void Menu::handleEvent(const sf::Event& event)
{
    // KEY PRESSED
    if (auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->scancode == sf::Keyboard::Scancode::Escape)
        {
            if (currentScreen != Screen::MainMenu)
                currentScreen = Screen::MainMenu;
            else
                wantsClose = true;
        }

        if (key->scancode == sf::Keyboard::Scancode::Space)
            if (currentScreen == Screen::GameScreen && gameBall)
                gameBall->setVelocityY(jumpStrength);
    }

    // KEY RELEASED
    if (auto* key = event.getIf<sf::Event::KeyReleased>())
    {
        if (key->scancode == sf::Keyboard::Scancode::Space)
        {
            spacePressed = false;
        }
    }

    // MOUSE
    if (auto* mb = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mb->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mousePos(
                (float)mb->position.x,
                (float)mb->position.y
            );

            if (currentScreen == Screen::MainMenu)
            {
                if (clicked(play, mousePos))
                    currentScreen = Screen::PlayMenu;
                else if (clicked(creators, mousePos))
                    currentScreen = Screen::CreatorsMenu;
                else if (clicked(high, mousePos))
                    currentScreen = Screen::HighscoreMenu;
                else if (clicked(about, mousePos))
                    currentScreen = Screen::AboutMenu;
            }
            else if (currentScreen == Screen::PlayMenu)
            {
                if (clicked(easyMenu, mousePos) ||
                    clicked(mediumMenu, mousePos) ||
                    clicked(hardMenu, mousePos))
                {
                    startGame();
                    currentScreen = Screen::GameScreen;
                }
            }
        }
    }
}
void Menu::update(float dt, float t)
{
    currentTime = t;

    leftBall.update(dt);
    rightBall.update(dt);
    leftBall2.update(dt);
    rightBall2.update(dt);

    star->setPosition({ 400.f, 275.f + sin(t * 2.f) * 10.f });

    plus->setRotation(sf::degrees(t * 80.f));
    plus2->setRotation(sf::degrees(t * 80.f));

    ring1->setRotation(sf::degrees(t * easySpeed));
    ring2->setRotation(sf::degrees(-(t * easySpeed)));
    if (currentScreen == Screen::GameScreen && gameBall && gameCamera)
    {
        const int width = 800;
        const int height = 900;
        const float gap = 700.f;

        applyGravity(*gameBall, gravity);
        moveBall(*gameBall);
        resetBallOnGround(*gameBall, 880.f);
        updateCamera(*gameCamera, *gameBall, width, height);
        rotateAllShapes(shapes, shapeCount, 1.0f);

        if (checkStarCollection(*gameBall, shapes, shapeCount))
        {
            score++;

            if (score > highScore)
            {
                highScore = score;
                saveHighScore();
            }

            std::cout << "Score: " << score << "\n";
        }

        

        checkShapePassCollision(*gameBall, shapes, shapeCount);

        if (checkWrongColorCollision(*gameBall, shapes, shapeCount))
        {
            if (score > highScore)
            {
                highScore = score;
                saveHighScore();
            }
            currentScreen = Screen::MainMenu;
        }

        if (gameBall->getPosition().y < lastSpawnY + gap)
        {
            spawnShape(shapes, shapeCount, shapeCapacity,
                width / 2.f, lastSpawnY, width);

            lastSpawnY -= gap;
        }
    }
}
void Menu::draw(sf::RenderWindow& window)
{
    if (currentScreen == Screen::MainMenu)
    {
        window.draw(*logo);
        window.draw(*star);
        leftBall.draw(window);
        rightBall.draw(window);
        window.draw(*play);

        plus->setPosition({ 650.f, 700.f });
        plus2->setPosition({ 150.f, 700.f });
        window.draw(*plus);
        window.draw(*plus2);

        window.draw(*creators);
        window.draw(*high);
        window.draw(*about);
    }
    else if (currentScreen == Screen::PlayMenu)
    {
        window.draw(*logo);

        plus->setPosition({ 180.f, 125.f });
        plus2->setPosition({ 620.f, 125.f });
        leftBall2.draw(window);
        rightBall2.draw(window);
        window.draw(*plus);
        window.draw(*plus2);
        window.draw(*star);

        window.draw(*easyMenu);
        ring1->setPosition({ 250.f,382.f });   // left ring inside easy button
        ring2->setPosition({ 553.f, 382.f });   // right ring inside easy button
        ring1->setRotation(sf::degrees(currentTime * easySpeed));
        ring2->setRotation(sf::degrees(-(currentTime * easySpeed)));
        window.draw(*ring1);
        window.draw(*ring2);
        window.draw(*mediumMenu);
        ring1->setPosition({ 250.f, 555.f });
        ring2->setPosition({ 553.f, 555.f });
        ring1->setRotation(sf::degrees(currentTime * mediumSpeed));
        ring2->setRotation(sf::degrees(-(currentTime * mediumSpeed)));
        window.draw(*ring1);
        window.draw(*ring2);
        window.draw(*hardMenu);
        ring1->setPosition({ 250.f, 733.f });
        ring2->setPosition({ 555.f, 733.f });
        ring1->setRotation(sf::degrees(currentTime * hardSpeed));
        ring2->setRotation(sf::degrees(-(currentTime * hardSpeed)));
        window.draw(*ring1);
        window.draw(*ring2);
    }
    else if (currentScreen == Screen::GameScreen)
    {
        // 🎮 Game world (camera view)
        window.setView(gameCamera->getView());

        for (int i = 0; i < shapeCount; i++)
            shapes[i]->draw(window);
        }

        gameBall->draw(window);

        // 🧾 UI (fixed screen view)
        window.setView(window.getDefaultView());

        window.draw(*scoreText);   // ✅ ADD HERE
    }
   
    else if (currentScreen == Screen::CreatorsMenu)
    {
        window.draw(*creatorPage);

        plus->setPosition({ 200.f, 80.f });
        plus2->setPosition({ 600.f, 80.f });
        window.draw(*plus);
        window.draw(*plus2);

        star->setPosition({ 740.f, 855.f });
        window.draw(*star);
    }
    else if (currentScreen == Screen::HighscoreMenu)
    {
        window.draw(*highScoreMenu);
        plus->setPosition({ 160.f, 120.f });
        plus2->setPosition({ 640.f, 120.f });
        window.draw(*plus);
        window.draw(*plus2);
        window.draw(*bigRing);
        window.draw(*bigRing2);
        window.draw(*bigRing3);
        window.draw(*bigRing4);
        window.draw(*bigRing5);

        window.draw(*highScoreText);
    }
    else if (currentScreen == Screen::AboutMenu)
    {
        window.draw(*details);

        plus->setPosition({ 200.f, 80.f });
        plus2->setPosition({ 600.f, 80.f });
        window.draw(*plus);
        window.draw(*plus2);
    }
}