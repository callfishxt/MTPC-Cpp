#include <string>
#include <cstring>
#include <ctime>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "libs/sff/sff.h"
#include "images.hpp"
#include <filesystem>
#include <map>

#include "json.hpp"





std::string replace_substring(std::string str, const std::string& oldSubstr, const std::string& newSubstr) {
    size_t pos = 0;
    while ((pos = str.find(oldSubstr, pos)) != std::string::npos) {
        str.replace(pos, oldSubstr.length(), newSubstr);
        pos += newSubstr.length();
    }
    return str;
}

