#include "utils.hpp"

std::string replace_substring(std::string str, const std::string& oldSubstr, const std::string& newSubstr) {
    size_t pos = 0;
    while ((pos = str.find(oldSubstr, pos)) != std::string::npos) {
        str.replace(pos, oldSubstr.length(), newSubstr);
        pos += newSubstr.length();
    }
    return str;
}

nlohmann::json json_loadf(const std::string& path) {
    nlohmann::json data;
    std::ifstream file(path);
    
    if (!file.is_open()) {
        std::cerr << "[E] <utils> file can't be opened: " << path << "\n";
        return data;  
    }

    try {
        file >> data;  
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "[E] <utils> JSON parse error: " << e.what() << "\n";
        return data;  
    }

    return data;  
}