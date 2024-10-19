
#include <filesystem>

#include "console.hpp"
#include "libs/sff/sff.h"
#include "global_variables.hpp"
#include "main.hpp"


int main(int argc, char* argv[]) {


    console.log("Minecraft Texture Pack Converter To Content Pack is Started!",cause::info);
    cm->loadFile("config.sff",cdata);
    if (std::filesystem::exists(cdata["content_pack_path"])) {
        std::filesystem::remove_all(cdata["content_pack_path"]);
    }
    if (cdata["content_pack_path"] != "") {
        std::filesystem::create_directories(cdata["content_pack_path"]+"/textures/blocks");
    }
    
    console.log("preparing to load texture pack info",cause::info);
    //cm->printData(cdata);
    mcpack_getinfo(cdata["texture_pack_path"]+"/pack.mcmeta");
    console.log("texture pack info is loaded",cause::info);
    console.log("content pack folder is created",cause::info);
    if (cdata["content_pack_path"] != "") 
        save_package(cdata["content_pack_name"],cdata["content_pack_path"],description);
    console.log("package.json file is created and writed",cause::info);
    
    if (std::filesystem::exists(cdata["texture_pack_path"] + "/pack.png")) {
        if (std::filesystem::exists(cdata["content_pack_path"] + "/icon.png")) 
            std::filesystem::remove(cdata["content_pack_path"] + "/icon.png");
        std::filesystem::copy_file(cdata["texture_pack_path"] + "/pack.png",cdata["content_pack_path"] + "/icon.png");
    }
    console.log("icon file is created",cause::info);
    console.log("preparing to converting",cause::info);
    converting_textures();
    console.log("texture pack to content pack successfully converted!",cause::info);
    //pack.mcmeta
    return 0;
}
