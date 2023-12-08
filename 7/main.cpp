#include "lordgasmic.h"
#include <iostream>
#include <map>
#include <algorithm>

enum HandType {
    high = 0,
    pair = 1,
    twoPair = 2,
    threeOfAKind = 3,
    full = 4,
    fourOfAKind = 5,
    fiveOfAKind = 6
};

enum CardType {
   two,three,four,five,six,seven,eight,nine, T, J, Q, K, A
};

static std::unordered_map<char, CardType> const cardTable = {
        {'2', CardType::two},
        {'3', CardType::three},
        {'4', CardType::four},
        {'5', CardType::five},
        {'6', CardType::six},
        {'7', CardType::seven},
        {'8', CardType::eight},
        {'9', CardType::nine},
        {'T', CardType::T},
        {'J', CardType::J},
        {'Q', CardType::Q},
        {'K', CardType::K},
        {'A', CardType::A}
};

struct Hand {
    std::string hand;
    long bet;
    HandType handType;

    bool operator<(const Hand &h) const {
        if (handType == h.handType) {
            for (int i = 0; i < 5; i++){
                if (hand.at(i) == h.hand.at(i)) {
                    continue;
                }

                auto lhs = cardTable.find(hand.at(i));
                auto rhs = cardTable.find(h.hand.at(i));
                return lhs->second < rhs->second;
            }
        }
        return (handType < h.handType);
    }

    bool operator()(Hand *lhs, Hand *rhs) const {
        return (*lhs) < (*rhs);
    }
};

HandType parseHand(std::string &hand) {
    std::map<char, int> handMap;
    for (char c: hand) {
        int i{0};
        if (handMap.count(c)) {
            i = handMap[c];
        }
        i++;
        handMap[c] = i;
    }

    if (handMap.size() == 1) {
        return fiveOfAKind;
    }

    if (handMap.size() == 5) {
        return high;
    }

    if (handMap.size() == 4) {
        return pair;
    }

    for (auto it = handMap.begin(); it != handMap.end(); ++it) {
        if (it->second == 4) {
            return fourOfAKind;
        }
        if (it->second == 3 && handMap.size() == 3) {
            return threeOfAKind;
        }
        if (it->second == 2 && handMap.size() == 3) {
            return twoPair;
        }
        if (it->second == 3 && handMap.size() == 2) {
            return full;
        }
    }
}



struct Env {
    std::string fileName;
};

//Env env{"/home/lordgasmic/workspace/AoC-2023/7/input.test.txt"};
Env env {"/home/lordgasmic/workspace/AoC-2023/7/input.txt"};

void partOne() {
    std::vector<std::string> lines;
    lordgasmic::readFile(env.fileName, lines);

    std::vector<Hand *> hands;
    for (std::string line: lines) {
        std::vector<std::string> parsedLine;
        lordgasmic::split(line, parsedLine);

        Hand *hand = new Hand();
        hand->hand = parsedLine[0];
        hand->bet = std::stol(parsedLine[1]);
        hand->handType = parseHand(hand->hand);

        hands.insert(hands.end(), hand);
    }

    std::sort(hands.begin(), hands.end(), Hand());

    long sum{0};
    int i{1};
    for (Hand *h : hands) {
        sum += (h->bet * i);
        i++;
    }

    std::cout << "part one winnings: " << sum << std::endl;
}

void partTwo() {
    std::vector<std::string> lines;
    lordgasmic::readFile(env.fileName, lines);

    std::vector<Hand *> hands;
    for (std::string line: lines) {
        std::vector<std::string> parsedLine;
        lordgasmic::split(line, parsedLine);

        Hand *hand = new Hand();
        hand->hand = parsedLine[0];
        hand->bet = std::stol(parsedLine[1]);
        hand->handType = parseHand(hand->hand);

        hands.insert(hands.end(), hand);
    }

    std::sort(hands.begin(), hands.end(), Hand());

    long sum{0};
    int i{1};
    for (Hand *h : hands) {
        sum += (h->bet * i);
        i++;
    }

    std::cout << "part two winnings: " << sum << std::endl;
}

int main() {
    partOne();
    partTwo()
    return 0;
}
