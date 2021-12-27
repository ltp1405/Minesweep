#include "Game.hpp"
#include "GameMenu.hpp"
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    Game game;
    game.Run();

    return 0;
}

Game::Game() {
    mWindow.create(sf::VideoMode(1152, 896), "Minesweeper", sf::Style::Close);
    font.loadFromFile("./resource/DejaVuSansMono.ttf");
    srand(time(0));
    board.x = 416;
    board.y = 160;
    easyStartBtn.move(100.f, 440.f);
    mediumStartBtn.move(100.f, 520.f);
    hardStartBtn.move(100.f, 600.f);
    easyStartBtn.setText("Easy");
    mediumStartBtn.setText("Medium");
    hardStartBtn.setText("Hard");
    currentScene = MENU;
    currentDifficulty = EASY;
    menu.addEntry("Continue");
    menu.addEntry("New Game");
    menu.addEntry("Scoreboard");
    menu.addEntry("Quit");
}

void Game::Run() {
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
            if (e.type == sf::Event::Closed)
                mWindow.close();
            else {
                menu.handleEvent(e);
            }
        }
        break;

    case GAME:
        while (mWindow.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                save();
                mWindow.close();
            } else if (e.type == sf::Event::KeyPressed &&
                       e.key.code == sf::Keyboard::Escape) {
                save();
                currentScene = MENU;
            }
            board.handleEvent(e);
            easyStartBtn.handleEvent(e);
            mediumStartBtn.handleEvent(e);
            hardStartBtn.handleEvent(e);
        }
        break;
    case SCOREBOARD:
        while (mWindow.pollEvent(e)) {
            if (e.type == sf::Event::KeyPressed &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                currentScene = MENU;
                reset();
            }
        }
        break;
    case GAMEOVER:
        while (mWindow.pollEvent(e)) {
            if (e.type == sf::Event::KeyPressed ||
                e.type == sf::Event::MouseButtonPressed) {
                currentScene = GAME;
                reset();
            }
        }
        break;

    case GAMEWIN:
        while (mWindow.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                mWindow.close();
            else if (e.type == sf::Event::KeyPressed ||
                     e.type == sf::Event::MouseButtonPressed) {
                currentScene = GAME;
                reset();
            }
        }
        break;
    }
}

void Game::update() {
    if (board.state == LOSE)
        currentScene = GAMEOVER;
    else if (board.state == WIN) {
        scoreBoard.save(currentTime.asSeconds(), currentDifficulty);
        currentScene = GAMEWIN;
        board.state = PLAYING;
    }

    if (currentScene == MENU) {
        if (menu.choiceSelected) {
            menu.choiceSelected = false;
            switch (menu.choice) {
            case 0:
                load();
                currentScene = GAME;
                break;
            case 1:
                reset();
                currentScene = GAME;
                resetTimer();
                break;
            case 2:
                currentScene = SCOREBOARD;
                scoreBoard.load();
                break;
            case 3:
                mWindow.close();
                break;
            }
        }
    } else if (currentScene == GAME) {
        currentTime += timer.restart();
        if (easyStartBtn.clicked) {
            board.initialize(8, 8, 10);
            currentDifficulty = EASY;
            resetTimer();
        } else if (mediumStartBtn.clicked) {
            board.initialize(16, 16, 40);
            currentDifficulty = MEDIUM;
            resetTimer();
        } else if (hardStartBtn.clicked) {
            board.initialize(24, 24, 100);
            currentDifficulty = HARD;
            resetTimer();
        }
    }
}

void Game::render() {
    mWindow.clear(sf::Color(255, 205, 161));

    switch (currentScene) {
    case MENU:
        texture.loadFromFile("./resource/background.png");
        sprite.setTexture(texture);
        mWindow.draw(sprite);
        //drawGameTitle(mWindow);
        menu.draw(mWindow);
        break;

    case GAME:
        drawBackground(mWindow);
        drawGameStatus(mWindow, board.bombCount, board.flagCount,
                       currentTime.asSeconds());
        board.draw(mWindow);
        easyStartBtn.draw(mWindow);
        mediumStartBtn.draw(mWindow);
        hardStartBtn.draw(mWindow);
        break;

    case SCOREBOARD:
        scoreBoard.draw(mWindow);
        break;

    case GAMEOVER:
        drawBackground(mWindow);
        drawGameStatus(mWindow, board.bombCount, board.flagCount,
                       currentTime.asSeconds());
        board.draw(mWindow);
        easyStartBtn.draw(mWindow);
        mediumStartBtn.draw(mWindow);
        hardStartBtn.draw(mWindow);
        drawGameoverMenu(mWindow);
        break;

    case GAMEWIN:
        drawBackground(mWindow);
        drawGameStatus(mWindow, board.bombCount, board.flagCount,
                       currentTime.asSeconds());
        board.draw(mWindow);
        easyStartBtn.draw(mWindow);
        mediumStartBtn.draw(mWindow);
        hardStartBtn.draw(mWindow);
        drawWin(mWindow);
        break;
    }

    mWindow.display();
}

void Game::reset() {
    switch (currentDifficulty) {
    case EASY:
        board.initialize(8, 8, 10);
        break;
    case MEDIUM:
        board.initialize(16, 16, 40);
        break;
    case HARD:
        board.initialize(24, 24, 100);
        break;
    }

    resetTimer();
}

void Game::save() {
    ofstream fout;
    fout.open("./save.dta");
    board.save(fout);
    fout.close();
    fout.open("./save.dta", ios::app);
    fout << currentTime.asSeconds();
    fout.close();
}

void Game::load() {
    ifstream fin;
    fin.open("./save.dta");
    board.load(fin);
    float cTime;
    fin >> cTime;
    currentTime = sf::seconds(cTime);
    timer.restart();
    fin.close();
}

void Game::resetTimer() {
    currentTime = sf::seconds(0.f);
    timer.restart();
}
