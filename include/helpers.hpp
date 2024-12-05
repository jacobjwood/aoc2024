#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>
#include <vector>

namespace helpers {
    std::string read_input(std::string uri);
    std::vector<std::string> split(const std::string &s, char delim);
    std::vector<std::string> split_nonempty(const std::string &s, char delim);
    std::vector<std::string> split(const std::string& s, const std::string& delim);
}

#endif