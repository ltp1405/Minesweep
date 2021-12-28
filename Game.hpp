#pragma once

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Menu.hpp"
#include "Button.hpp"
#include "GameMenu.hpp"
#include "Scoreboard.hpp"
#include "Sound.hpp"


class Game {
public:
    enum Scene { MENU, SCOREBOARD, GAME, PAUSE, GAMEOVER, GAMEWIN };
    enum Difficulty { EASY, MEDIUM, HARD };
public:
    Game();
    void Run();

private:
    Scoreboard scoreBoard;
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
    PushButton loadGameYesBtn;
    PushButton loadGameNoBtn;
    Menu menu;
    sf::Sprite sprite;
    sf::Texture texture;
    Sound sound;

    void handleEvent();
    void update();
    void render();
    void reset();
    void resetTimer();
    void save();
    void load();
};
