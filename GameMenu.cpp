#include "GameMenu.hpp"

Menu::Menu() {
    choice = 0;
    numberOfChoice = 0;
    size = sf::Vector2u(300, 50);
    position = sf::Vector2i(20, 20);
}

void Menu::addEntry(string name) {
    entries[numberOfChoice] = name;
    numberOfChoice++;
}


void Menu::handleEvent(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up :
                chooseNext();
                break;
            case sf::Keyboard::Down :
                choosePrev();
                break;
            case sf::Keyboard::Enter :
                choiceSelected = true;
        }
    }
}

void Menu::chooseNext() {
    if (choice > 0)
        choice--;
}

void Menu::choosePrev() {
    if (choice < numberOfChoice-1)
        choice++;
}


void Menu::draw(sf::RenderWindow &window) {
    sf::Vector2u winSize = window.getSize();
    for (int i = 0; i < numberOfChoice; ++i) {
        
        sf::RectangleShape rect(sf::Vector2f(size.x, size.y));
        rect.setOrigin(size.x / 2, 14);
        rect.setPosition((float)winSize.x / 2, 200 + (size.y+10)*i);
        sf::Font font;
        sf::Text text;
        font.loadFromFile("./resource/FFFFORWA.TTF");
        text.setFont(font);
        text.setString(entries[i]);
        text.setPosition((float)winSize.x / 2 - 40, 200 + (size.y+10)*i);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Yellow);
        if (i == choice) {
            rect.setFillColor(sf::Color::Green);
            text.setFillColor(sf::Color::White);
        } else {
            rect.setFillColor(sf::Color::Black);
            text.setFillColor(sf::Color::Yellow);
        }
        window.draw(rect);
        window.draw(text);
    }
}

/*
int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Menu", sf::Style::Close);
    Menu menu;
    
    while (window.isOpen()) {
        sf::Event event;
        window.clear(sf::Color(220, 10, 30));
        while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else {
                    menu.handleEvent(event);
                }
        }
        menu.draw(window);
        window.display();
    }
}
*/
