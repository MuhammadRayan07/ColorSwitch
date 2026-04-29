#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

enum class Screen
{
    MainMenu,
    PlayMenu,
    CreatorsMenu,
    HighscoreMenu,
    AboutMenu
};
int main()
{
    const unsigned width = 800;
    const unsigned height = 900;

    sf::RenderWindow window(
        sf::VideoMode({ width,height }),
        "Color Switch"
    );

    window.setFramerateLimit(60);

    sf::Color backgroundColor(41, 41, 41);


    sf::Texture playTex;
    sf::Texture logoTex;
    sf::Texture starTex;
    sf::Texture plusTex;
    sf::Texture creatorsTex;
    sf::Texture highTex;
    sf::Texture aboutTex;
    sf::Texture Creators;
    sf::Texture Details;
    if (!Details.loadFromFile(
        "ColorSwitchSprites/Aboutmenu.png") ||

        !Creators.loadFromFile(
            "ColorSwitchSprites/Creatorsmenu.png") ||

        !playTex.loadFromFile(
            "ColorSwitchSprites/Play.png") ||

        !logoTex.loadFromFile(
            "ColorSwitchSprites/Colorswitch.png") ||

        !starTex.loadFromFile(
            "ColorSwitchSprites/Star.png") ||

        !plusTex.loadFromFile(
            "ColorSwitchSprites/Plus.png") ||

        !creatorsTex.loadFromFile(
            "ColorSwitchSprites/Creators.png") ||

        !highTex.loadFromFile(
            "ColorSwitchSprites/Highscore.png") ||

        !aboutTex.loadFromFile(
            "ColorSwitchSprites/About.png"))
    {
        std::cout << "Failed loading textures\n";
        return -1;
    }

   
    sf::Sprite logo(logoTex);
    sf::Sprite play(playTex);
    sf::Sprite star(starTex);
    sf::Sprite plus(plusTex);
    sf::Sprite plus2(plusTex);
    sf::Sprite creators(creatorsTex);
    sf::Sprite high(highTex);
    sf::Sprite about(aboutTex);
    sf::Sprite Creator(Creators);
    sf::Sprite det(Details);

    auto centerOrigin = [](sf::Sprite& s)
        {
            auto size = s.getTexture().getSize();
            s.setOrigin({
                size.x / 2.f,
                size.y / 2.f
                });
        };

    centerOrigin(logo);
    centerOrigin(play);
    centerOrigin(star);
    centerOrigin(plus);
    centerOrigin(plus2);
    centerOrigin(creators);
    centerOrigin(high);
    centerOrigin(about);
    centerOrigin(Creator);
    centerOrigin(det);
    

    logo.setScale({ 0.70f,0.70f });
    play.setScale({ 0.70f,0.70f });
    star.setScale({ 0.40f,0.40f });
    plus.setScale({ 0.60f,0.60f });
    plus2.setScale({ 0.60f,0.60f });
    creators.setScale({ 0.40f,0.40f });
    high.setScale({ 0.40f,0.40f });
    about.setScale({ 0.40f,0.40f });
    Creator.setScale({ 0.80f,0.80f });
    det.setScale({ 0.85f,0.85f });
   
    logo.setPosition({width / 2.f,150.f});
    Creator.setPosition({ width / 2.f, 450.f
        });
    det.setPosition({
        360.f,
        450.f
        });
    
    play.setPosition({
        width / 2.f,
        450.f
        });

    star.setPosition({
        width / 4.f,
        275.f
        });

    creators.setPosition({
        400.f,
        660.f
        });

    high.setPosition({
        405.f,
        740.f
        });

    about.setPosition({
        400.f,
        820.f
        });
    auto clickedSprite = [&](const sf::Sprite& s, sf::Vector2f mouse)
        {
            return s.getGlobalBounds().contains(mouse);
        };
 
    sf::Clock clock;

    sf::CircleShape leftBall(18.f);
    sf::CircleShape rightBall(18.f);

    leftBall.setOrigin({ 18.f,18.f });
    rightBall.setOrigin({ 18.f,18.f });


    leftBall.setFillColor(sf::Color(255, 0, 180));
    rightBall.setFillColor(sf::Color(0, 220, 255));


    float leftX = 180.f;
    float rightX = 630.f;

    float leftY = 450.f;
    float rightY = 450.f;

    float leftVelocity = -620.f;
    float rightVelocity = -620.f;

    const float g = 800.f;
    const float topLimit = 30.f;
    const float bottomLimit = 540.f;

    sf::Clock deltaClock;

    Screen currentScreen = Screen::MainMenu;
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (auto key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                {
                    if (currentScreen != Screen::MainMenu)
                        currentScreen = Screen::MainMenu;
                    else
                        window.close();
                }
            }

            if (auto mousePress =
                event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePress->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos(
                        (float)mousePress->position.x,
                        (float)mousePress->position.y
                    );

                    if (currentScreen == Screen::MainMenu)
                    {
                        if (clickedSprite(play, mousePos))
                            currentScreen = Screen::PlayMenu;

                        else if (clickedSprite(creators, mousePos))
                            currentScreen = Screen::CreatorsMenu;

                        else if (clickedSprite(high, mousePos))
                            currentScreen = Screen::HighscoreMenu;

                        else if (clickedSprite(about, mousePos))
                            currentScreen = Screen::AboutMenu;
                    }
                }
            }
        }
        float dt = deltaClock.restart().asSeconds();
        float t = clock.getElapsedTime().asSeconds();
        plus.setRotation(
            sf::degrees(t * 80.f)
        );
        plus2.setRotation(
            sf::degrees(t * 80.f)
        );
        leftVelocity += g * dt;
        leftY += leftVelocity * dt;

        if (leftY < topLimit)
        {
            leftY = topLimit;
            leftVelocity *= -1.f;
        }

        if (leftY > bottomLimit)
        {
            leftY = bottomLimit;
            leftVelocity = -620.f;
        }


        rightVelocity += g * dt;
        rightY += rightVelocity * dt;

        if (rightY < topLimit)
        {
            rightY = topLimit;
            rightVelocity *= -1.f;
        }

        if (rightY > bottomLimit)
        {
            rightY = bottomLimit;
            rightVelocity = -620.f;
        }

        leftBall.setPosition({ leftX,leftY });
        rightBall.setPosition({ rightX,rightY });
  
        star.setPosition({
            width / 2.f,
            275.f + sin(t * 2.f) * 10.f
            });

        window.clear(backgroundColor);

        if (currentScreen == Screen::MainMenu)
        {
            
            window.draw(logo);
            window.draw(star);
            window.draw(leftBall);
            window.draw(rightBall);
            window.draw(play);
            plus.setPosition({650.f,700.f});
            plus2.setPosition({150.f, 700.f});
            window.draw(plus);
            window.draw(plus2);
            window.draw(creators);
            window.draw(high);
            window.draw(about);
        }
        else
        {
            if (currentScreen == Screen::PlayMenu)
            {
                
            }

            if (currentScreen == Screen::CreatorsMenu)
            {
                window.draw(Creator);
                plus.setPosition({ 200.f, 80.f });
                plus2.setPosition({ 600.f, 80.f });
                star.setPosition({ 740.f,855.f });
                window.draw(star);
                window.draw(plus);
                window.draw(plus2);
            }

            if (currentScreen == Screen::HighscoreMenu)
            {
                // score table
            }

            if (currentScreen == Screen::AboutMenu)
            {
                window.draw(det);
                plus.setPosition({ 200.f, 80.f });
                plus2.setPosition({ 600.f, 80.f });

                window.draw(plus);
                window.draw(plus2);
            }
        }
        window.display();
    }
}