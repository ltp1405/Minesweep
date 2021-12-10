#include "Game.hpp"
#include <iostream>
using namespace std;

int main() {
    Game game;
    game.run();
}

Game::Game()
: mWindow(sf::RenderWindow(sf::VideoMode(900, 900), "Minesweeper", sf::Style::Close)) {
    font.loadFromFile("./resource/DejaVuSansMono.ttf");
    srand(time(0));
    board.Initialize(8, 8 , 10);
    board.x = 300;
    board.y = 210;
    easyStartBtn.move(100.f, 440.f);
    mediumStartBtn.move(100.f, 520.f);
    hardStartBtn.move(100.f, 600.f);
    currentScene = MENU;
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
    case MENU:
        while (mWindow.pollEvent(e)) {
            if(e.type == sf::Event::Closed)
                mWindow.close();
            else if (e.type == sf::Event::KeyPressed ||
                e.type == sf::Event::MouseButtonPressed) {
                currentScene = GAME;
                timer.restart();
            }
        }
        break;

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
                Reset();
            }
        }
        break;

    case GAMEWIN:
        while (mWindow.pollEvent(e)) {
            if(e.type == sf::Event::Closed)
                mWindow.close();
            else if (e.type == sf::Event::KeyPressed ||
                e.type == sf::Event::MouseButtonPressed) {
                currentScene = GAME;
                Reset();
            }
        }
        break;
    }
}

void Game::update() {
    if (easyStartBtn.clicked) {
        board.Initialize(8, 8, 1);
        currentDifficulty = EASY;
        timer.restart();
    } else if (mediumStartBtn.clicked) {
        board.Initialize(16, 16, 40);
        currentDifficulty = MEDIUM;
        timer.restart();
    } else if (hardStartBtn.clicked) {
        board.Initialize(24, 24, 100);
        currentDifficulty = HARD;
        timer.restart();
    }

    if (currentScene == GAME)
        currentTime = timer.getElapsedTime();

    if (board.state == LOSE)
        currentScene = GAMEOVER;
    if (board.state == WIN)
        currentScene = GAMEWIN;
}

void Game::render() {
    mWindow.clear(sf::Color::White);

    DrawGameTitle(mWindow);
    DrawGameStatus(mWindow, board.bombCount, board.flagCount, currentTime.asSeconds()); 
    board.Draw(mWindow);
    easyStartBtn.draw(mWindow);
    mediumStartBtn.draw(mWindow);
    hardStartBtn.draw(mWindow);
    if (currentScene == GAMEOVER)
        DrawGameoverMenu(mWindow);
    else if (currentScene == MENU)
        DrawStartMenu(mWindow);
    else if (currentScene == GAMEWIN)
        DrawWin(mWindow);

    mWindow.display();
}

void Game::Reset() {
    switch (currentDifficulty) {
    case EASY:
        board.Initialize(8, 8, 10);
        break;
    case MEDIUM:
        board.Initialize(16, 16, 40);
        break;
    case HARD:
        board.Initialize(24, 24, 100);
        break;
    }

    timer.restart();
}
