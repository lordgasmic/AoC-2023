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

//void partOne() {
//    int sum{0};
//    std::vector<std::string> lines;
//    std::ifstream infile;
//    infile.open("/home/lordgasmic/workspace/AoC-2023/3/input.txt");
//    if (infile.is_open()) {
//        std::string str;
//        while (std::getline(infile, str)) {
//            lines.insert(lines.end(), str);
//        }
//        infile.close();
//    }
//
//    for (int lineIndex = 1; lineIndex < lines.size(); lineIndex++) {
//        std::string previous = lines.at(lineIndex - 1);
//        std::string current = lines.at(lineIndex);
//
//        for (int i = 0; i < current.length(); i++) {
//            std::string single = current.substr(i, 1);
//            if (!std::regex_match(single, matchDigit) && !std::regex_match(single, matchDot)) {
//                // check TL TC TR (index - 1, i - 1)(index - 1, i)(index -1, i + 1)
//                // check L      R (index, i - 1) (index, i + 1)
//            }
//        }
//    }
//
//    std::cout << "part one sum: " << sum << std::endl;
//}

void partTwo() {

}

int main() {
    partOne();
    partTwo();
    return 0;
}
//1517
