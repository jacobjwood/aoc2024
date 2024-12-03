#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <regex>
#include <string>

int part1(std::string input) {
    std::regex pattern("mul\\([0-9]+,[0-9]+\\)");
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto words_end = std::sregex_iterator();

    int res = 0;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        auto split = helpers::split(match.str(), ',');
        res += std::stoi(split[0].substr(4, split[0].length() - 4)) * std::stoi(split[1].substr(0, split[1].length() - 1));

    }
    return res;
}

int part2(std::string input) {
    std::regex pattern("mul\\([0-9]+,[0-9]+\\)|do\\(\\)|don't\\(\\)");
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto words_end = std::sregex_iterator();

    int res = 0;
    int do_bool = 1;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        if (match.str() == "do()") {
            do_bool = 1;
        } else if (match.str() == "don't()") {
            do_bool = 0;
        } else {
            auto split = helpers::split(match.str(), ',');
            res += do_bool * (std::stoi(split[0].substr(4, split[0].length() - 4)) * std::stoi(split[1].substr(0, split[1].length() - 1)));
        }
    }
    return res;
}

int main() {
    std::string input = helpers::read_input("day3/input.txt");
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}
