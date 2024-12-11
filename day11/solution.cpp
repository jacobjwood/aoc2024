#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <unordered_map>
#include <unordered_set>

void apply_rules(std::unordered_map<std::string, unsigned long long>& ball_map) {
    std::vector<std::pair<std::string, unsigned long long>> updates;

    for (auto p: ball_map) {

        if (p.first == "0") {
            updates.push_back(std::make_pair("1", p.second));
        } else if ((p.first.size() % 2) == 0) {
            std::string left = std::to_string(std::stoull(p.first.substr(0, p.first.size() / 2)));
            std::string right = std::to_string(std::stoull(p.first.substr(p.first.size() / 2, p.first.size() / 2)));
            updates.push_back(std::make_pair(right, p.second));
            updates.push_back(std::make_pair(left, p.second));
        } else {
             updates.push_back(std::make_pair(std::to_string(std::stoull(p.first) * 2024), p.second));
        }
        ball_map[p.first] = 0;
    }

    for (auto update : updates) {
        if (ball_map.find(update.first) == ball_map.end()) {
            ball_map[update.first] = update.second;
        } else {
            ball_map[update.first] += update.second;
        }
    }
}

unsigned long long solve(std::string& input, int iterations) {
    auto balls = helpers::split_nonempty(input, ' ');
    std::unordered_map<std::string, unsigned long long> ball_map;

    for (int i = 0; i < balls.size(); ++i) {
        // since no duplicates in input, we can just do this to initialise the map
        ball_map[std::to_string(std::stoull(balls[i]))] = 1;
    }

    for (int i = 0; i < iterations; ++i ) {
        apply_rules(ball_map);
    }

    unsigned long long res = 0;
    for (auto p : ball_map) {
        res += p.second;
    }

    return res;
}

int main() {
    std::string input = helpers::read_input("day11/input.txt");
    std::string example = "125 17";
    std::cout << "Part 1: " << solve(input, 25) << std::endl;
    std::cout << "Part 2: " << solve(input, 75) << std::endl;
    return 0;
}
