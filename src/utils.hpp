#include <string>
#include <cstring>
#include <ctime>
#include <iostream>
#include <json/json.h>
#include <fstream>
#include "libs/sff/sff.h"
#include "images.hpp"
#include <filesystem>
#include <map>

enum class cause { info, error, warning };

class console {
public:
    void log(const std::string& message, cause log_cause);
};

// Global Variables
std::map<std::string, std::string> cdata;
std::string pack_format;
std::string description = "A Converted Minecraft Texture Pack"; 
sff *cm = new sff;

//Functions
void console::log(const std::string& message, cause log_cause) {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::string output; 
    switch (log_cause) {
    case cause::error:
        output += "[E] ";
        break;
    case cause::info:
        output += "[I] ";
        break;
    case cause::warning:
        output += "[W] ";
        break;
    default:
        break;
    }

    output += "<" + std::to_string(now->tm_hour) + ':' + std::to_string(now->tm_min) + "> ";
    output += message;

    std::cout << output << "\n";
}

std::string replace_substring(std::string str, const std::string& oldSubstr, const std::string& newSubstr) {
    size_t pos = 0;
    while ((pos = str.find(oldSubstr, pos)) != std::string::npos) {
        str.replace(pos, oldSubstr.length(), newSubstr);
        pos += newSubstr.length();
    }
    return str;
}

void save_package(const std::string& name, const std::string& path, std::string description) {
    std::ofstream file(path + "/package.json");
    
    if (!file.is_open()) {
        std::cout << "[E] <utils> file can't be opened\n";
        return;
    }

    std::string id = path.substr(path.find_last_of("/\\") + 1);
    description = replace_substring(description,"\n","");
    
    file << "{\n";
    file << "  \"id\": \"" << id << "\",\n";
    file << "  \"title\": \"" << name << "\",\n";
    file << "  \"description\": \"" << description << "\"\n";
    file << "}\n";

    file.close();
}


Json::Value json_loadf(const std::string& path) {
    Json::Value data;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "[E] <utils> file can't be opened\n";
        return data;
    }
    file >> data; 
    return data;
}

void convert_texture(const std::string& from, const std::string& to) {
    std::cout << "[I] <utils> " << from.substr(from.find_last_of("/\\") + 1) << " is converting!" << std::endl;
    if (std::filesystem::exists(from)) {
        if (std::filesystem::exists(to)) 
            std::filesystem::remove(to);
        
        std::filesystem::copy(from, to);
        save_alpha_channel(to);
        std::cout << "[I] <utils> " << from.substr(from.find_last_of("/\\") + 1) << " successfully converted!" << std::endl;
    } else {
        std::cout << "[E] <utils> " << from.substr(from.find_last_of("/\\") + 1) << " file not found!" << std::endl;
    }
}

void converting_textures() {
    std::cout << "[I] <utils> convert function load\n";
    std::string path_to_blocks_tp;
    Json::Value data = json_loadf("packs.json");

        if (std::filesystem::exists(cdata["texture_pack_path"] + "/assets/minecraft/textures/block")) {
        path_to_blocks_tp = cdata["texture_pack_path"] + "/assets/minecraft/textures/block/";
    } else if (std::filesystem::exists(cdata["texture_pack_path"] + "/assets/minecraft/textures/blocks")) {
        path_to_blocks_tp = cdata["texture_pack_path"] + "/assets/minecraft/textures/blocks/";
    } else {
        std::cout << "[E] <utils> Texture path does not exist." << std::endl;
        return;
    }
    
    if (!data.isMember(pack_format) || !data[pack_format].isMember("blocks")) {
        std::cout << "[E] <utils> Invalid pack format or blocks not found in JSON." << std::endl;
        return;
    }
    
    for (const auto& key : data[pack_format]["blocks"].getMemberNames()) {
        std::string source_path = path_to_blocks_tp + key + ".png";
        std::string dest_path = cdata["content_pack_path"] + "/textures/blocks/" + data[pack_format]["blocks"][key].asString() + ".png";

        convert_texture(source_path, dest_path);
        if (cdata["use_colorize"] == "true") {
            for (int i=0;i<data[pack_format]["gray_color"].size();i++) {
                if (data[pack_format]["gray_color"][i] == key) {
                    colorize(source_path,dest_path);
                }
            }
        }
        
    }
        
    

    
}

void mcpack_getinfo(const std::string& texture_pack_path) {
    Json::Value data = json_loadf(texture_pack_path);

    if (data.isMember("pack")) {
        if (data["pack"].isMember("description") && !data["pack"]["description"].isNull()) {
            description = data["pack"]["description"].asString();
        }
        if (data["pack"].isMember("pack_format") && !data["pack"]["pack_format"].isNull()) {
            pack_format = data["pack"]["pack_format"].asString();
        }
    }
}

