#include "Menu.hpp"

Menu::Menu() {
    width = 300;
    height = 300;
}

Menu::~Menu() {
 }

void Menu::Draw(sf::RenderWindow &window) {
    sf::Vector2u winSize = window.getSize();

    sf::RectangleShape rect(sf::Vector2f((float)width, (float)height));
    rect.setOrigin(width / 2, height / 2);
    rect.setPosition((float)winSize.x / 2, (float)winSize.y / 2);
    rect.setFillColor(sf::Color::Green);

    window.draw(rect);
}
