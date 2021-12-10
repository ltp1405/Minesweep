#include "GameMenu.hpp"
#include <iostream>
using namespace std;

Menu::Menu() {
    choice = 0;
    numberOfChoice = 4;
    size = sf::Vector2u(300, 50);
    position = sf::Vector2i(20, 20);
}

void Menu::HandleEvent(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up :
                ChooseNext();
                break;
            case sf::Keyboard::Down :
                ChoosePrev();
                break;
            case sf::Keyboard::Enter :
                choiceSelected = true;
        }
    }
}

void Menu::ChooseNext() {
    if (choice > 0)
        choice--;
}

void Menu::ChoosePrev() {
    if (choice < numberOfChoice-1)
        choice++;
}


void Menu::Draw(sf::RenderWindow &window) {
    sf::Vector2u winSize = window.getSize();
    for (int i = 0; i < numberOfChoice; ++i) {
        
        sf::RectangleShape rect(sf::Vector2f(size.x, size.y));
        rect.setOrigin(size.x / 2, 0);
        rect.setPosition((float)winSize.x / 2, 200 + (size.y+10)*i);
        if (i == choice)
            rect.setFillColor(sf::Color::Green);
        else rect.setFillColor(sf::Color::Black);
        window.draw(rect);
    }
}

/*
int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Menu", sf::Style::Close);
    Menu menu;
    
    while (window.isOpen()) {
        sf::Event event;
        window.clear(sf::Color::White);
        while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else {
                    menu.HandleEvent(event);
                }
        }
        menu.Draw(window);
        window.display();
    }
}
*/
