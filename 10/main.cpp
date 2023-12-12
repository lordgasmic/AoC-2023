#include "lordgasmic.h"
#include <iostream>

enum PipeType {
    vertical, horizontal, ne, nw, se, sw, ground, starting, null
};

enum Direction {
   center, left, right, up, down
};

PipeType lookupTable(std::string &string) {
    if (string == "|") {
        return vertical;
    }
    if (string == "-") {
        return horizontal;
    }
    if (string == "L") {
        return ne;
    }
    if (string == "J") {
        return nw;
    }
    if (string == "7") {
        return sw;
    }
    if (string == "F") {
        return se;
    }
    if (string == ".") {
        return ground;
    }
    if (string == "S") {
        return starting;
    }

    return null;
}

struct Tile {
    PipeType pipeType;
    Tile *top{nullptr};
    Tile *bottom{nullptr};
    Tile *left{nullptr};
    Tile *right{nullptr};
    int x;
    int y;

    explicit Tile(PipeType pipeType) {
        this->pipeType = pipeType;
    }
};

bool isConnected(PipeType prime, PipeType neighbor, Direction relative) {
    if (prime == vertical && relative == down &&
        (neighbor == vertical || neighbor == ne || neighbor == nw || neighbor == starting)) {
        return true;
    }
    if (prime == vertical && relative == up &&
        (neighbor == vertical || neighbor == se || neighbor == sw || neighbor == starting)) {
        return true;
    }

    if (prime == horizontal && relative == left &&
        (neighbor == horizontal || neighbor == ne || neighbor == se || neighbor == starting)) {
        return true;
    }
    if (prime == horizontal && relative == right &&
        (neighbor == horizontal || neighbor == nw || neighbor == sw || neighbor == starting)) {
        return true;
    }

    if (prime == ne && relative == right &&
        (neighbor == horizontal || neighbor == nw || neighbor == sw || neighbor == starting)) {
        return true;
    }
    if (prime == ne && relative == up &&
        (neighbor == vertical || neighbor == se || neighbor == sw || neighbor == starting)) {
        return true;
    }

    if (prime == nw && relative == left &&
        (neighbor == horizontal || neighbor == ne || neighbor == se || neighbor == starting)) {
        return true;
    }
    if (prime == nw && relative == up &&
        (neighbor == vertical || neighbor == se || neighbor == sw || neighbor == starting)) {
        return true;
    }

    if (prime == sw && relative == left &&
        (neighbor == horizontal || neighbor == ne || neighbor == se || neighbor == starting)) {
        return true;
    }
    if (prime == sw && relative == down &&
        (neighbor == vertical || neighbor == ne || neighbor == nw || neighbor == starting)) {
        return true;
    }

    if (prime == se && relative == right &&
        (neighbor == horizontal || neighbor == nw || neighbor == sw || neighbor == starting)) {
        return true;
    }
    if (prime == se && relative == down &&
        (neighbor == vertical || neighbor == ne || neighbor == nw || neighbor == starting)) {
        return true;
    }

    if (prime == starting && relative == up &&
        (neighbor == vertical || neighbor == se || neighbor == sw)) {
        return true;
    }
    if (prime == starting && relative == down &&
        (neighbor == vertical || neighbor == ne || neighbor == nw)) {
        return true;
    }
    if (prime == starting && relative == left &&
        (neighbor == horizontal || neighbor == ne || neighbor == se)) {
        return true;
    }
    if (prime == starting && relative == right &&
        (neighbor == horizontal || neighbor == nw || neighbor == sw)) {
        return true;
    }

    return false;
}

Direction updateCourse(PipeType current, Direction heading){
    if (current == vertical && heading == up) {
        return up;
    }
    if (current == vertical && heading == down) {
        return down;
    }

    if (current == horizontal && heading == left) {
        return left;
    }
    if (current == horizontal && heading == right) {
        return right;
    }

    if (current == ne && heading == left) {
        return up;
    }
    if (current == ne && heading == down) {
        return right;
    }

    if (current == nw && heading == down) {
        return left;
    }
    if (current == nw && heading == right) {
        return up;
    }

    if (current == sw && heading ==right){
        return down;
    }
    if (current == sw && heading == up) {
        return left;
    }

    if (current == se && heading == left) {
        return down;
    }
    if (current == se && heading == up ) {
        return right;
    }

    return center;
}

struct Env {
    std::string fileName;
    int row;
    int col;
    Direction startingMove;
};

