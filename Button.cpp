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
    mShape = sf::RectangleShape(sf::Vector2f(120.f, 50.f));
}

PushButton::PushButton(sf::Vector2f size, sf::Vector2f position) {
    mShape = sf::RectangleShape(size);
    mShape.setPosition(position);
}

void PushButton::draw(sf::RenderWindow &window) {
    if (hovered)
        mShape.setFillColor(sf::Color::Green);
    else
        mShape.setFillColor(sf::Color::Yellow);

    window.draw(mShape);
}

void PushButton::move(float x, float y) {
    mShape.setPosition(sf::Vector2f(x, y));
}

void PushButton::HandleEvent(sf::Event e) {
    sf::Vector2f to = mShape.getSize() + mShape.getPosition();
    sf::Vector2f from = mShape.getPosition();

    switch (e.type) {
        case sf::Event::MouseMoved: {
            sf::Vector2f mousePos = sf::Vector2f(e.mouseMove.x, e.mouseMove.y);
            if (InBound(mousePos, from, to))
                hovered = true;
            else hovered = false;
            break;
        }

        case sf::Event::MouseButtonPressed: {
            sf::Vector2f mousePos = sf::Vector2f(e.mouseButton.x, e.mouseButton.y);
            if (InBound(mousePos, from, to))
                clicked = true;
            else clicked = false;
            break;
        }
    }
}
