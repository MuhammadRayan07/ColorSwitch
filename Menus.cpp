#include "Menus.h"
#include <iostream>
#include <cmath>
void Menu::setupSprite(sf::Sprite& s,
    float scaleX, float scaleY,
    float posX, float posY)
{
    auto size = s.getTexture().getSize();
    s.setOrigin({ size.x / 2.f, size.y / 2.f });
    s.setScale({ scaleX, scaleY });
    s.setPosition({ posX, posY });
}

Menu::Menu()
    : leftBall(180.f, sf::Color(255, 0, 180))
    , rightBall(630.f, sf::Color(0, 220, 255))
    , currentScreen(Screen::MainMenu)
    , wantsClose(false)
{
    if (!logoTex.loadFromFile("ColorSwitchSprites/Colorswitch.png") ||
        !playTex.loadFromFile("ColorSwitchSprites/Play.png") ||
        !starTex.loadFromFile("ColorSwitchSprites/Star.png") ||
        !plusTex.loadFromFile("ColorSwitchSprites/Plus.png") ||
        !creatorsTex.loadFromFile("ColorSwitchSprites/Creators.png") ||
        !highTex.loadFromFile("ColorSwitchSprites/Highscore.png") ||
        !aboutTex.loadFromFile("ColorSwitchSprites/About.png") ||
        !creatorPageTex.loadFromFile("ColorSwitchSprites/Creatorsmenu.png") ||
        !detailsTex.loadFromFile("ColorSwitchSprites/Aboutmenu.png"))
    {
        std::cout << "Failed loading textures\n";
    }
    logo.emplace(logoTex);
    play.emplace(playTex);
    star.emplace(starTex);
    plus.emplace(plusTex);
    plus2.emplace(plusTex);
    creators.emplace(creatorsTex);
    high.emplace(highTex);
    about.emplace(aboutTex);
    creatorPage.emplace(creatorPageTex);
    details.emplace(detailsTex);

    setupSprite(*logo, 0.70f, 0.70f, 400.f, 150.f);
    setupSprite(*play, 0.70f, 0.70f, 400.f, 450.f);
    setupSprite(*star, 0.40f, 0.40f, 400.f, 275.f);
    setupSprite(*plus, 0.60f, 0.60f, 650.f, 700.f);
    setupSprite(*plus2, 0.60f, 0.60f, 150.f, 700.f); 
    setupSprite(*creators, 0.40f, 0.40f, 400.f, 660.f);
    setupSprite(*high, 0.40f, 0.40f, 405.f, 740.f);
    setupSprite(*about, 0.40f, 0.40f, 400.f, 820.f);
    setupSprite(*creatorPage, 0.80f, 0.80f, 400.f, 450.f);
    setupSprite(*details, 0.85f, 0.85f, 360.f, 450.f);
}

bool Menu::clicked(const sf::Sprite& s, sf::Vector2f mouse) const
{
    return s.getGlobalBounds().contains(mouse);
}

void Menu::handleEvent(const sf::Event& event)
{
    if (auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->scancode == sf::Keyboard::Scancode::Escape)
        {
            if (currentScreen != Screen::MainMenu)
                currentScreen = Screen::MainMenu;
            else
                wantsClose = true;
        }
    }

    if (auto* mb = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mb->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f m(
                static_cast<float>(mb->position.x),
                static_cast<float>(mb->position.y)
            );

            if (currentScreen == Screen::MainMenu)
            {
                if (clicked(*play, m)) currentScreen = Screen::PlayMenu;
                else if (clicked(*creators, m)) currentScreen = Screen::CreatorsMenu;
                else if (clicked(*high, m)) currentScreen = Screen::HighscoreMenu;
                else if (clicked(*about, m)) currentScreen = Screen::AboutMenu;
            }
        }
    }
}

void Menu::update(float dt, float t)
{
    leftBall.update(dt);
    rightBall.update(dt);
    star->setPosition({ 400.f, 275.f + std::sin(t * 2.f) * 10.f });
    plus->setRotation(sf::degrees(t * 80.f));
    plus2->setRotation(sf::degrees(t * 80.f));
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
       //Modes
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