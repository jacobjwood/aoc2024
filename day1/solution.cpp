#include <iostream>
#include <fstream>
#include <sstream>
#include "helpers.hpp"

int passline_pt1(std::string line) {
    std::cout << "hi " << line << std::endl;
    int lptr = 0;
    int rptr = line.length();
    while ((lptr < line.length()) && (rptr >= 0)) {
        // std::cout << lptr << " " << rptr << std::endl;
        if (!std::isdigit(line[lptr])) {
            lptr++;
        }

        if (!std::isdigit(line[rptr])) {
            rptr--;
        }

        if (std::isdigit(line[lptr]) && std::isdigit(line[rptr])) {
            break;
        }
    }

    return 10 * std::stoi(line.substr(lptr, 1)) + std::stoi(line.substr(rptr, 1));
}

int main() {
    std::string input = helpers::read_input("day1/input.txt");
    std::cout << input << std::endl;
    std::istringstream inputstream(input);

    int pt1 = 0;
    for (std::string line; std::getline(inputstream, line); ) {
        pt1 += passline_pt1(line);
    }
    std::cout << "Part 1: " << pt1 << std::endl;
    return 0;
}
