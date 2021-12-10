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
    void Initialize(int width, int height, int bombCount);
    void DFS(int x, int y);
    void ToggleFlag(int x, int y);
    void Choose(int x, int y);
    void Save(ofstream&);
    void Load(ifstream&);

	void Draw(sf::RenderWindow& window);
    void HandleEvent(sf::Event event);

private:
    int cellWidth = 32;
    sf::Sprite sprite;
    sf::Texture texture;

    int CountBomb(int x, int y);
    void PlaceBomb();
    void GenerateGrid();
    void SetNumberTexture(int n);
    void SetBombTexture();
    void SetFlagTexture();
    void SetHiddenTexture();
    bool CheckForWin();
    void RealCoordToCellCoord(int rX, int rY, int &cX, int &cY);
    void OpenAll();
};
