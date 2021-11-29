#pragma once
#include <SFML/Graphics.hpp>


class PushButton {
public:
    PushButton(sf::RenderWindow &window);

    void draw();
    void move(sf::Vector2f pos);
    void move(float x, float y);
    bool clicked();
    bool hovered();
private:
    sf::Vector2f mPosition;
    sf::RectangleShape mShape;
    sf::Texture mTexture;
    sf::RenderWindow *mWindow;
};
