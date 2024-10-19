#include <string>
#include <cstring>
#include <ctime>
#include <iostream>

#include <map>


#include "utils.hpp"
#include "texture_converter.hpp"



void save_package(const std::string& name,  std::string path, std::string description) {
    std::ofstream file(path + "/package.json");
    
    if (!file.is_open()) {
        std::cout << "[E] <utils> file can't be opened\n";
        return;
    }

    for (char& c : path) {
        if (c == '\\') {
            c = '/';
        }
    }
    std::string id = path.substr(path.find_last_of("/") + 1);
    description = replace_substring(description,"\n","");
    
    file << "{\n";
    file << "  \"id\": \"" << id << "\",\n";
    file << "  \"title\": \"" << name << "\",\n";
    file << "  \"description\": \"" << description << "\"\n";
    file << "}\n";

    file.close();
}


void mcpack_getinfo(const std::string& texture_pack_path) {
    nlohmann::json data = json_loadf(texture_pack_path);

    if (data.contains("pack")) {
        if (data["pack"].contains("description") && !data["pack"]["description"].is_null()) {
            description = data["pack"]["description"].get<std::string>();
        }
        if (data["pack"].contains("pack_format") && !data["pack"]["pack_format"].is_null()) {
            if (data["pack"]["pack_format"].is_number()) {
                pack_format = std::to_string(data["pack"]["pack_format"].get<int>());
            } else {
                pack_format = data["pack"]["pack_format"].get<std::string>();
            }
        }
    }
}


//Converting Textures: Start
