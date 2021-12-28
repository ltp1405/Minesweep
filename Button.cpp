#include "Button.hpp"

#include <iostream>
using namespace std;

bool InBound(sf::Vector2f pos, sf::Vector2f from, sf::Vector2f to) {
    if (pos.x > from.x && pos.y > from.y && pos.x < to.x && pos.y < to.y)
        return true;
    return false;
}

PushButton::PushButton() {
    mFontSize = 24;
    font.loadFromFile("./resource/FFFFORWA.TTF");
    text = "";

    mNormalTexture.loadFromFile("./resource/ingame-button-hover.png");
    mHoverTexture.loadFromFile("./resource/ingame-button.png");
    mSize = sf::Vector2f(mNormalTexture.getSize());
    mHoverColor = sf::Color::Green;
    mFillColor = sf::Color::Yellow;
    mTextColor = sf::Color::Black;
}

void PushButton::draw(sf::RenderWindow &window) {
    mSize = sf::Vector2f(mNormalTexture.getSize());
    sf::Sprite sprite;
    sprite.move(mPosition);
    if (hovered)
        sprite.setTexture(mHoverTexture);
    else
        sprite.setTexture(mNormalTexture);

    sf::Text txt;
    txt.setFont(font);
    txt.setString(text);
    txt.setCharacterSize(mFontSize);
    txt.setFillColor(mTextColor);
    sf::Vector2f pos = mPosition;
    sf::Vector2f textPos = pos + sf::Vector2f(mSize / 2.f);

    txt.setOrigin(text.length() / 2 * mFontSize * 0.8, mFontSize * 0.8);
    txt.setPosition(textPos);

    window.draw(sprite);
    window.draw(txt);
}

void PushButton::move(float x, float y) { mPosition = sf::Vector2f(x, y); }

void PushButton::setSize(float x, float y) { mSize = sf::Vector2f(x, y); }

void PushButton::handleEvent(sf::Event e) {
    sf::Vector2f to = mSize + mPosition;
    sf::Vector2f from = mPosition;

    switch (e.type) {
    case sf::Event::MouseMoved: {
        sf::Vector2f mousePos = sf::Vector2f(e.mouseMove.x, e.mouseMove.y);
        if (InBound(mousePos, from, to))
            hovered = true;
        else
            hovered = false;
        break;
    }

    case sf::Event::MouseButtonPressed: {
        sf::Vector2f mousePos = sf::Vector2f(e.mouseButton.x, e.mouseButton.y);
        if (InBound(mousePos, from, to))
            clicked = true;
        else
            clicked = false;
        break;
    }

    case sf::Event::MouseButtonReleased: {
        clicked = false;
    }
    }
}

void PushButton::setText(string txt) { text = txt; }

void PushButton::setFillColor(sf::Color color) { mFillColor = color; }

void PushButton::setHoverColor(sf::Color color) { mHoverColor = color; }

void PushButton::setTextColor(sf::Color color) { mTextColor = color; }
