#include <iostream>
#include <fstream>
#include <string>
#include <regex>

std::string lookupTable(std::string word) {
    std::string one{"one"};
    std::string two{"two"};
    std::string three{"three"};
    std::string four{"four"};
    std::string five{"five"};
    std::string six{"six"};
    std::string seven{"seven"};
    std::string eight{"eight"};
    std::string nine{"nine"};
    if (one == word)  {
        return "1";
    }
    if (two == word) {
        return "2";
    }
    if (three == word) {
        return "3";
    }
    if (four == word) {
        return "4";
    }
    if (five == word) {
        return "5";
    }
    if (six == word) {
        return "6";
    }
    if (seven == word) {
        return "7";
    }
    if (eight == word) {
        return "8";
    }
    if (nine == word) {
        return "9";
    }

    return "-1";
}

void partOne( ) {
    long sum{0};
    std::regex e("\\d");

    std::ifstream infile;
    infile.open("/home/lordgasmic/workspace/AoC-2023/1/input.txt");
    if (infile.is_open()) {
        std::string str;
        while (std::getline(infile, str)) {
            char firstDigit{-1};
            char lastDigit{-1};
            std::cmatch cm;
            for (int i{0}; i <  str.length(); i++) {
                std::string single = str.substr(i,1);
                if (std::regex_match(single, e)) {
                    firstDigit = str.at(i) ;
                    break;
                }
            }
            for (int i{static_cast<int>(str.length() - 1)}; i >=  0; i--) {
                std::string single = str.substr(i,1);
                if (std::regex_match(single, e)) {
                    lastDigit = str.at(i) ;
                    break;
                }
            }
            std::string value;
            value += firstDigit ;
            value += lastDigit;

            sum = sum + std::stoi(value);
        }
        infile.close();
    }
    std::cout << "part one sum is: " << sum << std::endl;
}

void partTwo( ) {
    long sum{0};
    std::regex matchDigit("\\d");
    std::regex matchWord("(one|two|three|four|five|six|seven|eight|nine)");

    std::ifstream infile;
    infile.open("/home/lordgasmic/workspace/AoC-2023/1/input.txt");
    if (infile.is_open()) {
        std::string str;
        while (std::getline(infile, str)) {
            std::string numbers[100];
            int numberIndex = 0;
            std::string test;
            for (int i = 0; i < str.length(); i++) {
                std::string single = str.substr(i,1);
                if (std::regex_match(single, matchDigit)) {
                    numbers[numberIndex] = single;
                    numberIndex++;
                    test = "";
                    continue;
                }

                test += str.at(i);
                std::smatch match;
                if (std::regex_search(test,match,matchWord)) {
                    numbers[numberIndex] = lookupTable( match[0]);
                    numberIndex++;
                    test = single;
                }
            }

            std::string value;
            value += numbers[0] ;
            value += numbers[numberIndex-1];

            sum = sum + std::stoi(value);
        }
        infile.close();
    }
    std::cout << "part two sum is: " << sum << std::endl;
}

int main() {
    partOne();
    partTwo();
    return 0;
}
