#include "Board.hpp"

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

Board::Board() {
    texture.loadFromFile("./resource/tiles.jpg");
    sprite.setTexture(texture);
}

Board::~Board() {
    for (int i = 0; i < this->width; ++i) {
        delete [] this->grid[i];
    }
    delete [] this->grid;
}

void Board::PlaceBomb() {
    int count = bombCount;
    while (count > 0) {
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

            scale = 480 / float((cellWidth*width));
            sprite.setScale(sf::Vector2f(scale, scale));
            posX = x + i*cellWidth*scale;
            posY = y + j*cellWidth*scale;
            sprite.setPosition(posX, posY);
            window.draw(sprite);
        }
}

void Board::Initialize(int width, int height, int bombCount) {
    this->width = width;
    this->height = height;
    this->bombCount = bombCount;
    flagCount = bombCount;


    this->grid = new BoardCell*[this->width];
    for (int i = 0; i < this->width; i++)
        this->grid[i] = new BoardCell[this->height];

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
        revealedCount += 1;
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
    if (cell->state == HIDDEN && flagCount > 0) {
        cell->state = FLAGGED;
        flagCount--;
    } else if (cell->state == FLAGGED) {
        cell->state = HIDDEN;
        flagCount++;
    }
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
    if (coordX < 0 || coordX > width - 1 || coordY < 0 || coordY > height - 1)
        return;

    BoardCell *cell = &grid[coordX][coordY];
    if (cell->type == BOMB) {
        cell->state = REVEALED;
        this->state = LOSE;
        OpenAll();
        return;
    }

    switch (cell->state) {
        case HIDDEN:
            DFS(coordX, coordY);
            break;

        case FLAGGED:
            return;
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
    cX = (rX - this->x) / (cellWidth*scale);
    cY = (rY - this->y) / (cellWidth*scale);
}

void Board::OpenAll() {
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            if (grid[i][j].type == BOMB)
                grid[i][j].state = REVEALED;
        }
}

void Board::HandleEvent(sf::Event event) {
    switch (event.type) {
        case sf::Event::MouseButtonPressed:
        {
            int rX = event.mouseButton.x;
            int rY = event.mouseButton.y;
            if (event.mouseButton.button == sf::Mouse::Left) {
                Choose(rX, rY);
            } else if (event.mouseButton.button == sf::Mouse::Right)
                ToggleFlag(rX, rY);
            break;
        }

        default:
            break;
    }
}

void Board::Save() {
    ofstream fout;
    fout.open("save.dta");
    fout << width << " ";
    fout << height << " ";
    fout << bombCount << " ";
    fout << flagCount << " ";
    fout << revealedCount << endl;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (grid[i][j].type == BOMB)
                fout << grid[i][j].type << " " << grid[i][j].state << " " << 0 << " ";
            else fout << grid[i][j].type << " " << grid[i][j].state << " " << grid[i][j].normalCell.nearbyBombs << " ";
        }
        fout << endl;
    }

    fout.close();
}

void Board::Load() {
    ifstream fin;
    fin.open("save.dta");
    fin >> width;
    fin >> height;
    fin >> bombCount;
    Initialize(width, height, bombCount);
    fin >> flagCount;
    fin >> revealedCount;

    int state;
    int type;
    int nearbyBombs;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            fin >> type;
            fin >> state;
            fin >> nearbyBombs;
            if (type == BOMB)
                grid[i][j].type = BOMB;
            else {
                grid[i][j].type = NORMAL;
                grid[i][j].normalCell.nearbyBombs = nearbyBombs;
            }
            if (state == FLAGGED)
                grid[i][j].state = FLAGGED;
            else if (state == HIDDEN)
                grid[i][j].state = HIDDEN;
            else
                grid[i][j].state = REVEALED;
        }
    }
    fin.close();
}
