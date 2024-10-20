#include "console.hpp"

void term::log(const std::string& message, cause log_cause) {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::string output; 
    switch (log_cause) {
    case cause::error:
        output += "[E] ";
        output += "<" + std::to_string(now->tm_hour) + ':' + std::to_string(now->tm_min) + "> ";
        output += message;
        std::cerr << output << "\n";
        break;
    case cause::info:
        output += "[I] ";
        output += "<" + std::to_string(now->tm_hour) + ':' + std::to_string(now->tm_min) + "> ";
        output += message;
        std::cout << output << "\n";
        break;
    case cause::warning:
        output += "[W] ";
        output += "<" + std::to_string(now->tm_hour) + ':' + std::to_string(now->tm_min) + "> ";
        output += message;
        std::cerr << output << "\n";
        break;
    default:
        break;
    }

    
}