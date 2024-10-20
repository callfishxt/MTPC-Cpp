#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>
#include <ctime>
#include <iostream>

enum class cause { info, error, warning };

class term {
public:
    void log(const std::string& message, cause log_cause);
};

#endif 