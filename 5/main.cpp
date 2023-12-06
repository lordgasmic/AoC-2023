#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <regex>

class Env {
public:
    std::string fileName{};
    std::map<long,long> *lookupTable(std::string &line);
    std::map<long, long>* getSeedSoilMap() {
        return seedSoilMap;
    }
    std::map<long, long>* getSoilFertilizerMap() {
        return soilFertilizerMap;
    }
    std::map<long, long>* getFertilizerWaterMap() {
        return fertilizerWaterMap;
    }
    std::map<long, long>* getWaterLightMap() {
        return waterLightMap;
    }
    std::map<long, long>* getLightTemperatureMap() {
        return lightTemperatureMap;
    }
    std::map<long, long>* getTemperatureHumidityMap() {
        return temperatureHumidityMap;
    }
    std::map<long, long>* getHumidityLocationMap() {
        return humidityLocationMap;
    }
private:
    std::map<long, long> *seedSoilMap = new std::map<long,long>();
    std::map<long, long> *soilFertilizerMap= new std::map<long,long>();
    std::map<long, long> *fertilizerWaterMap= new std::map<long,long>();
    std::map<long, long> *waterLightMap= new std::map<long,long>();
    std::map<long, long> *lightTemperatureMap= new std::map<long,long>();
    std::map<long, long> *temperatureHumidityMap= new std::map<long,long>();
    std::map<long, long> *humidityLocationMap= new std::map<long,long>();
};

std::regex match {"[stlhwf]"};

Env *env = new Env();
//Env env {"/home/lordgasmic/workspace/AoC-2023/5/input.txt"};

std::map<long,long>* Env::lookupTable(std::string &line) {
    if ("seed-to-soil map:" == line) {
        return this->seedSoilMap;
    }
    if ("soil-to-fertilizer map:" == line) {
        return  this->soilFertilizerMap;
    }
    if ("fertilizer-to-water map:" == line) {
        return this->fertilizerWaterMap;
    }
    if ("water-to-light map:" == line) {
        return this->waterLightMap;
    }
    if ("light-to-temperature map:" == line) {
        return this->lightTemperatureMap;
    }
    if ("temperature-to-humidity map:" == line) {
        return this->temperatureHumidityMap;
    }
    if ("humidity-to-location map:" == line) {
        return this->humidityLocationMap;
    }
}

long getValueOrElse(std::map<long,long> *map, long key) {
    if (map->find(key) == map->end()){
        return key;
    }
    else {
        return map->at(key);
    }
}

long getLocationFromSeed(long &seed) {
    auto chain = getValueOrElse(env->getSeedSoilMap(), seed);
    chain = getValueOrElse(env->getSoilFertilizerMap(), chain);
    chain = getValueOrElse(env->getFertilizerWaterMap(), chain);
    chain = getValueOrElse(env->getWaterLightMap(), chain);
    chain = getValueOrElse(env->getLightTemperatureMap(), chain);
    chain = getValueOrElse(env->getTemperatureHumidityMap(), chain);
    return getValueOrElse(env->getHumidityLocationMap(), chain);
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

void readFile(std::vector<std::string> &lines, Env *env) {
    std::ifstream infile;
    infile.open(env->fileName);
    if (infile.is_open()) {
        std::string str;
        while (std::getline(infile, str)) {
            lines.insert(lines.end(), str);
        }
        infile.close();
    }
}

void partOne() {
//    env->fileName = "/home/lordgasmic/workspace/AoC-2023/5/input.test.txt";
    env->fileName = "/home/lordgasmic/workspace/AoC-2023/5/input.txt";

    std::vector<std::string> lines;
    readFile(lines, env);

    std::vector<std::string> seeds;
    std::string seedLine = lines.at(0);
    seedLine = seedLine.substr(7);
    split(seedLine, seeds);

    std::map<long, long> *lookupMap;
    for (int i = 2; i < lines.size(); i++) {
        std::string line = lines.at(i);
        if (line.empty()) {
            continue;
        }

        std::string single = line.substr(0,1);
        if (std::regex_match(single, match)) {
            lookupMap = env->lookupTable(line );
            std::cout << line<< std::endl;
            continue;
        }

        std::vector<std::string> values;
        split(line, values);

        long destination = std::stol(values[0]);
        long source = std::stol(values[1]);
        long range = std::stol(values[2]);

        for (long j = 0; j < range; j++){
            lookupMap->insert(std::pair<long,long>(source, destination));
            source++;
            destination++;
        }
    }

    long location {env->getHumidityLocationMap()->begin()->first};

    for (std::string s: seeds) {
        auto seed = std::stol(s);
        auto tempVal = getLocationFromSeed(seed);

        std::cout << "seed: " << seed << ", loc: " << tempVal << std::endl;

        if (tempVal < location) {
            location = tempVal;
        }
    }

    std::cout << "smallest location: " << location << std::endl;
}

int main() {
    partOne();
    return 0;
}
