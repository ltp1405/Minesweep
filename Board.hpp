#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
using namespace std;

/**
 * Denote the type of the cell
 */
enum CellType { BOMB, NORMAL };
/**
 * State of the cell
 */
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

    BoardCell();
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
    /**
     * init Board
     *
     * @param width Width of the board
     * @param height Height of the board
     */
    void initialize(int width, int height, int bombCount);

    void DFS(int x, int y);

    /**
     * Flagged or unflagged a cell at a [x][y] position
     * @param x,y cell position
     */
    void toggleFlag(int x, int y);

    /**
     * Trigger an action when a cell is chosen (clicked)
     */
    void choose(int x, int y);

    /**
     * Save board state to file
     */
    void save(ofstream &);

    /**
     * Load board state from file
     */
    void load(ifstream &);

    void draw(sf::RenderWindow &window);
    void handleEvent(sf::Event event);

  private:
    int cellWidth = 32;
    sf::Sprite sprite;
    sf::Texture texture;

    /**
     * Count number of bombs around a specific cell
     * @return number of bombs around a cel at position [x,y]
     */
    int countBomb(int x, int y);

    /**
     * Randomly place bombs across the board
     */
    void placeBomb();

    /**
     * Generate grid of cell
     *
     * The grid does not contain any bombs yet
     */
    void generateGrid();

    void setNumberTexture(int n);
    void setBombTexture();
    void setFlagTexture();
    void setHiddenTexture();

    /**
     * Check if the board is in win state
     *
     * @return true if win, false if not
     */
    bool checkForWin();

    /**
     * Convert window coordinate to local cell coordinate
     *
     * @param rX window x coordinate
     * @param rY window y coordinate
     * @param cX cell x output coordinate
     * @param cY cell y output coordinate
     */
    void realCoordToCellCoord(int rX, int rY, int &cX, int &cY);

    /**
     * Open all cell in board
     */
    void openAll();
};
