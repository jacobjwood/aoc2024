#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <unordered_map>
#include <unordered_set>

void apply_rules(std::vector<std::string>& balls, bool debug) {
    int i = 0;
    while (i < balls.size()) {

        // if (debug && (i > 300)) {
        //     return;
        // }
        if (balls[i] == "0") {
            balls[i] = "1";
        } else if ((balls[i].size() % 2) == 0) {
            std::string left = std::to_string(std::stoll(balls[i].substr(0, balls[i].size() / 2)));
            std::string right = std::to_string(std::stoll(balls[i].substr(balls[i].size() / 2, balls[i].size() / 2)));
            balls[i] = right;
            balls.insert(balls.begin() + i, left);
            i++;
        } else {
            balls[i] = std::to_string(std::stoll(balls[i]) * 2024);
        }
        i++;

        // if (debug) {
        //     std::cout << "Arrangement: ";
        //     for (auto ball : balls) {
        //         std::cout << ball << " ";
        //     }
        //     std::cout << std::endl;
        // }
    }
    if (debug) {
        int zero_count = 0;
        int ball_count = 0;
        long long max_ball = 0;
        // std::cout << "Arrangement: ";
        for (auto ball : balls) {
            zero_count += (ball == "0");
            // std::cout << ball << " ";
            ball_count++;
            max_ball = std::max(std::stoll(ball), max_ball);
        }
        std::cout << std::endl;
        
        std::cout << "Balls: " << ball_count << std::endl;
        std::cout << "Zeros: " << zero_count << std::endl;
        std::cout << "Max ball: " << max_ball << std::endl << std::endl;
    }
}

void apply_rules_pt2(std::vector<std::string>& balls, bool debug, std::unordered_set<std::string>& seen) {
    int i = 0;
    while (i < balls.size()) {

        // if (debug && (i > 300)) {
        //     return;
        // }
        if (balls[i] == "0") {
            balls[i] == "1";
        } else if ((balls[i].size() % 2) == 0) {
            std::string left = std::to_string(std::stoll(balls[i].substr(0, balls[i].size() / 2)));
            std::string right = std::to_string(std::stoll(balls[i].substr(balls[i].size() / 2, balls[i].size() / 2)));
            balls[i] = right;
            seen.insert(left);
            balls.insert(balls.begin() + i, left);
            i++;
        } else {
            balls[i] = std::to_string(std::stoll(balls[i]) * 2024);
        }
        seen.insert(balls[i]);
        i++;

        // if (debug) {
        //     std::cout << "Arrangement: ";
        //     for (auto ball : balls) {
        //         std::cout << ball << " ";
        //     }
        //     std::cout << std::endl;
        // }
    }
    if (debug) {
        int zero_count = 0;
        int ball_count = 0;
        long long max_ball = 0;
        // std::cout << "Arrangement: ";
        for (auto ball : balls) {
            zero_count += (ball == "0");
            // std::cout << ball << " ";
            ball_count++;
            max_ball = std::max(std::stoll(ball), max_ball);
        }
        std::cout << std::endl;
        
        std::cout << "Balls: " << ball_count << std::endl;
        std::cout << "Zeros: " << zero_count << std::endl;
        std::cout << "Max ball: " << max_ball << std::endl << std::endl;
    }
}
int part1(std::string& input, bool debug) {

    auto balls = helpers::split_nonempty(input, ' ');
    for (int i = 0; i < balls.size(); ++i) {
        balls[i] = std::to_string(std::stoi(balls[i]));
    }
    for (int i = 0; i < 25; ++i ) {
        apply_rules(balls, debug);
    }

    return balls.size();
}

int part2(std::string& input, int iterations, bool debug) {
    std::unordered_set<std::string> seen;
    auto balls = helpers::split_nonempty(input, ' ');
    for (int i = 0; i < balls.size(); ++i) {
        balls[i] = std::to_string(std::stoi(balls[i]));
    }

    for (int i = 0; i < iterations; ++i ) {
        apply_rules_pt2(balls, debug, seen);
        std::cout << "Seen size: " << seen.size() << std::endl;
    }

    return balls.size();
}

int main() {
    std::string input = helpers::read_input("day11/input.txt");
    std::string example = "125 17";
    std::string zero_only = "1";
    std::cout << input << std::endl;
    // std::cout << "Part 1: " << part1(input, false) << std::endl;
    std::cout << "Part 2: " << part2(input, 35, false) << std::endl;
    return 0;
}