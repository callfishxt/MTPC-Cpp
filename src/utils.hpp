#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>
#include <iostream>

#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

std::string replace_substring(std::string str, const std::string& oldSubstr, const std::string& newSubstr);
nlohmann::json json_loadf(const std::string& path);


#endif 