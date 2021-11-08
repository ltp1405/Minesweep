#include <iostream>
#include "Board.hpp"
using namespace std;

int Rand(int Min, int Max) {
    return rand() % (Max - Min + 1) + Min;
}

int dx[9] = { 0, -1, 0, 1, 1, 1, 0, -1, -1 };
int dy[9] = { 0, -1, -1, -1, 0, 1, 1, 1, 0 };

BoardCell::BoardCell(CellType t=NORMAL) {
    type = t;
    switch (type) {
        case BOMB:
            bombCell = BombCell();
            break;
        case NORMAL:
            normalCell = NormalCell();
            break;
    }
}

Board::Board(int width, int height, int bombCount) {
    this->width = width;
    this->height = height;
    this->bombCount = bombCount;

    texture.loadFromFile("tiles.jpg");
    sprite.setTexture(texture);

    this->grid = new BoardCell*[this->width];
    for (int i = 0; i < this->width; i++)
        this->grid[i] = new BoardCell[this->height];
}

Board::~Board() {
    for (int i = 0; i < this->width; ++i) {
        delete [] this->grid[i];
    }
    delete [] this->grid;
}

void Board::PlaceBomb() {
    int count = bombCount;
    while (count >= 0) {
        int x = Rand(0, width - 1);
        int y = Rand(0, height - 1);
        if (this->grid[x][y].type != BOMB) {
            this->grid[x][y].type = BOMB;
            this->grid[x][y].bombCell = BombCell();
            --count;
        }
    }
}

void Board::GenerateGrid() {
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            this->grid[i][j] = BoardCell();
}

int Board::CountBomb(int x, int y) {
    int bombCount = 0;
    // count 8 block for bombs
    for (int k = 0; k <= 8; k++) {
        int X = x + dx[k];
        int Y = y + dy[k];
        if (X < 1 || X > width - 1 || Y < 1 || Y > height - 1)
            continue;
        if (this->grid[x][y].type == BOMB)
            bombCount++;
    }

    return bombCount;
}

void Board::Draw(sf::RenderWindow& window) {
    int posX, posY;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            BoardCell cell = grid[i][j];
            switch (cell.state) {
                case HIDDEN:
                    SetHiddenTexture();
                    break;

                case REVEALED:
                    if (cell.type == NORMAL)
                        SetNumberTexture(grid[i][j].normalCell.nearbyBombs);
                    else
                        SetBombTexture();
                    break;

                case FLAGGED:
                    SetFlagTexture();
                    break;
            }

            posX = x + i*cellWidth;
            posY = y + j*cellWidth;
            sprite.setPosition(posX, posY);
            window.draw(sprite);
        }
}

void Board::Initialize() {
    this->revealedCount = 0;
    this->state = PLAYING;
    GenerateGrid();
    PlaceBomb();

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            if (this->grid[i][j].type == NORMAL) {
                int bombCount = 0;
                // count 8 block for bombs
                for (int k = 0; k <= 8; k++) {
                    int X = i + dx[k];
                    int Y = j + dy[k];
                    if (X < 0 || X > width - 1 || Y < 0 || Y > height - 1)
                        continue;
                    if (this->grid[X][Y].type == BOMB) {
                        bombCount++;
                    }
                }
                this->grid[i][j].normalCell.nearbyBombs = bombCount;
            }
        }
}

void Board::DFS(int x, int y) {
    if (x < 0 || x > width - 1 || y < 0 || y > height -1)
        return;

    BoardCell* cell = &grid[x][y];
    if (cell->state == HIDDEN) {
        cell->state = REVEALED;
        this->revealedCount += 1;
        if (cell->normalCell.nearbyBombs == 0) {
            for (int i = 1; i <= 8; i++) {
                int X = x + dx[i];
                int Y = y + dy[i];
                DFS(X, Y);
            }
        }
    }
}

void Board::ToggleFlag(int x, int y) {
    int cellX, cellY;
    RealCoordToCellCoord(x, y, cellX, cellY);
    BoardCell* cell = &grid[cellX][cellY];
    if (cell->state == HIDDEN)
        cell->state = FLAGGED;
    else if (cell->state == FLAGGED)
        cell->state = HIDDEN;
}

void Board::SetNumberTexture(int n) {
    sprite.setTextureRect(sf::IntRect(n * cellWidth, 0, cellWidth, cellWidth));
}

void Board::SetBombTexture() {
    sprite.setTextureRect(sf::IntRect(9 * cellWidth, 0, cellWidth, cellWidth));
}

void Board::SetFlagTexture() {
    sprite.setTextureRect(sf::IntRect(11 * cellWidth, 0, cellWidth, cellWidth));
}

void Board::SetHiddenTexture() {
    sprite.setTextureRect(sf::IntRect(10 * cellWidth, 0, cellWidth, cellWidth));
}

void Board::Choose(int x, int y) {
    int coordX, coordY;
    RealCoordToCellCoord(x, y, coordX, coordY);
    cout << coordX << " " << coordY << endl;
    if (coordX < 0 || coordX > width - 1 || coordY < 0 || coordY > height - 1)
        return;

    BoardCell *cell = &grid[coordX][coordY];
    if (cell->type == BOMB) {
        cell->state = REVEALED;
        this->state = LOSE;
        return;
    }

    switch (cell->state) {
        case HIDDEN:
            DFS(coordX, coordY);
            break;

        case FLAGGED:
            break;
    }

    if (CheckForWin() == true)
        this->state = WIN;
}

bool Board::CheckForWin() {
    if (revealedCount + bombCount == width * height)
        return true;
    return false;
}

void Board::RealCoordToCellCoord(int rX, int rY, int &cX, int &cY) {
    cX = (rX - this->x) / cellWidth;
    cY = (rY - this->y) / cellWidth;
}
