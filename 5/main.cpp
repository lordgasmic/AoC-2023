#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <regex>

struct CategoryMap {
    CategoryMap(long dest, long src, long rng) {
        this->destination = dest;
        this->source = src;
        this->range = rng;
    }

    long destination;
    long source;
    long range;
};

struct SeedMap {
    SeedMap(long start, long range) {
        this->start = start;
        this->range = range;
    }

    long start;
    long range;
};

std::vector<CategoryMap*> *seedSoilMap = new std::vector<CategoryMap*>;
std::vector<CategoryMap*> *soilFertilizerMap = new std::vector<CategoryMap*>;
std::vector<CategoryMap*> *fertilizerWaterMap = new std::vector<CategoryMap*>;
std::vector<CategoryMap*> *waterLightMap = new std::vector<CategoryMap*>;
std::vector<CategoryMap*> *lightTemperatureMap = new std::vector<CategoryMap*>;
std::vector<CategoryMap*> *temperatureHumidityMap = new std::vector<CategoryMap*>;
std::vector<CategoryMap*> *humidityLocationMap = new std::vector<CategoryMap*>;

std::vector<CategoryMap*> * lookupTable(std::string &line) {
    if ("seed-to-soil map:" == line) {
        return seedSoilMap;
    }
    if ("soil-to-fertilizer map:" == line) {
        return  soilFertilizerMap;
    }
    if ("fertilizer-to-water map:" == line) {
        return fertilizerWaterMap;
    }
    if ("water-to-light map:" == line) {
        return waterLightMap;
    }
    if ("light-to-temperature map:" == line) {
        return lightTemperatureMap;
    }
    if ("temperature-to-humidity map:" == line) {
        return temperatureHumidityMap;
    }
    if ("humidity-to-location map:" == line) {
        return humidityLocationMap;
    }

    return nullptr;
}

std::regex match {"[stlhwf]"};

struct Env {
    std::string fileName{};
};

//Env env {"/home/lordgasmic/workspace/AoC-2023/5/input.test.txt"};
Env env {"/home/lordgasmic/workspace/AoC-2023/5/input.txt"};

long getValueOrElse(std::vector<CategoryMap*> *categoryMap, long sourceKey) {
    for (auto map : *categoryMap) {
        long upperRange = map->source + map->range - 1;
        if (map->source <= sourceKey && sourceKey <= upperRange) {
            auto temp = sourceKey - map->source;
            return map->destination + temp;
        }
    }

    return sourceKey;
}

long getLocationFromSeed(long &seed) {
    auto chain = getValueOrElse(seedSoilMap, seed);
    chain = getValueOrElse(soilFertilizerMap, chain);
    chain = getValueOrElse(fertilizerWaterMap, chain);
    chain = getValueOrElse(waterLightMap, chain);
    chain = getValueOrElse(lightTemperatureMap, chain);
    chain = getValueOrElse(temperatureHumidityMap, chain);
    return getValueOrElse(humidityLocationMap, chain);
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

void partOne() {
    std::vector<std::string> lines;
    readFile(lines);

    std::vector<std::string> seeds;
    std::string seedLine = lines.at(0);
    seedLine = seedLine.substr(7);
    split(seedLine, seeds);

    std::vector<CategoryMap*> *lookupMap;
    for (int i = 2; i < lines.size(); i++) {
        std::string line = lines.at(i);
        if (line.empty()) {
            continue;
        }

        std::string single = line.substr(0,1);
        if (std::regex_match(single, match)) {
            lookupMap = lookupTable(line);
            std::cout << line<< std::endl;
            continue;
        }

        std::vector<std::string> values;
        split(line, values);

        long destination = std::stol(values[0]);
        long source = std::stol(values[1]);
        long range = std::stol(values[2]);

        auto map = new CategoryMap(destination, source, range);
        lookupMap->insert(lookupMap->end(), map);
    }

    long location {humidityLocationMap->at(0)->destination};

    for (const std::string& s: seeds) {
        auto seed = std::stol(s);
        auto tempVal = getLocationFromSeed(seed);

        if (tempVal < location) {
            location = tempVal;
        }
    }

    std::cout << "smallest location: " << location << std::endl;
}

void partTwo() {
    std::vector<std::string> lines;
    readFile(lines);

    std::vector<std::string> seeds;
    std::string seedLine = lines.at(0);
    seedLine = seedLine.substr(7);
    split(seedLine, seeds);

    auto *seedMap = new std::vector<SeedMap*>;
    for (int i = 0; i < seeds.size(); i++){
        auto src = std::stol(seeds.at(i));
        i++;
        auto rng = std::stol(seeds.at(i));
        seedMap->insert(seedMap->end(), new SeedMap(src,rng));
    }

    std::vector<CategoryMap*> *lookupMap;
    for (int i = 2; i < lines.size(); i++) {
        std::string line = lines.at(i);
        if (line.empty()) {
            continue;
        }

        std::string single = line.substr(0,1);
        if (std::regex_match(single, match)) {
            lookupMap = lookupTable(line);
            std::cout << line<< std::endl;
            continue;
        }

        std::vector<std::string> values;
        split(line, values);

        long destination = std::stol(values[0]);
        long source = std::stol(values[1]);
        long range = std::stol(values[2]);

        auto map = new CategoryMap(destination, source, range);
        lookupMap->insert(lookupMap->end(), map);
    }

    long location {humidityLocationMap->at(0)->destination};

    for (auto & s: *seedMap) {
        for (int i = 0; i < s->range; i++){
            auto seed = s->start + i;
            auto tempVal = getLocationFromSeed(seed);

//            std::cout << "seed: " << seed << ", loc: " << tempVal << std::endl;

            if (tempVal < location) {
                location = tempVal;
            }
        }

    }

    std::cout << "smallest location: " << location << std::endl;
}

int main() {
//    partOne();
    partTwo();

    return 0;
}
