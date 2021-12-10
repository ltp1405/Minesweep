#pragma once

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Menu.hpp"
#include "Button.hpp"
#include "GameMenu.hpp"


class Game {
public:
    enum Scene { MENU, GAME, PAUSE, GAMEOVER, GAMEWIN };
    enum Difficulty { EASY, MEDIUM, HARD };
public:
    Game();
    void Run();

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
    PushButton loadGameYesBtn;
    PushButton loadGameNoBtn;
    Menu menu;

    void HandleEvent();
    void Update();
    void Render();
    void Reset();
    void ResetTimer();
    void Save();
    void Load();
};
