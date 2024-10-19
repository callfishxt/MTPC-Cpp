#include <map>
#include <string>

#include "libs/sff/sff.h"
#include "console.hpp"

std::map<std::string, std::string> cdata;
std::string pack_format;
std::string description = "A Converted Minecraft Texture Pack"; 
term console;
sff *cm = new sff(); 