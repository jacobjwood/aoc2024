#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "helpers.hpp"

int passline_pt2(std::string line) {
    int linetot = 0;
    int lptr = 0;
    int rptr = line.length();
    std::unordered_map<std::string, int> string_to_int = {
        {"1", 1},
        {"2", 2},
        {"3", 3},
        {"4", 4},
        {"5", 5},
        {"6", 6},
        {"7", 7},
        {"8", 8},
        {"9", 9},
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };

    std::string lcache = "";
    std::string rcache = "";

    while ((lptr < line.length()) && (rptr >= 0)) {
        // std::cout << lptr << " " << rptr << std::endl;
        if (!std::isdigit(line[lptr])) {
            lcache += line.at(lptr);
            lptr++;
        }

        if (!std::isdigit(line[rptr])) {
            rcache = line.at(rptr) + rcache;
            rptr--;
        }

        for (auto& key: string_to_int) {
            std::cout << string_to_int.find(key) << std::endl;
        }
    }

    return 10 * std::stoi(line.substr(lptr, 1)) + std::stoi(line.substr(rptr, 1));
}

int passline_pt1(std::string line) {
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

int part1(std::string input) {
    int pt1 = 0;
    std::istringstream inputstream(input);
    for (std::string line; std::getline(inputstream, line); ) {
        pt1 += passline_pt1(line);
    }
    return pt1;
}

int main() {
    std::string input = helpers::read_input("day1/input.txt");
    std::cout << input << std::endl;

    std::cout << "Part 1: " << part1(input) << std::endl;
    return 0;
}
