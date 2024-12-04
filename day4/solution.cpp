#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <sstream>
#include <string>
#include <vector>

// A hash function used to hash a pair of any kind
// TODO: Understand this better
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

std::vector<std::vector<char>> get_grid(std::string input) {
    std::vector<std::vector<char>> res = std::vector<std::vector<char>>();
    auto iss = std::istringstream(input);
    for ( std::string line; std::getline(iss, line); ) {
        std::vector<char> line_vec = std::vector<char>();
        for ( char c : line ) {
            line_vec.push_back(c);
        }
        res.push_back(line_vec);
    }
    return res;
}

int search(std::vector<std::vector<char>>& grid, int i, int j, int M, int N, std::pair<int, int> dir, std::string& s, int s_idx) {
    if ( s_idx == s.length() ) {
        return 1;
    }

    if ( i < 0 || j < 0 || i >= M || j >= N ) {
        return 0;
    }
    if ( grid[i][j] == s[s_idx] ) {
        return search(grid, i + dir.first, j + dir.second, M, N, dir, s, s_idx + 1);
    }
    return 0;
}

void search_pt2(std::vector<std::vector<char>>& grid, std::unordered_map<std::pair<int, int>, int, hash_pair>& a_map, int i, int j, int M, int N, std::pair<int, int> dir, std::string& s, int s_idx) {
    if ( (s_idx == s.length()) || ( i < 0 || j < 0 || i >= M || j >= N ) ) {
        return;
    }

    if ( grid[i][j] == s[s_idx] ) {
        if (grid[i][j] == 'S') {
            auto it = a_map.find(std::make_pair(i - dir.first, j - dir.second));
            if (it != a_map.end()) {
                a_map[std::make_pair(i - dir.first, j - dir.second)] += 1;
            } else {
                a_map[std::make_pair(i - dir.first, j - dir.second)] = 1;
            }
        }
        return search_pt2(grid, a_map, i + dir.first, j + dir.second, M, N, dir, s, s_idx + 1);
    }
}

int part1(std::string& input) {
    auto grid = get_grid(input);
    std::string match = "XMAS";
    int M = grid.size();
    int N = grid[0].size();
    // tuple only has explicit constructors, so using pair. Also more explicit.
    std::vector<std::pair<int, int>> dirs = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};
    int res = 0;
    for ( int i = 0; i < M; i++ ) {
        for ( int j = 0; j < N; j++ ) {
            for ( auto dir : dirs ) {
                res += search(grid, i, j, M, N, dir, match, 0);
            }
        }
    }

    return res;
}

int part2(std::string& input) {
    auto grid = get_grid(input);
    std::string match = "MAS";
    int M = grid.size();
    int N = grid[0].size();
    std::vector<std::pair<int, int>> dirs = {{-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
    std::unordered_map<std::pair<int, int>, int, hash_pair> a_map; // = std::unordered_map<std::pair<int, int>, int, hash_pair>();
    int res = 0;
    for ( int i = 0; i < M; i++ ) {
        for ( int j = 0; j < N; j++ ) {
            for ( auto dir : dirs ) {
                search_pt2(grid, a_map, i, j, M, N, dir, match, 0);
            }
        }
    }
    for ( auto a_map_pair : a_map ) {
        res += (a_map_pair.second == 2);
    }
    return res;
}


int main() {
    std::string input = helpers::read_input("day4/input.txt");
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}

// TODO: Figure out how to hash the position correctly. Maybe could use a grid?
