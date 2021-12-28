#include "GameMenu.hpp"

Menu::Menu() {
    choice = 0;
    numberOfChoice = 0;
    size = sf::Vector2u(300, 50);
    position = sf::Vector2i(20, 20);
}

void Menu::addEntry(string name) {
    PushButton btn;
    entries[0].hovered = true;
    btn.setText(name);
    btn.setSize(size.x, size.y);
    entries[numberOfChoice] = btn;
    numberOfChoice++;
}

void Menu::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseMoved) {
        for (int i = 0; i < numberOfChoice; ++i)
            entries[i].handleEvent(event);
        for (int i = 0; i < numberOfChoice; ++i) {
            if (entries[i].hovered) {
                choice = i;
            }
        }
    } else if (event.type == sf::Event::MouseButtonPressed) {
        for (int i = 0; i < numberOfChoice; ++i)
            entries[i].handleEvent(event);
        for (int i = 0; i < numberOfChoice; ++i) {
            if (entries[i].clicked) {
                choice = i;
                choiceSelected = true;
            }
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            chooseNext();
            break;
        case sf::Keyboard::Down:
            choosePrev();
            break;
        case sf::Keyboard::Enter:
            choiceSelected = true;
            break;
        }
    }
}

void Menu::chooseNext() {
    if (choice > 0) {
        entries[choice].hovered = false;
        choice--;
        entries[choice].hovered = true;
    }
}

void Menu::choosePrev() {
    if (choice < numberOfChoice - 1) {
        entries[choice].hovered = false;
        choice++;
        entries[choice].hovered = true;
    }
}

void Menu::draw(sf::RenderWindow &window) {
    sf::Vector2u winSize = window.getSize();
    for (int i = 0; i < numberOfChoice; ++i) {
        entries[i].move(window.getSize().x / 2 - size.x / 2,
                        window.getSize().y / 2 - 200 + i * 120);
        entries[i].draw(window);
    }
}

void Menu::getChoiceFromMousePosition(sf::Vector2f mousePos,
                                      sf::Vector2f winSize) {}

/*
int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Menu", sf::Style::Close);
    Menu menu;
    menu.addEntry("HDJGNEGEDJGE");
    menu.addEntry("HDJGNEGEDJGE");
    menu.addEntry("HDJGNEGEDJGE");

    while (window.isOpen()) {
        sf::Event event;
        window.clear(sf::Color::White);
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
