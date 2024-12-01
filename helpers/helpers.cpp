#include <fstream>
#include <sstream> 
#include <string>
#include <iterator>
#include <vector>

namespace helpers {

std::string read_input(std::string uri) {
    std::ifstream input_stream{ uri };
    std::stringstream buffer;
    buffer << input_stream.rdbuf();
    std::string input;
    input = buffer.str();
    return input;
}

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

template <typename Out>
void split_nonempty(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        if (!item.empty()) {
            *result++ = item;
        }
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    // Generic back inserter used. Compiler infers type
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::vector<std::string> split_nonempty(const std::string &s, char delim) {
    std::vector<std::string> elems;
    // Generic back inserter used. Compiler infers type
    split_nonempty(s, delim, std::back_inserter(elems));
    return elems;
}

}