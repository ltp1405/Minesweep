#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;


class PushButton {
public:
    PushButton();

    void draw(sf::RenderWindow &window);
    void move(sf::Vector2f pos);
    void move(float x, float y);
    void setSize(float x, float y);
    void setText(string text);
    void HandleEvent(sf::Event event);
    void setFillColor(sf::Color color);
    void setHoverColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setTextSize(int size);
    bool clicked = false;
    bool hovered = false;

private:
    string text;
    sf::Font font;
    int mFontSize;

    sf::RectangleShape mShape;
    sf::Texture mTexture;

    sf::Vector2f mPosition;
    sf::Vector2f mSize;

    sf::Color mFillColor;
    sf::Color mHoverColor;
    sf::Color mTextColor;
};
