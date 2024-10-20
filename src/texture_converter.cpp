#include "texture_converter.hpp"
#include "globals.hpp"

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
    nlohmann::json data = json_loadf("packs.json");

    if (std::filesystem::exists(cdata["texture_pack_path"] + "/assets/minecraft/textures/block")) {
        path_to_blocks_tp = cdata["texture_pack_path"] + "/assets/minecraft/textures/block/";
    } else if (std::filesystem::exists(cdata["texture_pack_path"] + "/assets/minecraft/textures/blocks")) {
        path_to_blocks_tp = cdata["texture_pack_path"] + "/assets/minecraft/textures/blocks/";
    } else {
        std::cout << "[E] <utils> Texture path does not exist." << std::endl;
        return;
    }
    
    if (!data.contains(pack_format) || !data[pack_format].contains("blocks")) {
        std::cout << "[E] <utils> Invalid pack format or blocks not found in JSON." << std::endl;
        return;
    }
    
    for (const auto& key : data[pack_format]["blocks"].items()) {
        std::string vc_block_name = key.value().get<std::string>();
        std::string source_path = path_to_blocks_tp + key.key() + ".png";

        std::string dest_path = cdata["content_pack_path"] + "/textures/blocks/" + vc_block_name + ".png";

        convert_texture(source_path, dest_path);
        if (cdata["use_colorize"] == "true") {
            for (const auto& gray_key : data[pack_format]["gray_color"]) {
                if (gray_key.get<std::string>() == key.key()) {
                    colorize(source_path, dest_path);
                }
            }
        }
    }
}