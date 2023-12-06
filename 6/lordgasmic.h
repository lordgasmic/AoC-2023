//
// Created by lordgasmic on 12/6/23.
//

#ifndef INC_6_LORDGASMIC_H
#define INC_6_LORDGASMIC_H

#include <vector>
#include <fstream>

namespace lordgasmic {
    void readFile(std::string &fileName, std::vector<std::string> &lines) {
        std::ifstream infile;
        infile.open(fileName);
        if (infile.is_open()) {
            std::string str;
            while (std::getline(infile, str)) {
                lines.insert(lines.end(), str);
            }
            infile.close();
        }
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
}
#endif //INC_6_LORDGASMIC_H
