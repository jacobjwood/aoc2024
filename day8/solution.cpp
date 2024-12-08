#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <sstream>
#include <unordered_map>
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




std::vector<std::vector<char>> parse_map(std::string& input) {
    std::istringstream iss(input);
    std::string line;
    std::vector<std::vector<char>> grid;
    for ( line; std::getline(iss, line); ) {
        std::vector<char> linevec;
        for ( char c : line ) {
            linevec.push_back(c);
        }
        grid.push_back(linevec);
    }

    return grid;
}

std::unordered_map<char, std::vector<std::pair<int, int>>> get_nodes(std::vector<std::vector<char>>& grid) {
    std::unordered_map<char, std::vector<std::pair<int, int>>> node_map;
    int M = grid.size();
    int N = grid[0].size();
    for ( int i = 0; i < M; ++i ) {
        for ( int j = 0; j < N; ++j ) {
            if (grid[i][j] == '.') continue;

            if (node_map.find(grid[i][j]) == node_map.end()) {
                node_map[grid[i][j]] = std::vector<std::pair<int, int>>();
            }

            node_map[grid[i][j]].push_back(std::make_pair(i, j));
        }
    }

    return node_map;
}

void check_antinode_bounds(std::vector<std::pair<int, int>> node_vec, int bound_i, int bound_j, std::unordered_set<std::pair<int, int>, hash_pair>& unique_locs) {

    for ( int i = 0; i < node_vec.size(); ++i ) {
        for ( int j = i + 1; j < node_vec.size(); ++j ) {
            auto p1 = node_vec[i];
            auto p2 = node_vec[j];

            std::pair<int, int> p1_to_p2 = {p2.first - p1.first, p2.second - p1.second};
            std::pair<int, int> anti_p1 = {p1.first - p1_to_p2.first, p1.second - p1_to_p2.second};
            std::pair<int, int> anti_p2 = {p2.first + p1_to_p2.first, p2.second + p1_to_p2.second};

            for ( auto p : {anti_p1, anti_p2}) {
                if ((p.first >= 0) && (p.second >= 0) && (p.first < bound_i) && (p.second < bound_j)) {
                    unique_locs.insert(std::make_pair(p.first, p.second));
                }
            }

        }
    }
}

void check_antinode_bounds_pt2(std::vector<std::pair<int, int>> node_vec, int bound_i, int bound_j, std::unordered_set<std::pair<int, int>, hash_pair>& unique_locs) {

    for ( int i = 0; i < node_vec.size(); ++i ) {
        for ( int j = i + 1; j < node_vec.size(); ++j ) {
            auto p1 = node_vec[i];
            auto p2 = node_vec[j];

            std::pair<int, int> p1_to_p2 = {p2.first - p1.first, p2.second - p1.second};
            while ((p1.first >= 0) && (p1.first < bound_i) && (p1.second >=0) && (p1.second < bound_j)) {
                unique_locs.insert(std::make_pair(p1.first, p1.second));
                p1 = {p1.first - p1_to_p2.first, p1.second - p1_to_p2.second};
            }
            
            while ((p2.first >= 0) && (p2.first < bound_i) && (p2.second >=0) && (p2.second < bound_j)) {
                unique_locs.insert(std::make_pair(p2.first, p2.second));
                p2 = {p2.first + p1_to_p2.first, p2.second + p1_to_p2.second};
            }
        }
    }
}

int part1(std::string& input) {
    auto grid = parse_map(input);
    auto node_map = get_nodes(grid);
    int M = grid.size();
    int N = grid[0].size();
    std::unordered_set<std::pair<int, int>, hash_pair> unique;

    for ( auto p : node_map ) {
        auto node_vec = p.second;
        check_antinode_bounds(node_vec, M, N, unique);
    }


    return unique.size();
}

int part2(std::string& input) {
    auto grid = parse_map(input);
    auto node_map = get_nodes(grid);
    int M = grid.size();
    int N = grid[0].size();
    std::unordered_set<std::pair<int, int>, hash_pair> unique;

    for ( auto p : node_map ) {
        auto node_vec = p.second;
        check_antinode_bounds_pt2(node_vec, M, N, unique);
    }

    bool debug = false;
    if (debug) {
        for (auto p: unique) {
            grid[p.first][p.second] = '#';
        }

        for (auto line: grid) {
            
            for (char c : line ) {
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }


    return unique.size();
}

int main() {
    std::string input = helpers::read_input("day8/input.txt");
    std::string example = R""""(............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............
)"""";
    // std::cout << input << std::endl;
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}