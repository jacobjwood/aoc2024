#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <sstream>

#include <unordered_map>
#include <unordered_set>

std::unordered_map<int, std::unordered_set<int>> get_dependencies(std::vector<std::string>& instructions) {
    std::unordered_map<int, std::unordered_set<int>> res;
    for (auto ins : instructions) {
        std::vector<std::string> before_after = helpers::split(ins, '|');
        int before = std::stoi(before_after[0]);
        int after = std::stoi(before_after[1]);

        auto t = res.find(after);
        // if ( t == res.end() ) {
        //     res[before] = std::unordered_set<int>();
        // }
        res[after].insert(before);
    }

    return res;
} 

int check_order(std::unordered_map<int, std::unordered_set<int>>& order_map, std::vector<int>& order_ints) {
    for (int i = 0; i < order_ints.size(); i++) {
        if ( order_map.find(order_ints[i]) == order_map.end() ) {
            continue;
        }
        for (int j = i + 1; j < order_ints.size(); j++) {
            auto curr_set = order_map[order_ints[i]];
            if (curr_set.find(order_ints[j]) != curr_set.end()) {
                return 0;
            }
        }
    }

    return order_ints[order_ints.size() / 2];
}

int check_order_pt2(std::unordered_map<int, std::unordered_set<int>>& order_map, std::vector<int>& order_ints) {
    for (int i = 0; i < order_ints.size(); i++) {
        if ( order_map.find(order_ints[i]) == order_map.end() ) {
            continue;
        }
        for (int j = i + 1; j < order_ints.size(); j++) {
            auto curr_set = order_map[order_ints[i]];
            if (curr_set.find(order_ints[j]) != curr_set.end()) {
                int tmp = order_ints[j];
                order_ints[j] = order_ints[i];
                order_ints[i] = tmp;
                return check_order_pt2(order_map, order_ints);
            }
        }
    }

    return order_ints[order_ints.size() / 2];
}


int part1(std::string& input) {
    std::vector<std::string> instructions;
    std::vector<std::string> orders;
    std::istringstream iss(input);
    std::string line;
    bool flip = 0;

    for ( line; std::getline(iss, line); ) {
        if (line.empty()) {
            flip = 1;
            continue;
        }

        if (!flip) {
            instructions.push_back(line);
        } else {
            orders.push_back(line);
        }
    }

    auto order_map = get_dependencies(instructions);

    int res = 0;
    for (auto order : orders) {
        std::vector<int> order_ints;
        auto order_strs = helpers::split(order, ',');
        for (std::string order_str : order_strs ) {
            order_ints.push_back(std::stoi(order_str));
        }

        res += check_order(order_map, order_ints);
    }

    return res;
}

int part2(std::string& input) {
    // std::vector<std::string> instructions_orders = helpers::split(input, "\n");
    std::vector<std::string> instructions;
    std::vector<std::string> orders;
    std::istringstream iss(input);
    std::string line;
    bool flip = 0;

    for ( line; std::getline(iss, line); ) {
        if (line.empty()) {
            flip = 1;
            continue;
        }

        if (!flip) {
            instructions.push_back(line);
        } else {
            orders.push_back(line);
        }
    }

    auto order_map = get_dependencies(instructions);

    int res = 0;
    for (auto order : orders) {
        std::vector<int> order_ints;
        auto order_strs = helpers::split(order, ',');
        for (std::string order_str : order_strs ) {
            order_ints.push_back(std::stoi(order_str));
        }

        res += check_order_pt2(order_map, order_ints);
    }

    return res;
}

int main() {
    std::string input = helpers::read_input("day5/input.txt");
    // std::cout << input << std::endl;
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) - part1(input) << std::endl;
    return 0;
}