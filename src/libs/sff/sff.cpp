#include "sff.h" 
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

void sff::loadFile(const std::string& filename, std::map<std::string, std::string>& data) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string pair;

        while (std::getline(iss, pair, ';')) {
            if (pair.empty()) continue;

            size_t pos = pair.find(':');
            if (pos != std::string::npos) {
                std::string key = pair.substr(0, pos);
                std::string value = pair.substr(pos + 1);

                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t\""));
                value.erase(value.find_last_not_of(" \t\"") + 1);

                data[key] = value;
            }
        }
    }
}

void sff::saveFile(const std::string& filename, const std::map<std::string, std::string>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& pair : data) {
        file << pair.first << ": \"" << pair.second << "\";\n";
    }
}
