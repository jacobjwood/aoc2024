#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

long long part1(std::string& input) {
    std::vector<int> c_vec;
    long long check_sum = 0;
    int idx = 0;

    for ( int i = 0; i < input.size(); ++i ) {
        // std::cout << input[i] << std::endl;
        if ((i % 2) == 0) {
            int range = (int)input[i] - 48;
            for (int j = 0; j < range; ++j) {
                c_vec.push_back(idx);
            }
            idx++;
        } else {
            int range = (int)input[i] - 48;
            for (int j = 0; j < range; ++j) {
                c_vec.push_back(-1);
            }
        }
    }

    int l = 0;
    int r = c_vec.size() - 1;
    while (l < r) {
        if (c_vec[r] == -1) {
            r--;
            continue;
        }
        if (c_vec[l] == -1) {   
            c_vec[l] = c_vec[r];
            c_vec[r] = -1;
        }
        l++;
    }

    int pos = 0;
    for (auto i : c_vec) {
        if (i == -1) {
            break;
        }

        check_sum += pos * i;
        pos++;

    }

    return check_sum;
}


long long part2(std::string input) {
    std::vector<std::pair<int, int>> intervals;
    long long check_sum = 0;
    std::unordered_set<int> seen;

    for (int i = 0; i < input.size(); ++i ) {
        int length = (int)input[i] - 48;
        if (i % 2) {
            intervals.push_back(std::make_pair(-1, length));
        } else {
            intervals.push_back(std::make_pair(i / 2, length));
        }
    }

    int r = intervals.size() - 1;
    while (r >= 0) {
        if ((intervals[r].first == -1) || (seen.find(intervals[r].first) != seen.end())) {
            r--;
            continue;
        }



        int l = 0;
        seen.insert(intervals[r].first);
        while (l < r) {
            if (intervals[l].first != -1) {
                l++;
                continue;
            }

            if (intervals[l].second >= intervals[r].second) {
                intervals.insert(intervals.begin() + l, intervals[r]);

                intervals[l+1].second -= intervals[l].second;
                intervals[r].second += intervals[l].second;
                intervals.erase(intervals.begin() + r + 1);
                break;
            }

            l++;
        }

        r--;
    }

    std::vector<int> res;
    for ( auto interval : intervals ) {
        for ( int i = 0; i < interval.second; ++i) {
            if (interval.first != -1) {
                res.push_back(interval.first);
            } else {
                res.push_back(0);
            }
        }
    }

    for ( int i = 0; i < res.size(); ++i ) {
        check_sum += i * res[i];
    }

    return check_sum;
}

int main() {
    std::string input = helpers::read_input("day9/input.txt");
    std::string example = "2333133121414131402";
    // std::cout << input << std::endl;
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}