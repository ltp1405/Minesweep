#include "Game.hpp"

int main() {
    Game game;
    game.run();
}

Game::Game()
: mWindow(sf::RenderWindow(sf::VideoMode(600, 400), "Minesweeper")) {
    font.loadFromFile("./DejaVuSansMono.ttf");
    srand(time(0));
    board.Initialize(8, 8 , 10);
    board.x = 300;
    board.y = 100;
    easyStartBtn.move(100.f, 100.f);
    mediumStartBtn.move(100.f, 200.f);
    hardStartBtn.move(100.f, 300.f);
    currentScene = GAME;
    currentDifficulty = EASY;
}

void Game::run() {
    while (mWindow.isOpen()) {
        handleEvent();
        update();
        render();
    }
}

void Game::handleEvent() {
    sf::Event e;
    switch (currentScene) {
    case GAME:
        while (mWindow.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                mWindow.close();
            board.HandleEvent(e);
            easyStartBtn.HandleEvent(e);
            mediumStartBtn.HandleEvent(e);
            hardStartBtn.HandleEvent(e);
        }
        break;
    case GAMEOVER:
        while (mWindow.pollEvent(e)) {
            if (e.type == sf::Event::KeyPressed ||
                e.type == sf::Event::MouseButtonPressed) {
                currentScene = GAME;
                board.Initialize(8, 8, 10);
            }
        }
        break;
    }
}

void Game::update() {
    if (easyStartBtn.clicked) {
        board.Initialize(8, 8, 10);
        currentDifficulty = EASY;
    } else if (mediumStartBtn.clicked) {
        board.Initialize(16, 16, 40);
        currentDifficulty = MEDIUM;
    } else if (hardStartBtn.clicked) {
        board.Initialize(24, 24, 100);
        currentDifficulty = HARD;
    }

    if (board.state == LOSE)
        currentScene = GAMEOVER;
    if (board.state == WIN)
        currentScene = MENU;
}


void Game::render() {
    mWindow.clear(sf::Color::White);

    board.Draw(mWindow);
    easyStartBtn.draw(mWindow);
    mediumStartBtn.draw(mWindow);
    hardStartBtn.draw(mWindow);

    mWindow.display();
}
