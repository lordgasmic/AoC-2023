#include "lordgasmic.h"
#include <iostream>

struct Env {
    std::string fileName;
};

//Env env {"/home/lordgasmic/workspace/AoC-2023/6/input.test.txt"};
Env env{"/home/lordgasmic/workspace/AoC-2023/6/input.txt"};

void partOne() {
    std::vector<std::string> lines;
    lordgasmic::readFile(env.fileName, lines);

    long sum{0};

    std::string times = lines.at(0).substr(5);
    std::string distances = lines.at(1).substr(9);
    std::vector<std::string> timeVector;
    std::vector<std::string> distanceVector;
    lordgasmic::split(times, timeVector);
    lordgasmic::split(distances, distanceVector);

    for (int i = 0; i < timeVector.size(); i++) {
        int waysToBeat{0};
        int time = std::stoi(timeVector.at(i));
        int distance = std::stoi(distanceVector.at(i));

        for (int j = 1; j < time; j++) {
            auto runDuration = time - j;
            auto distanceTraveled = runDuration * j;

            if (distance < distanceTraveled) {
                waysToBeat++;
            }
        }

        if (sum == 0) {
            sum = waysToBeat;
        }
        else {
            sum = sum * waysToBeat;
        }
    }

    std::cout << "margin of error: " << sum << std::endl;
}

void partTwo() {
    std::vector<std::string> lines;
    lordgasmic::readFile(env.fileName, lines);

    long sum{0};

    std::string times = lines.at(0).substr(5);
    std::string distances = lines.at(1).substr(9);
    std::vector<std::string> timeVector;
    std::vector<std::string> distanceVector;
    lordgasmic::split(times, timeVector);
    lordgasmic::split(distances, distanceVector);

    std::string totalTime;
    for (auto &str: timeVector) {
        totalTime.append(str);
    }

    std::string totalDistance;
    for (auto &dist: distanceVector) {
        totalDistance.append(dist);
    }

    long waysToBeat{0};
    long time = std::stol(totalTime);
    long distance = std::stol(totalDistance);

    for (int j = 1; j < time; j++) {
        auto runDuration = time - j;
        auto distanceTravled = runDuration * j;

        if (distance < distanceTravled) {
            waysToBeat++;
        }
    }

    sum = waysToBeat;

    std::cout << "margin of error: " << sum << std::endl;
}

int main() {
    partOne();
    partTwo();
    return 0;
}
