#include "console.hpp"

void term::log(const std::string& message, cause log_cause) {
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