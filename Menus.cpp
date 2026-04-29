#include "Menus.h"
#include <iostream>
#include <cmath>

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

    logo->setPosition({ 400.f, 150.f });
    play->setPosition({ 400.f, 450.f });
    star->setPosition({ 400.f, 275.f });
    creators->setPosition({ 400.f, 660.f });
    high->setPosition({ 405.f, 740.f });
    about->setPosition({ 400.f, 820.f });
    creatorPage->setPosition({ 400.f, 450.f });
    details->setPosition({ 360.f, 450.f });
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
            sf::Vector2f mousePos(
                (float)mb->position.x,
                (float)mb->position.y
            );

            if (currentScreen == Screen::MainMenu)
            {
                if (clicked(play, mousePos)) currentScreen = Screen::PlayMenu;
                else if (clicked(creators, mousePos)) currentScreen = Screen::CreatorsMenu;
                else if (clicked(high, mousePos)) currentScreen = Screen::HighscoreMenu;
                else if (clicked(about, mousePos)) currentScreen = Screen::AboutMenu;
            }
        }
    }
}

void Menu::update(float dt, float t)
{
    leftBall.update(dt);
    rightBall.update(dt);

    star->setPosition({ 400.f, 275.f + sin(t * 2.f) * 10.f });

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
        //  level select
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
        // score table
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