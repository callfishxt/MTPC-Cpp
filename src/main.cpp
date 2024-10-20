#include "main.hpp"
#include "globals.hpp"

int main(int argc, char* argv[]) {
    std::string config_name = "config.sff";
    int required_args = 2;

    if (argc < 2+1) { 
        std::cerr << "Error: insufficient arguments. Expected " 
                  << 2 << ", but received " << argc - 1 << ".\n";
        std::cerr << "Usage: ./mtpc -c \"config.sff\"" << std::endl;
        return 1; 
    } else if (argv[1] == "-c" or "--config") {
        if (std::filesystem::exists(argv[2])) {
            config_name = argv[2];
        } else {
            console.log("Configuration file is not exists!",cause::error);
            return 1;
        }
        
    } else {
        console.log("Unexpected arguments.",cause::error);
        return 1;
    }
    

    console.log("Minecraft Texture Pack Converter To Content Pack is Started!", cause::info);
    cm->loadFile(config_name, cdata);
    if (std::filesystem::exists(cdata["content_pack_path"])) {
        std::filesystem::remove_all(cdata["content_pack_path"]);
    }
    if (cdata["content_pack_path"] != "") {
        std::filesystem::create_directories(cdata["content_pack_path"] + "/textures/blocks");
    }
    
    console.log("preparing to load texture pack info", cause::info);
    mcpack_getinfo(cdata["texture_pack_path"] + "/pack.mcmeta");
    console.log("texture pack info is loaded", cause::info);
    console.log("content pack folder is created", cause::info);
    if (cdata["content_pack_path"] != "") 
        save_pkg(cdata["content_pack_name"], cdata["content_pack_path"], description);
    console.log("package.json file is created and writed", cause::info);
    
    if (std::filesystem::exists(cdata["texture_pack_path"] + "/pack.png")) {
        if (std::filesystem::exists(cdata["content_pack_path"] + "/icon.png")) 
            std::filesystem::remove(cdata["content_pack_path"] + "/icon.png");
        std::filesystem::copy_file(cdata["texture_pack_path"] + "/pack.png", cdata["content_pack_path"] + "/icon.png");
    }
    console.log("icon file is created", cause::info);
    console.log("preparing to converting", cause::info);
    converting_textures();
    console.log("texture pack to content pack successfully converted!", cause::info);
    return 0;
}