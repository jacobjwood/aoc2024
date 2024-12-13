#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <unordered_map>
#include <sstream>

struct ClawGame {
    std::pair<long long, long long> a;
    std::pair<long long, long long> b;
    std::pair<long long, long long> target;
};

std::vector<ClawGame> parse_input(std::string input) {
    std::vector<ClawGame> parsed;
    std::istringstream iss(input);
    std::string line;
    std::pair<long long, long long> a;
    std::pair<long long, long long> b;
    std::pair<long long, long long> target;
    long long line_idx = 0;
    for (line; std::getline(iss, line); ) {
        if ((line_idx % 4) == 3) {
            parsed.push_back(
                {a, b, target}
            );
        } else if ((line_idx % 4) == 0) {
            auto v = helpers::split(line, '+');
            a = {std::stoi(v[1]), std::stoi(v[2])};
        } else if ((line_idx % 4) == 1) {
            auto v = helpers::split(line, '+');
            b = {std::stoi(v[1]), std::stoi(v[2])};
        } else {
            auto v = helpers::split(line, '=');
            target = {std::stoi(v[1]), std::stoi(v[2])};
        }
        line_idx++;
    }
    parsed.push_back(
        {a, b, target}
    );

    // for (auto c : parsed) {
    //     std::cout << "(" << c.a.first << ", " << c.a.second << "), " << "(" << c.b.first << ", " << c.b.second << "), " << "(" << c.target.first << ", " << c.target.second << ")" << std::endl;
    // }

    return parsed;
}

long long part1(std::string input) {
    auto parsed = parse_input(input);
    long long a_cost = 3;
    long long b_cost = 1;
    long long costs = 0;
    for (auto cg: parsed) {
        // long long a_div = std::min(cg.target.first / cg.a.first, cg.target.second / cg.a.second);
        // long long b_div = std::min(cg.target.first / cg.b.first, cg.target.second / cg.b.second);
        // std::cout << a_div << " " << b_div << std::endl;
        // if (a_div > 100) && (b_div > 100) {
        //     continue;
        // }
        bool found = 0;
        for (long long i = 1; i <= 100; ++i) {
            for (long long j = 1; j <= 100; ++j) {
                std::pair<long long, long long> curr = {(cg.a.first * i) + (cg.b.first * j), (cg.a.second * i) + (cg.b.second * j)};
                if ((curr.first == cg.target.first) && (curr.second == cg.target.second)) {
                    found = 1;
                    costs += (i * a_cost) + (j * b_cost);
                }
                if (found) break;    
            }
            if (found) break;
        }
    }

    return costs;
}

long long part2(std::string input) {
    auto parsed = parse_input(input);
    long long a_cost = 3;
    long long b_cost = 1;
    long long costs = 0;
    for (auto cg: parsed) {
        cg.target.first += 10000000000000;
        // long long a_div = std::min(cg.target.first / cg.a.first, cg.target.second / cg.a.second);
        // long long b_div = std::min(cg.target.first / cg.b.first, cg.target.second / cg.b.second);
        // std::cout << a_div << " " << b_div << std::endl;
        // if (a_div > 100) && (b_div > 100) {
        //     continue;
        // }
        
    }

    return costs;
}

int main() {
    std::string input = helpers::read_input("day13/input.txt");
    std::cout << input << std::endl;
    std::cout << "Part 1: " << part1(input) << std::endl;
    return 0;
}