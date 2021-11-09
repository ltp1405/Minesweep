#pragma once

#include <string>
#include <SFML/Graphics.hpp>

struct Button
{
    int x, y, width, height;
    bool hovered;

    void Draw();
};

class Menu {
public:
    int width;
    int height;

    Menu();
    ~Menu();
    void Draw(sf::RenderWindow &window);
};
