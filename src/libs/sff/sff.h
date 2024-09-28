#ifndef SFF_H
#define SFF_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

class sff {
public:
    void loadFile(const std::string& filename, std::map<std::string, std::string>& data);
    void saveFile(const std::string& filename, const std::map<std::string, std::string>& data);
    void printData(const std::map<std::string, std::string>& data) {
        for (const auto& pair : data) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

};


#endif
