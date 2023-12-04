#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Env{
    int headerLength{};
    std::string fileName{};
    int winningCols{};
    int playCols{};
};

//Env env {7, "/home/lordgasmic/workspace/AoC-2023/4/input.test.txt", 5, 8};
Env env {9, "/home/lordgasmic/workspace/AoC-2023/4/input.txt",10,25};

void readFile(std::vector<std::string> &lines) {
    std::ifstream infile;
    infile.open(env.fileName);
    if (infile.is_open()) {
        std::string str;
        while (std::getline(infile, str)) {
            lines.insert(lines.end(), str);
        }
        infile.close();
    }
}

void parseNumbers(std::string &line, std::vector<int> &winningNumbers, std::vector<int> &playingNumbers) {
    auto temp = line.substr(env.headerLength);
    for (int i = 0; i< env.winningCols; i++) {
        auto num = temp.substr(i*3, 3);
        winningNumbers.insert(winningNumbers.end(), std::stoi(num));
    }
    for (int i = 0; i< env.playCols; i++) {
        int pipe = temp.find_first_of('|');
        auto num = temp.substr(pipe + 1 + (i*3), 3);
        playingNumbers.insert(playingNumbers.end(), std::stoi(num));
    }
}

void partOne() {
    long sum{0};
    std::vector<std::string> lines;
    readFile(lines);

    for(std::string &line : lines){
        std::vector<int> winningNumbers;
        std::vector<int> playingNumbers;
        parseNumbers(line, winningNumbers, playingNumbers);

        int matchedNumbers{0};
        for (int num : playingNumbers) {
            if (std::count(winningNumbers.begin(), winningNumbers.end(), num)){
                matchedNumbers++;
            }
        }
        if (matchedNumbers > 0){
            sum += pow(2, matchedNumbers -1);
        }
    }

    std::cout << "part one sum is: " << sum << std::endl;
}

void lolsRecursion(std::vector<std::string> &lines, int pos, int &sum) {
    std::vector<int> winningNumbers;
    std::vector<int> playingNumbers;
    parseNumbers(lines.at(pos), winningNumbers, playingNumbers);

    sum++;
    int matchedNumbers{0};
    for (int num : playingNumbers) {
        if (std::count(winningNumbers.begin(), winningNumbers.end(), num)){
            matchedNumbers++;
            lolsRecursion(lines, pos + matchedNumbers, sum);
        }
    }
}

void partTwo() {
    int sum{0};
    std::vector<std::string> lines;
    readFile(lines);

    for(int i =  0; i < lines.size(); i++){
        lolsRecursion(lines, i, sum);
    }

    std::cout << "part two sum is: " << sum << std::endl;
}

int main() {
    partOne();
    partTwo();

    return 0;
}
