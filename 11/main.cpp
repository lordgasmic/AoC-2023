#include "lordgasmic.h"
#include <iostream>
#include <algorithm>

struct Galaxy {
    int x;
    int y;
};

struct Env {
    std::string filename;
    int startingLength;
};

//Env env{"/home/lordgasmic/workspace/AoC-2023/11/input.p1-1.test.txt", 10};
Env env{"/home/lordgasmic/workspace/AoC-2023/11/input.txt", 140};

const int factor{1000000};

void partOne() {
    std::vector<std::string> origLines;
    lordgasmic::readFile(env.filename, origLines);

    std::vector<std::vector<char>> convertedLines;
    for (const std::string &s: origLines) {
        std::vector<char> chars;
        for (char c: s) {
            chars.push_back(c);
        }
        convertedLines.push_back(chars);
    }

    std::vector<char> padding;
    padding.insert(padding.begin(), env.startingLength, '.');
    for (auto it = convertedLines.begin(); it != convertedLines.end(); it++) {
        bool galaxyFound{false};
        for (char &cIt: *it) {
            if (cIt == '#') {
                galaxyFound = true;
                break;
            }
        }
        if (!galaxyFound) {
            convertedLines.insert(it, padding);
            it++;
        }
    }

    int length = convertedLines.at(0).size();
    std::vector<int> noGalaxies;
    for (int i = 0; i < length; i++) {
        bool galaxyFound{false};
        for (auto &convertedLine: convertedLines) {
            if (convertedLine.at(i) == '#') {
                galaxyFound = true;
                break;
            }
        }
        if (!galaxyFound) {
            noGalaxies.insert(noGalaxies.begin(), i);
        }
    }

    for (int i: noGalaxies) {
        for (auto &charLine: convertedLines) {
            auto it = charLine.begin() + i;
            charLine.insert(it, '.');
        }
    }

    std::vector<Galaxy *> galaxies;
    for (int i = 0; i < convertedLines.size(); i++) {
        std::vector<char> &current = convertedLines.at(i);
        for (int j = 0; j < current.size(); j++) {
            if (current.at(j) == '#') {
                galaxies.push_back(new Galaxy{j, i});
            }
        }
    }

    int sum{0};
    for (int i = 0; i < galaxies.size(); i++) {
        auto current = galaxies.at(i);
        for (int j = i + 1; j < galaxies.size(); j++) {
            auto next = galaxies.at(j);
            // dx/dy
            int dx = abs(next->x - current->x);
            int dy = abs(next->y - current->y);
            sum += dx + dy;
        }
    }

    std::cout << sum << std::endl;
}

void partTwo() {
    std::vector<std::string> origLines;
    lordgasmic::readFile(env.filename, origLines);

    std::vector<std::vector<char>> convertedLines;
    for (const std::string &s: origLines) {
        std::vector<char> chars;
        for (char c: s) {
            chars.push_back(c);
        }
        convertedLines.push_back(chars);
    }

    std::vector<char> padding;
    padding.insert(padding.begin(), env.startingLength, 'M');
    for (auto it = convertedLines.begin(); it != convertedLines.end(); it++) {
        bool galaxyFound{false};
        for (char &cIt: *it) {
            if (cIt == '#') {
                galaxyFound = true;
                break;
            }
        }
        if (!galaxyFound) {
            convertedLines.erase(it, it + 1);
            convertedLines.insert(it, padding);
//            it += 1000000;
//            it++;
        }
    }

    int length = convertedLines.at(0).size();
    std::vector<int> noGalaxies;
    for (int i = 0; i < length; i++) {
        bool galaxyFound{false};
        for (auto &convertedLine: convertedLines) {
            if (convertedLine.at(i) == '#') {
                galaxyFound = true;
                break;
            }
        }
        if (!galaxyFound) {
            noGalaxies.insert(noGalaxies.begin(), i);
        }
    }

    for (int i: noGalaxies) {
        for (auto &convertedLine: convertedLines) {
            convertedLine[i] = 'M';
        }
    }

    std::vector<Galaxy *> galaxies;
    for (int i = 0; i < convertedLines.size(); i++) {
        std::vector<char> &current = convertedLines.at(i);
        for (int j = 0; j < current.size(); j++) {
            if (current.at(j) == '#') {
                galaxies.push_back(new Galaxy{j, i});
            }
        }
    }

    long sum{0};
    for (int i = 0; i < galaxies.size(); i++) {
        auto current = galaxies.at(i);
        for (int j = i + 1; j < galaxies.size(); j++) {
            auto next = galaxies.at(j);

            int ym{0};
            int xm{0};
            for (int k = current->y; k < next->y; k++) { // check crossing m on y
                if (convertedLines.at(k).at(0) == 'M') {
                    ym++;
                }
            }
            for (int l = current->x;
                 l != next->x;
                 current->x > next->x ? l-- : l++) {// check crossing m on x
                if (convertedLines.at(current->y).at(l) == 'M') {
                    xm++;
                }
            }
            // dx/dy
            int dx = abs(next->x - current->x) - xm;
            int dy = abs(next->y - current->y) - ym;
            sum += dx + dy + (xm * factor) + (ym * factor);
        }
    }

    std::cout << sum << std::endl;
}

int main() {
    partOne();
    partTwo();
    return 0;
}