//Env env{"/home/lordgasmic/workspace/AoC-2023/10/input.p2-1.test.txt", 11, 9, right};
//Env env{"/home/lordgasmic/workspace/AoC-2023/10/input.p2-2.test.txt", 20, 10, down};
//Env env{"/home/lordgasmic/workspace/AoC-2023/10/input.p2-3.test.txt", 20, 10, down};
//Env env{"/home/lordgasmic/workspace/AoC-2023/10/input-2.test.txt", 5, right};
Env env{"/home/lordgasmic/workspace/AoC-2023/10/input.txt",140, 140, right};

void partOne() {
    std::vector<std::string> lines;
    lordgasmic::readFile(env.fileName, lines);

    std::vector<std::vector<Tile *>> tiles;
    for (const std::string &line: lines) {
        std::vector<Tile *> tileLine;
        for (int i = 0; i < line.length(); i++) {
            auto c = line.substr(i, 1);
            PipeType pipeType = lookupTable(c);
            tileLine.push_back(new Tile(pipeType));
        }
        tiles.push_back(tileLine);
    }

    // find neighbors
    int startingI{-1};
    int startingJ{-1};
    for (int i = 0; i < env.col; i++) {
        for (int j = 0; j < env.row; j++) {
            auto tile = tiles[i][j];

            Tile *tTile;
            Tile *bTile;
            Tile *lTile;
            Tile *rTile;
            switch (tile->pipeType) {
                case vertical:
                    tTile = nullptr;
                    bTile = nullptr;
                    if (i > 0) {
                        tTile = tiles[i - 1][j];
                        if (!isConnected(tile->pipeType, tTile->pipeType, up)) {
                            tTile = nullptr;
                        }
                    }
                    if (i + 1 < env.col) {
                        bTile = tiles[i + 1][j];
                        if (!isConnected(tile->pipeType, bTile->pipeType, down)) {
                            bTile = nullptr;
                        }
                    }
                    tile->top = tTile;
                    tile->bottom = bTile;
                    break;
                case horizontal:
                    lTile = nullptr;
                    rTile = nullptr;
                    if (j > 0) {
                        lTile = tiles[i][j - 1];
                        if (!isConnected(tile->pipeType, lTile->pipeType, left)) {
                            lTile = nullptr;
                        }
                    }
                    if (j + 1 < env.row) {
                        rTile = tiles[i][j + 1];
                        if (!isConnected(tile->pipeType, rTile->pipeType, right)) {
                            rTile = nullptr;
                        }
                    }
                    tile->left = lTile;
                    tile->right = rTile;
                    break;
                case ne:
                    tTile = nullptr;
                    rTile = nullptr;
                    if (i > 0) {
                        tTile = tiles[i - 1][j];
                        if (!isConnected(tile->pipeType, tTile->pipeType, up)) {
                            tTile = nullptr;
                        }
                    }
                    if (j + 1 < env.row) {
                        rTile = tiles[i][j + 1];
                        if (!isConnected(tile->pipeType, rTile->pipeType, right)) {
                            rTile = nullptr;
                        }
                    }
                    tile->top = tTile;
                    tile->right = rTile;
                    break;
                case nw:
                    tTile = nullptr;
                    lTile = nullptr;
                    if (i > 0) {
                        tTile = tiles[i - 1][j];
                        if (!isConnected(tile->pipeType, tTile->pipeType, up)) {
                            tTile = nullptr;
                        }
                    }
                    if (j > 0) {
                        lTile = tiles[i][j - 1];
                        if (!isConnected(tile->pipeType, lTile->pipeType, left)) {
                            lTile = nullptr;
                        }
                    }
                    tile->top = tTile;
                    tile->left = lTile;
                    break;
                case se:
                    bTile = nullptr;
                    rTile = nullptr;
                    if (i + 1 < env.col) {
                        bTile = tiles[i + 1][j];
                        if (!isConnected(tile->pipeType, bTile->pipeType, down)) {
                            bTile = nullptr;
                        }
                    }
                    if (j + 1 < env.row) {
                        rTile = tiles[i][j + 1];
                        if (!isConnected(tile->pipeType, rTile->pipeType, right)) {
                            rTile = nullptr;
                        }
                    }
                    tile->bottom = bTile;
                    tile->right = rTile;
                    break;
                case sw:
                    bTile = nullptr;
                    lTile = nullptr;
                    if (i + 1 < env.col) {
                        bTile = tiles[i + 1][j];
                        if (!isConnected(tile->pipeType, bTile->pipeType, down)) {
                            bTile = nullptr;
                        }
                    }
                    if (j > 0) {
                        lTile = tiles[i][j - 1];
                        if (!isConnected(tile->pipeType, lTile->pipeType, left)) {
                            lTile = nullptr;
                        }
                    }
                    tile->bottom = bTile;
                    tile->left = lTile;
                    break;
                case ground:
                    // nothing to do
                    break;
                case starting:
                    startingI = i;
                    startingJ = j;
                    tTile = nullptr;
                    bTile = nullptr;
                    rTile = nullptr;
                    lTile = nullptr;

                    if (i > 0) {
                        tTile = tiles[i - 1][j];
                        if (!isConnected(tile->pipeType, tTile->pipeType, up)) {
                            tTile = nullptr;
                        }
                    }
                    if (i + 1 < env.col) {
                        bTile = tiles[i + 1][j];
                        if (!isConnected(tile->pipeType, bTile->pipeType, down)) {
                            bTile = nullptr;
                        }
                    }
                    if (j > 0) {
                        lTile = tiles[i][j - 1];
                        if (!isConnected(tile->pipeType, lTile->pipeType, left)) {
                            lTile = nullptr;
                        }
                    }
                    if (j + 1 < env.row) {
                        rTile = tiles[i][j + 1];
                        if (!isConnected(tile->pipeType, rTile->pipeType, right)) {
                            rTile = nullptr;
                        }
                    }
                    tile->top = tTile;
                    tile->bottom = bTile;
                    tile->right = rTile;
                    tile->left = lTile;
                    break;
                case null:
                default:
                    std::cout << "Error reading pipe type: [" << i << ", " << j << "]" << std::endl;
                    return;
            }
        }
    }

    // find starting loc neighbors
    auto currentTile = tiles[startingI][startingJ];

    int sum{0};
    auto course = env.startingMove;
    do {
        Tile *nextTile = nullptr;
        if (course == right) {
              nextTile = currentTile->right;
        }
        if (course == left) {
              nextTile = currentTile->left;
        }
        if (course == up) {
              nextTile = currentTile->top;
        }
        if (course == down) {
              nextTile = currentTile->bottom;
        }
        currentTile = nextTile;
        course = updateCourse(currentTile->pipeType, course);
        sum++;
    } while (currentTile->pipeType != starting);

    int longestPath = sum/2;
    std::cout << "longestPath: " << longestPath << std::endl;
}

