#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <cmath>


uint64_t check_operands(uint64_t target, std::vector<uint64_t> operands) {

    uint64_t max_sum = target;
    for ( long i = 0; i <  std::pow(2, (operands.size() - 1)); ++i ) {
        long tmp = i;
        uint64_t sum = operands[0];
        uint64_t prev_sum = 0;
        std::string eqn = "";
        eqn += std::to_string(target) + " = ";
        eqn += std::to_string(sum);
        for ( int j = 1; j < (operands.size()); ++j ) {
            int op = tmp % 2;
            if (op) {
                sum += operands[j];
            } else {
                sum *= operands[j]; 
            }

            tmp = tmp >> 1;
            eqn += (op ? " + " : " * ") + std::to_string(operands[j]);
        }

        max_sum = std::max(max_sum, sum);

        if (sum == target) {
            return target;
        }

    }
    return 0;
}

bool check_operands_recursive(uint64_t target, std::vector<uint64_t>& operands, int pos, uint64_t sum, bool part1) {
    if (pos == operands.size()) {
        return sum == target;
    }

    if (pos == 0) {
        return check_operands_recursive(target, operands, pos + 1, sum + operands[pos], part1);
    }


    bool pt1_only = check_operands_recursive(target, operands, pos + 1, sum * operands[pos], part1) || check_operands_recursive(target, operands, pos + 1, sum + operands[pos], part1); 
    if (part1) {
        return pt1_only;
    } else {
        return pt1_only || check_operands_recursive(target, operands, pos + 1, std::stoull(std::to_string(sum) + std::to_string(operands[pos])), part1);
    }
}

void solve(std::string& input) {
    std::istringstream iss(input);
    std::string line;
    uint64_t res_pt1 = 0;
    uint64_t res_pt2 = 0;

    for ( line; std::getline(iss, line); ) {
        // std::cout << line << std::endl;
        auto l1 = helpers::split(line, ": ");
        uint64_t target = std::stoull(l1[0]);
        std::vector<uint64_t> operands;
        auto split_2 = helpers::split(l1[1], " ");
        for ( std::string operand : split_2 ) {
            operands.push_back(std::stoull(operand));
        }
        
        if (check_operands_recursive(target, operands, 0, 0, true)) {
            res_pt1 += target;
        }

        if (check_operands_recursive(target, operands, 0, 0, false)) {
            res_pt2 += target;
        }
    }
    std::cout << "Part 1: " << res_pt1 << std::endl;
    std::cout << "Part 2: " << res_pt2 << std::endl;
}

int main() {
    std::string input = helpers::read_input("day7/input.txt");
    std::string example = R""""(190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20)"""";
    solve(input);
    return 0;
}