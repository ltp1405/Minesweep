#pragma once
#include <SFML/Graphics.hpp>


class PushButton {
public:
    PushButton();
    PushButton(sf::Vector2f size, sf::Vector2f position);

    void draw(sf::RenderWindow &window);
    void move(sf::Vector2f pos);
    void move(float x, float y);
    void HandleEvent(sf::Event event);
    bool clicked = false;
    bool hovered = false;
private:
    sf::RectangleShape mShape;
    sf::Texture mTexture;
};
