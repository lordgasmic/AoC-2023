#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

enum DataType {
    part, symbol
};

class LineData {
public:
    int m_position{};
    std::string m_value{};
    int m_lowerRange{};
    int m_upperRange{};
    DataType m_dataType{};
};

std::regex matchDigit("\\d");
std::regex matchDot("\\.");

const int NUM_LINES{140};

void comparePartVectors(std::vector<LineData *> &mainVector, std::vector<LineData *> &compareVector, int &sum) {
    for (auto currentPart: mainVector) {
        if (currentPart->m_dataType != symbol) {
            continue;
        }
        for (auto nextPart: compareVector) {
            if (nextPart->m_dataType == symbol) {
                continue; // only looking for parts
            }

            if (nextPart->m_lowerRange <= currentPart->m_position &&
                currentPart->m_position <= nextPart->m_upperRange) {
                sum += std::stoi(nextPart->m_value);
            }
        }
    }
}

void partOne() {
    int sum{0};
    std::vector<LineData *> parsedParts[NUM_LINES];
    int index{0};
    std::ifstream infile;
    infile.open("/home/lordgasmic/workspace/AoC-2023/3/input.txt");
    if (infile.is_open()) {
        std::string str;
        while (std::getline(infile, str)) {
            std::string accumulator;
            auto *lineData = new LineData();
            for (int i = 0; i < str.length(); i++) {
                std::string single = str.substr(i, 1);
                if (single == ".") {
                    if (accumulator.length() != 0) {
                        lineData->m_value = accumulator;
                        lineData->m_upperRange = i;
                        parsedParts[index].insert(parsedParts[index].end(), lineData);
                        accumulator = "";
                        lineData = new LineData();
                    }
                    continue;
                }
                if (std::regex_match(single, matchDigit)) {
                    if (accumulator.length() == 0) {
                        lineData->m_position = i;
                        lineData->m_dataType = part;
                        lineData->m_lowerRange = i - 1;
                    }
                    accumulator += single;
                }
                else {
                    if (accumulator.length() == 0) {
                        lineData->m_value = single;
                        lineData->m_position = i;
                        lineData->m_dataType = symbol;
                    }
                    else {
                        lineData->m_value = accumulator;
                        lineData->m_upperRange = i;
                        parsedParts[index].insert(parsedParts[index].end(), lineData);
                        accumulator = "";
                        lineData = new LineData();
                        lineData->m_value = single;
                        lineData->m_position = i;
                        lineData->m_dataType = symbol;
                    }
                    parsedParts[index].insert(parsedParts[index].end(), lineData);
                    lineData = new LineData();
                }
            }

            if (accumulator.length() != 0) {
                lineData->m_value = accumulator;
                lineData->m_upperRange = str.length() - accumulator.length() - 1;
                parsedParts[index].insert(parsedParts[index].end(), lineData);
                accumulator = "";
                lineData = new LineData();
            }

            index++;
        }
        infile.close();
    }

    index = 1;
    while (index < NUM_LINES - 1) {
        std::vector previous = parsedParts[index - 1];
        std::vector current = parsedParts[index];
        std::vector next = parsedParts[index + 1];

        // compare current to current
        for (int i = 0; i < current.size(); i++) {
            auto currentPart = current.at(i);
            if (currentPart->m_dataType == symbol) {
                LineData *nextPart = nullptr;
                LineData *previousPart = nullptr;
                if (i > 0) {
                    previousPart = current.at(i - 1);
                }
                if (i + 1 < current.size()) {
                    nextPart = current.at(i + 1);
                }

                if (nextPart && nextPart->m_lowerRange <= currentPart->m_position &&
                    currentPart->m_position <= nextPart->m_upperRange) {
                    sum += std::stoi(nextPart->m_value);
                }
                if (previousPart && previousPart->m_lowerRange <= currentPart->m_position &&
                    currentPart->m_position <= previousPart->m_upperRange) {
                    sum += std::stoi(previousPart->m_value);
                }
            }
        }
        // compare current to previous and next
        comparePartVectors(current, previous, sum);
        comparePartVectors(current, next, sum);

        index++;
    }

    std::cout << "part one sum: " << sum << std::endl;
}

