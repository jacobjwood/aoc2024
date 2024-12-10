#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <unordered_map>
#include <sstream>
#include <unordered_set>

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        // Hash the first element
        size_t hash1 = std::hash<T1>{}(p.first);
        // Hash the second element
        size_t hash2 = std::hash<T2>{}(p.second);
        // Combine the two hash values
        return hash1
               ^ (hash2 + 0x9e3779b9 + (hash1 << 6)
                  + (hash1 >> 2));
    }
};

std::vector<std::vector<int>> get_grid(std::string& input) {
    std::vector<std::vector<int>> grid;
    std::istringstream iss(input);
    std::string line;

    for (line; std::getline(iss, line); ) {
        std::vector<int> linevec;
        for ( char c : line ) {
            linevec.push_back((int)c - 48 );
        }
        grid.push_back(linevec);
    }

    return grid;
}

int scan(std::vector<std::vector<int>>& grid, std::unordered_set<std::pair<int, int>, hash_pair>& tops, int i, int j) {

    int M = grid.size();
    int N = grid[0].size();


    if (grid[i][j] == 9) {
        tops.insert(std::make_pair(i, j));
        return 1;
    }


    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int res = 0;
    for ( auto dpair : directions) {
        int new_i = i + dpair.first;
        int new_j = j + dpair.second;

        if ((new_i >= M) || (new_j >= N) || (new_j < 0) || (new_i < 0)) continue;

        if ((grid[i][j] - grid[new_i][new_j]) != -1) continue;

        res += scan(grid, tops, new_i, new_j);

    }

    return res;



}


int solve(std::string input, bool part2) {
    auto grid = get_grid(input);

    int res = 0;
    int pt2 = 0;
    for ( int i = 0; i < grid.size(); ++i ) {
        for ( int j = 0; j < grid[0].size(); ++j ) {
            std::unordered_set<std::pair<int, int>, hash_pair> tops;
            if (grid[i][j] == 0) {
                pt2 += scan(grid, tops, i, j);
                res += tops.size();
            }
        }
    }
    if (part2) return pt2;
    return res;
}


int main() {
    std::string input = helpers::read_input("day10/input.txt");
    std::string example = R""""(89010123
78121874
87430965
96549874
45678903
32019012
01329801
10456732)"""";
    std::cout << "Part 1: " << solve(input, false) << std::endl;
    std::cout << "Part 2: " << solve(input, true) << std::endl;
    return 0;
}