#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
using namespace std;

enum CellType { BOMB, NORMAL };
enum CellState { FLAGGED, HIDDEN, REVEALED };
enum GameState { LOSE, WIN, PAUSED, PLAYING };


struct BombCell {
    bool triggered = false;
};


struct NormalCell {
    int nearbyBombs;
};


struct BoardCell {
    CellState state = HIDDEN;
    CellType type;
    union {
        BombCell bombCell;
        NormalCell normalCell;
    };

    BoardCell(CellType);
};


class Board {
public:
    int x = 0;
    int y = 0;
    int width;
    int height;
    float scale = 1.f;
    int bombCount;
    int flagCount;
    int revealedCount = 0;
    GameState state = PLAYING;
    BoardCell **grid;

    Board();
    ~Board();
    void initialize(int width, int height, int bombCount);
    void DFS(int x, int y);
    void toggleFlag(int x, int y);
    void choose(int x, int y);
    void save(ofstream&);
    void load(ifstream&);

	void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event event);

private:
    int cellWidth = 32;
    sf::Sprite sprite;
    sf::Texture texture;

    int countBomb(int x, int y);
    void placeBomb();
    void generateGrid();
    void setNumberTexture(int n);
    void setBombTexture();
    void setFlagTexture();
    void setHiddenTexture();
    bool checkForWin();
    void realCoordToCellCoord(int rX, int rY, int &cX, int &cY);
    void openAll();
};
