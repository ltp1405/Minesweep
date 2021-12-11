#include "Button.hpp"

#include <iostream>
using namespace std;

bool InBound(sf::Vector2f pos, sf::Vector2f from, sf::Vector2f to) {
    if (pos.x > from.x && pos.y > from.y &&
            pos.x < to.x && pos.y < to.y)
        return true;
    return false;
}

PushButton::PushButton() {
    mSize = sf::Vector2f(150.f, 50.f);
    mFontSize = 18;
    font.loadFromFile("./resource/FFFFORWA.TTF");
    text = "";

    mHoverColor = sf::Color::Green;
    mFillColor = sf::Color::Yellow;
    mTextColor = sf::Color::Black;
}

void PushButton::draw(sf::RenderWindow &window) {
    sf::RectangleShape rect(mSize);
    rect.move(mPosition);
    if (hovered)
        rect.setFillColor(mHoverColor);
    else
        rect.setFillColor(mFillColor);

    sf::Text txt;
    txt.setFont(font);
    txt.setString(text);
    txt.setCharacterSize(mFontSize);
    txt.setFillColor(mTextColor);
    sf::Vector2f pos = mPosition;
    sf::Vector2f textPos = pos + sf::Vector2f(mSize/2.f);

    txt.setOrigin(text.length()/2 * mFontSize * 0.8, mFontSize*0.5);
    txt.setPosition(textPos);

    window.draw(rect);
    window.draw(txt);
}

void PushButton::move(float x, float y) {
    mPosition = sf::Vector2f(x, y);
}

void PushButton::setSize(float x, float y) {
    mSize = sf::Vector2f(x, y);
}

void PushButton::handleEvent(sf::Event e) {
    sf::Vector2f to = mSize + mPosition;
    sf::Vector2f from = mPosition;

    switch (e.type) {
        case sf::Event::MouseMoved:
        {
            sf::Vector2f mousePos = sf::Vector2f(e.mouseMove.x, e.mouseMove.y);
            if (InBound(mousePos, from, to))
                hovered = true;
            else hovered = false;
            break;
        }

        case sf::Event::MouseButtonPressed:
        {
            sf::Vector2f mousePos = sf::Vector2f(e.mouseButton.x, e.mouseButton.y);
            if (InBound(mousePos, from, to))
                clicked = true;
            else clicked = false;
            break;
        }

        case sf::Event::MouseButtonReleased:
        {
            clicked = false;
        }
    }
}

void PushButton::setText(string txt) {
    text = txt;
}

void PushButton::setFillColor(sf::Color color) {
    mFillColor = color;
}

void PushButton::setHoverColor(sf::Color color) {
    mHoverColor = color;
}

void PushButton::setTextColor(sf::Color color) {
    mTextColor = color;
}
