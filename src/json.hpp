#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

nlohmann::json json_loadf(const std::string& path) {
    nlohmann::json data;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "[E] <utils> file can't be opened\n";
        return data;
    }
    file >> data; 
    return data;
}