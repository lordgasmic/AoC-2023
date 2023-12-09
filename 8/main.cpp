#include "lordgasmic.h"
#include <iostream>
#include <map>
#include <regex>

std::regex startingMatcher {"..A"};
std::regex endingMatcher {"..Z"};


struct Coords {
    std::string left;
    std::string right;

    Coords(std::string left, std::string right) {
        this->left = left;
        this->right = right;
    }
};


struct Env {
    std::string fileName;
};

long foo(std::string &directions,
         __gnu_cxx::__normal_iterator<char *, std::basic_string<char, std::char_traits<char>, std::allocator<char>>> &direction,
         std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, Coords *>> & iterator);

long long gcd(long long int a, long long int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long lcm(long a, long b)
{
    return (a / gcd(a, b)) * b;
}


std::map<std::string, Coords *> coordsMap;
std::vector<std::_Rb_tree_iterator<std::pair<const std::string, Coords *>>> validStartingPoints;

//Env env{"/home/lordgasmic/workspace/AoC-2023/8/input.1.test.txt"};
//Env env {"/home/lordgasmic/workspace/AoC-2023/8/input.2.test.txt"};
//Env env{"/home/lordgasmic/workspace/AoC-2023/8/input.part2.test.txt"};
Env env {"/home/lordgasmic/workspace/AoC-2023/8/input.txt"};

void partOne() {
    std::vector<std::string> lines;
    lordgasmic::readFile(env.fileName, lines);

    std::string directions = lines.at(0);
    lines.erase(lines.begin(), lines.begin() + 2);

    std::map<std::string, Coords *> coordsMap;

    for (const std::string &line: lines) {
        std::string starting = line.substr(0, 3);
        std::string left = line.substr(7, 3);
        std::string right = line.substr(12, 3);

        coordsMap[starting] = new Coords(left, right);
    }

    auto it = coordsMap.find("AAA");
    auto direction = directions.begin();

    int steps{0};
    bool atZZZ{false};
    do {
        if (direction == directions.end()) {
            direction = directions.begin();
        }

        if (it->first == "ZZZ") {
            atZZZ = true;
        }
        else {
            if ('R' == *direction) {
                it = coordsMap.find(it->second->right);
            }
            else {
                it = coordsMap.find(it->second->left);
            }
            direction++;
            steps++;
        }
    } while (!atZZZ);

    std::cout << "num steps: " << steps << std::endl;
}

void partTwo() {
    std::vector<std::string> lines;
    lordgasmic::readFile(env.fileName, lines);

    std::string directions = lines.at(0);
    lines.erase(lines.begin(), lines.begin() + 2);


    for (const std::string &line: lines) {
        std::string starting = line.substr(0, 3);
        std::string left = line.substr(7, 3);
        std::string right = line.substr(12, 3);

        coordsMap[starting] = new Coords(left, right);
    }

    auto direction = directions.begin();

    for (auto itr = coordsMap.begin(); itr != coordsMap.end(); itr++) {
        if (std::regex_match(itr->first, startingMatcher)) {
            validStartingPoints.push_back(itr);
        }
    }

    for (auto it : validStartingPoints) {
        long steps1 = foo(directions, direction, it);
        std::cout << "steps: " << steps1 << std::endl;
    }


//    auto steps = lcm(steps1, steps2);

//    std::cout << "num steps1: " << steps << std::endl;
}

long foo(std::string &directions,
         __gnu_cxx::__normal_iterator<char *, std::basic_string<char, std::char_traits<char>, std::allocator<char>>> &direction,
         std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, Coords *>> & it) {
    long steps{0};
    bool atZZZ{false};
    do {
        if (direction == directions.end()) {
            direction = directions.begin();
        }

        if ('R' == *direction) {
            it = coordsMap.find(it->second->right);
        }
        else {
            it = coordsMap.find(it->second->left);
        }
        validStartingPoints[0] = it;
        direction++;
        steps++;

        if (std::regex_match(it->first, endingMatcher)) {
            atZZZ = true;
        }
    } while (!atZZZ);

    return steps;
}

int main() {
//    partOne();
    partTwo();
    return 0;
}
