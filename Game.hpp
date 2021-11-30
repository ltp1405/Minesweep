#pragma once

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Menu.hpp"
#include "Button.hpp"


class Game {
public:
    enum Scene { MENU, GAME, GAMEOVER, GAMEWIN };
    enum Difficulty { EASY, MEDIUM, HARD };
public:
    Game();
    void run();

private:
    sf::Clock timer;
    sf::Time currentTime;
    Board board;
    Scene currentScene;
    Difficulty currentDifficulty;
    sf::RenderWindow mWindow;
    sf::Font font;
    PushButton easyStartBtn;
    PushButton mediumStartBtn;
    PushButton hardStartBtn;

    void handleEvent();
    void update();
    void render();
    void Reset();
};