void partTwo() {
    int sum{0};
    std::vector<LineData *> parsedParts[NUM_LINES];
    int index{0};
    std::ifstream infile;
    infile.open("/home/lordgasmic/workspace/AoC-2023/3/input.txt");
    if (infile.is_open()) {
        std::string str;
        while (std::getline(infile, str)) {
            std::string accumulator;
            auto *lineData = new LineData();
            for (int i = 0; i < str.length(); i++) {
                std::string single = str.substr(i, 1);
                if (single == ".") {
                    if (accumulator.length() != 0) {
                        lineData->m_value = accumulator;
                        lineData->m_upperRange = i;
                        parsedParts[index].insert(parsedParts[index].end(), lineData);
                        accumulator = "";
                        lineData = new LineData();
                    }
                    continue;
                }
                if (std::regex_match(single, matchDigit)) {
                    if (accumulator.length() == 0) {
                        lineData->m_position = i;
                        lineData->m_dataType = part;
                        lineData->m_lowerRange = i - 1;
                    }
                    accumulator += single;
                }
                else {
                    if (accumulator.length() == 0) {
                        lineData->m_value = single;
                        lineData->m_position = i;
                        lineData->m_dataType = symbol;
                    }
                    else {
                        lineData->m_value = accumulator;
                        lineData->m_upperRange = i;
                        parsedParts[index].insert(parsedParts[index].end(), lineData);
                        accumulator = "";
                        lineData = new LineData();
                        lineData->m_value = single;
                        lineData->m_position = i;
                        lineData->m_dataType = symbol;
                    }
                    parsedParts[index].insert(parsedParts[index].end(), lineData);
                    lineData = new LineData();
                }
            }

            if (accumulator.length() != 0) {
                lineData->m_value = accumulator;
                lineData->m_upperRange = str.length() - accumulator.length() - 1;
                parsedParts[index].insert(parsedParts[index].end(), lineData);
                accumulator = "";
                lineData = new LineData();
            }

            index++;
        }
        infile.close();
    }

    index = 1;
    while (index < NUM_LINES - 1) {
        std::vector top = parsedParts[index - 1];
        std::vector current = parsedParts[index];
        std::vector bottom = parsedParts[index + 1];

        // compare current to current
        for (int i = 0; i < current.size(); i++) {
            auto currentPart = current.at(i);
            if (currentPart->m_dataType == symbol && currentPart->m_value == "*") {
                std::vector<LineData*> adjacents;
                if (i > 0) {
                    auto temp = current.at(i - 1);
                    if (temp->m_upperRange == currentPart->m_position) {
                        adjacents.insert(adjacents.end(), temp);
                    }
                }
                if (i + 1 < current.size()) {
                    auto temp = current.at(i + 1);
                    if (currentPart->m_position == temp->m_lowerRange) {
                        adjacents.insert(adjacents.end(), temp);
                    }
                }

                for(LineData *searchPart : top){
                    if (searchPart->m_dataType == part && searchPart->m_lowerRange <= currentPart->m_position &&
                                                        currentPart->m_position <= searchPart->m_upperRange) {
                        adjacents.insert(adjacents.end(), searchPart);
                    }
                }
                for(LineData *searchPart : bottom){
                    if (searchPart->m_dataType == part && searchPart->m_lowerRange <= currentPart->m_position &&
                                                        currentPart->m_position <= searchPart->m_upperRange) {
                        adjacents.insert(adjacents.end(), searchPart);
                    }
                }

                if (adjacents.size() == 2) {
                    sum += (std::stoi(adjacents.at(0)->m_value) * std::stoi(adjacents.at(1)->m_value));
                }
            }
        }

        index++;
    }

    std::cout << "part two sum: " << sum << std::endl;
}

int main() {
//    partOne();
    partTwo();
    return 0;
}
//1517
