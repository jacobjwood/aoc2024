#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <unordered_map>
#include <sstream>
#include <climits>
#include <cmath>

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
        cg.target.second += 10000000000000;


        // We check for a solution
        // na0 + mb0 = t0 + 1000000
        // na1 + mb1 = t1 + 1000000
        // n(a0 - a1) + m (b0 - b1) = t0 - t1
        // iterate over n, m
        // a0 b0 m = f + t0
        // a1 b1 n = f + t1
        long long quotient = (cg.a.first * cg.b.second - cg.b.first * cg.a.second);
        if (quotient == 0) {
            std::cout << "ZERO QUOT" << std::endl;
            continue;
        }
        long double inverse_factor = (cg.a.first * cg.b.second - cg.b.first * cg.a.second);
        long double inverse_summation_m = (cg.b.second * cg.target.first - cg.b.first * cg.target.second);
        long double inverse_summation_n = (cg.target.second * cg.a.first - cg.a.second * cg.target.first);
        double epsilon = 0.00001;
        double m_d = inverse_summation_m / inverse_factor;
        double n_d = inverse_summation_n / inverse_factor;
        long long m = (long long) std::round(m_d);
        long long n = (long long) std::round(n_d);
        double delta_m = std::abs(std::round(m_d) - m_d);
        double delta_n = std::abs(std::round(n_d) - n_d);
        // std::cout << m << " " << n << std::endl;
        if ((m >= 0) && (n >= 0) && (delta_m < epsilon) && (delta_n < epsilon)) {
            costs += (m * a_cost + n * b_cost);
        }
        // long long delta_a = cg.a.first - cg.a.second;
        // long long delta_b = cg.b.first - cg.b.second;
        // long long delta_t = cg.target.first - cg.target.second;

        // // std::cout << delta_a << " " << delta_b << " " << delta_t << std::endl;
        // int threshold = 100000;
        // long long cost1 = LLONG_MAX;
        // long long cost2 = LLONG_MAX;
        // for (int i = 0; i < threshold; i++) {
        //     for (int j = 0; j < threshold; j++ ) {

        //         if (((i * delta_a + j * delta_b) > delta_t) && ((j * delta_a + i * delta_b) > delta_t)) {
        //             break;
        //         }
                
        //         if ((i * delta_a + j * delta_b) == delta_t) {
        //             // std::cout << "MATCH" << std::endl;
        //             cost1 = std::min(cost1, i * a_cost + j * b_cost);
        //         } 
                
        //         if ((j * delta_a + i * delta_b) == delta_t) {
        //             // std::cout << "MATCH2" << std::endl;
        //             cost2 = std::min(cost2, j * a_cost + i * b_cost);
        //         }
        //     }
        // }

        // long long poss_cost = std::min(cost1, cost2);
        // if (poss_cost != LLONG_MAX) {
        //     costs += poss_cost;
        // }

        



    }

    return costs;
}

int main() {
    std::string input = helpers::read_input("day13/input.txt");
    std::cout << input << std::endl;
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}
