#include "Menu.hpp"
#include <iostream>

Menu::Menu() {
    width = 300;
    height = 300;
}

Menu::~Menu() {
 }

void Menu::draw(sf::RenderWindow &window) {
    sf::Vector2u winSize = window.getSize();
    sf::Font font;
    font.loadFromFile("./resource/DejaVuSansMono.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Welcome to the Minesweeper");
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::Black);
    text.setPosition((float)winSize.x / 2 - 100, 200);


    sf::RectangleShape rect(sf::Vector2f((float)width, (float)height));
    rect.setOrigin(width / 2, height / 2);
    rect.setPosition((float)winSize.x / 2, (float)winSize.y / 2);
    rect.setFillColor(sf::Color::Green);

    window.draw(rect);
    window.draw(text);
}


void DrawGameoverMenu(sf::RenderWindow &window) {
    sf::Font font;
    font.loadFromFile("./resource/FFFFORWA.TTF");
    sf::Vector2u windowSize = window.getSize();
    sf::Text text;
    sf::Color bgColor(66, 99, 245, 220);
    sf::Vector2f rectSize(400.f, 350.f);
    sf::RectangleShape rect(rectSize);
    rect.setFillColor(bgColor);
    rect.setOutlineColor(sf::Color(0,71,71));
    rect.setOutlineThickness(10);
    rect.setOrigin(rectSize / 2.f);
    rect.setPosition((float)windowSize.x / 2, (float)windowSize.y / 2);

    text.setFont(font);
    text.setString("GAME OVER!");
    text.setCharacterSize(42);
    text.setFillColor(sf::Color::Black);
    text.setPosition((float)windowSize.x / 2 - 160, (float)windowSize.y / 2 - 100);

    window.draw(rect);
    window.draw(text);
}

void DrawGameTitle(sf::RenderWindow &window) {
    sf::Font font;
    font.loadFromFile("./resource/FFFFORWA.TTF");
    sf::Vector2u windowSize = window.getSize();
    sf::Text text;
    sf::Color bgColor(66, 99, 245, 220);

    text.setFont(font);
    text.setString("MINESWEEPER");
    text.setCharacterSize(64);
    text.setFillColor(sf::Color(245, 141, 66));
    text.setPosition(140.f, 50.f);

    window.draw(text);
}

void DrawGameStatus(sf::RenderWindow &window, int bombCount, int flagCount, float timer) {
    sf::Font font;
    font.loadFromFile("./resource/FFFFORWA.TTF");
    sf::Vector2u windowSize = window.getSize();
    sf::Text text;

    text.setFont(font);

    int mins = (int)timer / 60;
    int snds = timer - mins*60;
    char timeString[10];
    sprintf(timeString, "%02d-%02d", mins, snds);
    
    text.setString(timeString);
    text.setCharacterSize(32);
    text.setFillColor(sf::Color(0, 0, 0));
    text.setPosition(60.f, 250.f);

    window.draw(text);
}

void DrawStartMenu(sf::RenderWindow &window) {
    int w = 420;
    int h = 420;
    sf::Vector2u winSize = window.getSize();
    sf::Font font;
    font.loadFromFile("./resource/FFFFORWA.TTF");
    sf::Text text;
    text.setFont(font);
    text.setString("WELCOME");
    text.setCharacterSize(42);
    text.setFillColor(sf::Color::Black);
    text.setPosition((float)winSize.x / 2 - 120, 400);


    sf::RectangleShape rect(sf::Vector2f((float)w, (float)h));
    rect.setOutlineColor(sf::Color(0,71,71));
    rect.setOutlineThickness(10);
    rect.setOrigin(w / 2, h / 2);
    rect.setPosition((float)winSize.x / 2, (float)winSize.y / 2);
    rect.setFillColor(sf::Color(235, 134, 52, 220));

    window.draw(rect);
    window.draw(text);
}

void DrawWin(sf::RenderWindow &window) {
    sf::Font font;
    font.loadFromFile("./resource/FFFFORWA.TTF");
    sf::Vector2u windowSize = window.getSize();
    sf::Text text;
    sf::Color bgColor(66, 99, 245, 220);
    sf::Vector2f rectSize(400.f, 350.f);
    sf::RectangleShape rect(rectSize);
    rect.setFillColor(bgColor);
    rect.setOutlineColor(sf::Color(0,71,71));
    rect.setOutlineThickness(10);
    rect.setOrigin(rectSize / 2.f);
    rect.setPosition((float)windowSize.x / 2, (float)windowSize.y / 2);

    text.setFont(font);
    text.setString("YOU WIN!");
    text.setCharacterSize(42);
    text.setFillColor(sf::Color::Black);
    text.setPosition((float)windowSize.x / 2 - 160, (float)windowSize.y / 2 - 100);

    window.draw(rect);
    window.draw(text);
}
