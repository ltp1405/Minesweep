#include "Game.hpp"
#include <iostream>
#include <fstream>
#include "GameMenu.hpp"
using namespace std;

int main() {
    Game game;
    game.Run();
}

Game::Game()
: mWindow(sf::RenderWindow(sf::VideoMode(900, 900), "Minesweeper", sf::Style::Close)) {
    font.loadFromFile("./resource/DejaVuSansMono.ttf");
    srand(time(0));
    board.x = 300;
    board.y = 210;
    easyStartBtn.move(100.f, 440.f);
    mediumStartBtn.move(100.f, 520.f);
    hardStartBtn.move(100.f, 600.f);
    easyStartBtn.setText("Easy");
    mediumStartBtn.setText("Medium");
    hardStartBtn.setText("Hard");
    currentScene = MENU;
    currentDifficulty = EASY;
    menu.AddEntry("Continue");
    menu.AddEntry("New Game");
    menu.AddEntry("Quit");
}

void Game::Run() {
    while (mWindow.isOpen()) {
        HandleEvent();
        Update();
        Render();
    }
}

void Game::HandleEvent() {
    sf::Event e;
    
    switch (currentScene) {
    case MENU:
        while (mWindow.pollEvent(e)) {
            if(e.type == sf::Event::Closed)
                mWindow.close();
            else {
                menu.HandleEvent(e);
            }
        }
        break;

    case GAME:
        while (mWindow.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                Save();
                mWindow.close();
            } else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
                Save();
                currentScene = MENU;
            }
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

void Game::Update() {
    if (board.state == LOSE)
        currentScene = GAMEOVER;
    else if (board.state == WIN)
        currentScene = GAMEWIN;

    if (currentScene == MENU) {
        if (menu.choiceSelected) {
            menu.choiceSelected = false;
            switch (menu.choice) {
            case 0:
                Load();
                currentScene = GAME;
                break;
            case 1:
                Reset();
                currentScene = GAME;
                ResetTimer();
                break;
            case 2:
                mWindow.close();
                break;
            }
        }
    } else if (currentScene == GAME) {
        currentTime += timer.restart();
        if (easyStartBtn.clicked) {
            board.Initialize(8, 8, 10);
            currentDifficulty = EASY;
            ResetTimer();
        } else if (mediumStartBtn.clicked) {
            board.Initialize(16, 16, 40);
            currentDifficulty = MEDIUM;
            ResetTimer();
        } else if (hardStartBtn.clicked) {
            board.Initialize(24, 24, 100);
            currentDifficulty = HARD;
            ResetTimer();
        }
    }
}

void Game::Render() {
    mWindow.clear(sf::Color(255, 205, 161));

    switch (currentScene) {
    case MENU:
        DrawGameTitle(mWindow);
        menu.Draw(mWindow);
        break;

    case GAME:
        DrawGameTitle(mWindow);
        DrawGameStatus(mWindow, board.bombCount, board.flagCount, currentTime.asSeconds()); 
        board.Draw(mWindow);
        easyStartBtn.draw(mWindow);
        mediumStartBtn.draw(mWindow);
        hardStartBtn.draw(mWindow);
        break;

    case GAMEOVER:
        DrawGameTitle(mWindow);
        DrawGameStatus(mWindow, board.bombCount, board.flagCount, currentTime.asSeconds()); 
        board.Draw(mWindow);
        easyStartBtn.draw(mWindow);
        mediumStartBtn.draw(mWindow);
        hardStartBtn.draw(mWindow);
        DrawGameoverMenu(mWindow);
        break;

    case GAMEWIN:
        DrawWin(mWindow);
        break;
    }

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

    ResetTimer();
}

void Game::Save() {
    ofstream fout;
    fout.open("./save.dta");
    board.Save(fout);
    fout.close();
    fout.open("./save.dta", ios::app);
    fout << currentTime.asSeconds();
    fout.close();
}

void Game::Load() {
    ifstream fin;
    fin.open("./save.dta");
    board.Load(fin);
    float cTime;
    fin >> cTime;
    currentTime = sf::seconds(cTime);
    timer.restart();
    fin.close();
}

void Game::ResetTimer() {
    currentTime = sf::seconds(0.f);
    timer.restart();
}
