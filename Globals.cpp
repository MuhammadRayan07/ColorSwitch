#include "Globals.h"
#include <cstdlib>

sf::Color palette[4] = {
    sf::Color(50, 226, 241),
    sf::Color(255, 232, 15),
    sf::Color(140, 18, 251),
    sf::Color(255, 0, 128)
};

void getShuffledColors(sf::Color colors[4])
{
    for (int i = 0; i < 4; i++)
        colors[i] = palette[i];

    for (int i = 3; i > 0; i--)
    {
        int j = rand() % (i + 1);
        std::swap(colors[i], colors[j]);
    }
}