void partTwo() {
    std::vector<std::string> lines;
    lordgasmic::readFile(env.fileName, lines);

    std::vector<std::vector<Tile *>> tiles;
    for (const std::string &line: lines) {
        std::vector<Tile *> tileLine;
        for (int i = 0; i < line.length(); i++) {
            auto c = line.substr(i, 1);
            PipeType pipeType = lookupTable(c);
            tileLine.push_back(new Tile(pipeType));
        }
        tiles.push_back(tileLine);
    }

    // find neighbors
    int startingI{-1};
    int startingJ{-1};
    for (int i = 0; i < env.col; i++) {
        for (int j = 0; j < env.row; j++) {
            auto tile = tiles[i][j];
            tile->x = j;
            tile->y = i;

            Tile *tTile;
            Tile *bTile;
            Tile *lTile;
            Tile *rTile;
            switch (tile->pipeType) {
                case vertical:
                    tTile = nullptr;
                    bTile = nullptr;
                    if (i > 0) {
                        tTile = tiles[i - 1][j];
                        if (!isConnected(tile->pipeType, tTile->pipeType, up)) {
                            tTile = nullptr;
                        }
                    }
                    if (i + 1 < env.col) {
                        bTile = tiles[i + 1][j];
                        if (!isConnected(tile->pipeType, bTile->pipeType, down)) {
                            bTile = nullptr;
                        }
                    }
                    tile->top = tTile;
                    tile->bottom = bTile;
                    break;
                case horizontal:
                    lTile = nullptr;
                    rTile = nullptr;
                    if (j > 0) {
                        lTile = tiles[i][j - 1];
                        if (!isConnected(tile->pipeType, lTile->pipeType, left)) {
                            lTile = nullptr;
                        }
                    }
                    if (j + 1 < env.row) {
                        rTile = tiles[i][j + 1];
                        if (!isConnected(tile->pipeType, rTile->pipeType, right)) {
                            rTile = nullptr;
                        }
                    }
                    tile->left = lTile;
                    tile->right = rTile;
                    break;
                case ne:
                    tTile = nullptr;
                    rTile = nullptr;
                    if (i > 0) {
                        tTile = tiles[i - 1][j];
                        if (!isConnected(tile->pipeType, tTile->pipeType, up)) {
                            tTile = nullptr;
                        }
                    }
                    if (j + 1 < env.row) {
                        rTile = tiles[i][j + 1];
                        if (!isConnected(tile->pipeType, rTile->pipeType, right)) {
                            rTile = nullptr;
                        }
                    }
                    tile->top = tTile;
                    tile->right = rTile;
                    break;
                case nw:
                    tTile = nullptr;
                    lTile = nullptr;
                    if (i > 0) {
                        tTile = tiles[i - 1][j];
                        if (!isConnected(tile->pipeType, tTile->pipeType, up)) {
                            tTile = nullptr;
                        }
                    }
                    if (j > 0) {
                        lTile = tiles[i][j - 1];
                        if (!isConnected(tile->pipeType, lTile->pipeType, left)) {
                            lTile = nullptr;
                        }
                    }
                    tile->top = tTile;
                    tile->left = lTile;
                    break;
                case se:
                    bTile = nullptr;
                    rTile = nullptr;
                    if (i + 1 < env.col) {
                        bTile = tiles[i + 1][j];
                        if (!isConnected(tile->pipeType, bTile->pipeType, down)) {
                            bTile = nullptr;
                        }
                    }
                    if (j + 1 < env.row) {
                        rTile = tiles[i][j + 1];
                        if (!isConnected(tile->pipeType, rTile->pipeType, right)) {
                            rTile = nullptr;
                        }
                    }
                    tile->bottom = bTile;
                    tile->right = rTile;
                    break;
                case sw:
                    bTile = nullptr;
                    lTile = nullptr;
                    if (i + 1 < env.col) {
                        bTile = tiles[i + 1][j];
                        if (!isConnected(tile->pipeType, bTile->pipeType, down)) {
                            bTile = nullptr;
                        }
                    }
                    if (j > 0) {
                        lTile = tiles[i][j - 1];
                        if (!isConnected(tile->pipeType, lTile->pipeType, left)) {
                            lTile = nullptr;
                        }
                    }
                    tile->bottom = bTile;
                    tile->left = lTile;
                    break;
                case ground:
                    // nothing to do
                    break;
                case starting:
                    startingI = i;
                    startingJ = j;
                    tTile = nullptr;
                    bTile = nullptr;
                    rTile = nullptr;
                    lTile = nullptr;

                    if (i > 0) {
                        tTile = tiles[i - 1][j];
                        if (!isConnected(tile->pipeType, tTile->pipeType, up)) {
                            tTile = nullptr;
                        }
                    }
                    if (i + 1 < env.col) {
                        bTile = tiles[i + 1][j];
                        if (!isConnected(tile->pipeType, bTile->pipeType, down)) {
                            bTile = nullptr;
                        }
                    }
                    if (j > 0) {
                        lTile = tiles[i][j - 1];
                        if (!isConnected(tile->pipeType, lTile->pipeType, left)) {
                            lTile = nullptr;
                        }
                    }
                    if (j + 1 < env.row) {
                        rTile = tiles[i][j + 1];
                        if (!isConnected(tile->pipeType, rTile->pipeType, right)) {
                            rTile = nullptr;
                        }
                    }
                    tile->top = tTile;
                    tile->bottom = bTile;
                    tile->right = rTile;
                    tile->left = lTile;
                    break;
                case null:
                default:
                    std::cout << "Error reading pipe type: [" << i << ", " << j << "]" << std::endl;
                    return;
            }
        }
    }

    // find starting loc neighbors
    auto currentTile = tiles[startingI][startingJ];
    int sum{0};
    long p{0};
    auto course = env.startingMove;
    do {
        Tile *nextTile = nullptr;
        if (course == right) {
              nextTile = currentTile->right;
        }
        if (course == left) {
              nextTile = currentTile->left;
        }
        if (course == up) {
              nextTile = currentTile->top;
        }
        if (course == down) {
              nextTile = currentTile->bottom;
        }

        long x1 = currentTile->x;
        long y1 = currentTile->y;
        long x2 = nextTile->x;
        long y2 = nextTile->y;

        long m1 = x1 * y2;
        long m2 = x2 * y1;
        p += m1 - m2;

        currentTile = nextTile;
        course = updateCourse(currentTile->pipeType, course);
        sum++;
    } while (currentTile->pipeType != starting);

    int longestPath = sum/2;
    long a = p/2;
    std::cout << "longestPath: " << longestPath << std::endl;
    std::cout << "area: " << a << std::endl;
    // a + 1 - b/2 = i
    long pick = a + 1 - longestPath;
    std::cout << "picks: " << pick << std::endl;
}

int main() {
//    partOne();
    partTwo();
    return 0;
}
