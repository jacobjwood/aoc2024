#include <fstream>
#include <sstream> 

namespace helpers {

std::string read_input(std::string uri) {
    std::ifstream input_stream{ uri };
    std::stringstream buffer;
    buffer << input_stream.rdbuf();
    std::string input;
    input = buffer.str();
    return input;
}

}