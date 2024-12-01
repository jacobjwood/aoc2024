#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <queue> 
#include <sstream>
#include <unordered_map>

int part1(std::string& input) {
    std::priority_queue<int> left_heap;
    std::priority_queue<int> right_heap;
    std::istringstream iss(input);

    for (std::string line; std::getline(iss, line); ) {
        std::vector<std::string> splitline = helpers::split_nonempty(line, ' ');
        left_heap.push(std::stoi(splitline[0]));
        right_heap.push(std::stoi(splitline[1]));
    }

    int res = 0;
    while (left_heap.size() && right_heap.size()) {
        res += std::abs(left_heap.top() - right_heap.top());
        left_heap.pop(); right_heap.pop();
    }
    return res;
}

int part2(std::string& input) {
    std::unordered_map<int, int> counts;
    std::istringstream iss(input);

    for (std::string line; std::getline(iss, line); ) {
        std::vector<std::string> splitline = helpers::split_nonempty(line, ' ');
        int l = std::stoi(splitline[0]);
        int r = std::stoi(splitline[1]);
        if ((counts.find(l) == counts.end()) && (counts.find(-l) == counts.end())) {
            counts[l] = 0;
        } else if ((counts.find(l) == counts.end()) && (counts.find(-l) != counts.end())) {
            counts[l] = std::abs(counts[-l]);
            ~counts[-l];
        }

        if (counts.find(r) != counts.end()) {
            counts[r]++;
        } else if (counts.find(-r) != counts.end()) {
            counts[-r]--;
        } else {
            counts[-r] = -1;
        }
    }

    int res = 0;
    for (auto intpair : counts) {
        if (intpair.first > 0) {
            res += intpair.first * intpair.second;
        }
    }
    return res;
}

int main() {
    std::string input = helpers::read_input("day1/input.txt");
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}