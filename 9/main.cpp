#include "lordgasmic.h"
#include <iostream>
#include <algorithm>

struct Env {
    std::string fileName;
};

//Env env{"/home/lordgasmic/workspace/AoC-2023/9/input.1.test.txt"};
Env env {"/home/lordgasmic/workspace/AoC-2023/9/input.txt"};

void loadDifference(std::vector<std::vector<long>> &differences, std::vector<std::string> &environmentalData) {
    std::vector<long> difference;
    for (int i = 0; i < environmentalData.size(); i++) {
        int j = i + 1;

        if (j == environmentalData.size()) {
            break;
        }

        long first = std::stol(environmentalData[i]);
        long second = std::stol(environmentalData[j]);

        difference.push_back(second - first);
    }

    differences.push_back(difference);
}

void loadDifference(std::vector<std::vector<long>> &differences, std::vector<long> &environmentalData) {
    std::vector<long> difference;
    for (int i = 0; i < environmentalData.size(); i++) {
        int j = i + 1;

        if (j == environmentalData.size()) {
            break;
        }

        long first = environmentalData[i];
        long second = environmentalData[j];

        difference.push_back(second - first);
    }

    differences.push_back(difference);
}

void partOne() {
    std::vector<std::string> lines;
    lordgasmic::readFile(env.fileName, lines);

    long sum{0};

    for (auto line: lines) {
        std::vector<std::string> environmentalData;
        lordgasmic::split(line, environmentalData, ' ');

        std::vector<std::vector<long>> differences;
        loadDifference(differences, environmentalData);

        bool allZeros{false};
        do {
            std::vector<long> difference = differences[differences.size() - 1];
            auto count = std::count(difference.begin(), difference.end(), 0);
            if (count == difference.size()) {
                allZeros = true;
            }
            else {
                loadDifference(differences, difference);
            }
        } while (!allZeros);

        // walk differences
        // last value of last difference PLUS last value of (last difference-1) = difference -2 predicted value
        long deltaPredicted{0};
        for (auto it = differences.end() - 1; it != differences.begin(); it--) {
            auto it1 = it - 1;

            auto dIt0 = deltaPredicted;
            auto dIt1 = it1->end() - 1;
            deltaPredicted = dIt0 + *dIt1;
        }

        auto predictedValue = deltaPredicted + std::stol(*(environmentalData.end() - 1));
//        std::cout << "predicted value: " << predictedValue << std::endl;
        sum += predictedValue;
    }

    std::cout << "part one output: " << sum << std::endl;
}

void partTwo() {
    std::vector<std::string> lines;
    lordgasmic::readFile(env.fileName, lines);

    long sum{0};

    for (auto line: lines) {
        std::vector<std::string> environmentalData;
        lordgasmic::split(line, environmentalData, ' ');

        std::vector<std::vector<long>> differences;
        loadDifference(differences, environmentalData);

        bool allZeros{false};
        do {
            std::vector<long> difference = differences[differences.size() - 1];
            auto count = std::count(difference.begin(), difference.end(), 0);
            if (count == difference.size()) {
                allZeros = true;
            }
            else {
                loadDifference(differences, difference);
            }
        } while (!allZeros);

        // walk differences
        long preDeltaPredicted{0};
        for (auto it = differences.end() - 1; it != differences.begin(); it--) {
            auto it1 = it - 1;

            auto dIt0 = preDeltaPredicted;
            auto dIt1 = it1->begin();
            preDeltaPredicted = *dIt1 - dIt0;
        }

        auto predictedValue =  std::stol(*(environmentalData.begin())) - preDeltaPredicted;
        std::cout << "predicted value: " << predictedValue << std::endl;
        sum += predictedValue;
    }

    std::cout << "part two output: " << sum << std::endl;
}

int main() {
    partOne();
    partTwo();
    return 0;
}
