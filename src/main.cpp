#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Board.hpp"
#include "Menu.hpp"
#include <iostream>
using namespace std;

enum Scene { MENU, GAME, GAMEOVER };
sf::Font FONT;

void PrintBoard(BoardCell **a, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            BoardCell cell = a[i][j];
            switch (a[i][j].type) {
                case BOMB:
                    cout << "B ";
                    break;
                case NORMAL:
                    cout << cell.normalCell.nearbyBombs << " ";
                    break;
            }
        }
        cout << endl;
    }
}

void DrawGameoverMenu(sf::RenderWindow&);

int main() {
    int windowType = 0;
    FONT.loadFromFile("./DejaVuSansMono.ttf");
    // windowType = 0: Menu
    // windowType = 1: Game
    srand(time(0));

    Board board(15, 15, 20);

    Menu menu;

    sf::RenderWindow window(sf::VideoMode(board.width*32, board.height*32), "Minesweeper", sf::Style::Close);

    Scene currentScene = MENU;
    while (window.isOpen()) {
        window.clear(sf::Color::White);
        switch (currentScene) {
        case (MENU):
            sf::Event e;
            
            while (window.pollEvent(e)) {
                if (e.type == sf::Event::KeyPressed
                    || e.type == sf::Event::MouseButtonPressed) {
                    currentScene = GAME;
                    board.Initialize();
                }
            }

            menu.Draw(window);
            break;

        case (GAME):
            {
                if (board.state == LOSE)
                    currentScene = GAMEOVER;
                if (board.state == WIN)
                    currentScene = MENU;

                sf::Vector2i pos = sf::Mouse::getPosition(window);

                while (window.pollEvent(e)) {
                    if (e.type == sf::Event::Closed)
                        window.close();

                    if (e.type == sf::Event::MouseButtonPressed) {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            board.Choose(pos.x, pos.y);
                        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                            board.ToggleFlag(pos.x, pos.y);
                    }

                }

                board.Draw(window);
                break;
            }

        case (GAMEOVER):
            while (window.pollEvent(e)) {
                if (e.type == sf::Event::KeyPressed
                    || e.type == sf::Event::MouseButtonPressed) {
                    currentScene = GAME;
                    board.Initialize();
                }
            }

            board.Draw(window);
            DrawGameoverMenu(window);
            break;
        }
        window.display();
    }
}

void DrawGameoverMenu(sf::RenderWindow &window) {
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

    text.setFont(FONT);
    text.setString("GAME OVER!");
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::Black);
    text.setPosition((float)windowSize.x / 2 - 100, (float)windowSize.y / 2 - 100);

    window.draw(rect);
    window.draw(text);
}
