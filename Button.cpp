#include "Button.hpp"

#include <iostream>
using namespace std;

PushButton::PushButton(sf::RenderWindow &window) {
    mShape = sf::RectangleShape(sf::Vector2f(120.f, 50.f));
    mWindow = &window;
}

void PushButton::draw() {
    if (clicked())
        mShape.setFillColor(sf::Color::Green);
    else
        mShape.setFillColor(sf::Color::Yellow);

    mWindow->draw(mShape);
}

bool PushButton::hovered() {
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*mWindow));
    sf::Vector2f bound = mShape.getSize() + mShape.getPosition();
    sf::Vector2f origin = mShape.getPosition();
    if (mousePos.x > origin.x && mousePos.y > origin.y &&
            mousePos.x < bound.x && mousePos.y < bound.y)
        return true;
    return false;
}

bool PushButton::clicked() {
    if (!hovered())
        return false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return true;
    else return false;
}

void PushButton::move(float x, float y) {
    mShape.setPosition(sf::Vector2f(x, y));
}
