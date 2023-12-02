#include <iostream>
#include <fstream>
#include <vector>

const int red{12};
const int green{13};
const int blue{14};

int lookupTable(std::string &color) {
    if ("red" == color) {
        return red;
    }
    if ("green" == color) {
        return green;
    }
    if ("blue" == color) {
        return blue;
    }

    return -1;
}

void split(std::string &string, std::vector<std::string> &vector, const char token = ' ') {
    std::string accumulator;
    for (int i = 0; i < string.length(); i++) {
        if (accumulator.length() == 0 && string.at(i) == ' ') {
            continue;
        }
        if (string.at(i) == token) {
            vector.insert(vector.end(), accumulator);
            accumulator = "";
            continue;
        }
        std::string single = string.substr(i, 1);
        accumulator += single;
    }
    vector.insert(vector.end(), accumulator);
}

void partOne() {
    long sum{0};

    std::ifstream infile;
    infile.open("/home/lordgasmic/workspace/AoC-2023/2/input.txt");
    if (infile.is_open()) {
        std::string str;
        while (std::getline(infile, str)) {
            bool invalid{false};
            // get game id
            int gameSpaceIndex = str.find(' ');
            int colonIndex = str.find(':');
            std::string gameId = str.substr(gameSpaceIndex + 1, colonIndex - gameSpaceIndex - 1);

            // parse games by semi-colon (tokenizer?)
            std::string gamesLine = str.substr(colonIndex + 2);
            std::vector<std::string> gameVector;
            split(gamesLine, gameVector, ';');
            // check games
            for (std::string &game: gameVector) {
                if (invalid) {
                    break;
                }
                // get count and color
                std::vector<std::string> drawVector;
                split(game, drawVector, ',');
                for (std::string &draw: drawVector) {
                    if (invalid) {
                        break;
                    }
                    std::vector<std::string> colorVector;
                    split(draw, colorVector);
                    int count = std::stoi(colorVector[0]);
                    int colorValue = lookupTable(colorVector[1]);
                    if (count > colorValue) {
                        invalid = true;
                    }
                }
            }
            if (!invalid) {
                sum += std::stoi(gameId);
            }
        }
        infile.close();
    }
    std::cout << "part one sum is: " << sum << std::endl;
}

void partTwo() {
    long sum{0};

    std::ifstream infile;
    infile.open("/home/lordgasmic/workspace/AoC-2023/2/input.txt");
    if (infile.is_open()) {
        std::string str;
        while (std::getline(infile, str)) {

        }
        infile.close();
    }
    std::cout << "part one sum is: " << sum << std::endl;
}

int main() {
    partOne();
    partTwo();
    return 0;
}
