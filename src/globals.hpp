#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <string>
#include <nlohmann/json.hpp>
#include "console.hpp"
#include "libs/sff/sff.h"
#include <map>

extern std::string description;
extern std::string pack_format;
extern std::map<std::string, std::string> cdata;    

extern sff *cm;
extern term console;
#endif 