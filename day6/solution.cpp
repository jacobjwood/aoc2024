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

std::pair<std::vector<std::vector<char>>, std::pair<int, int>> get_grid_and_pos(std::string &input) {
    std::vector<std::vector<char>> grid = std::vector<std::vector<char>>();
    std::istringstream iss(input);
    std::string line;
    int i = 0, j = 0;
    int line_i = 0, line_j = 0;

    for ( line; std::getline(iss, line); ) {
        std::vector<char> linevec = std::vector<char>();
        for ( char c : line ) {
            linevec.push_back(c);

            if (c == '^') {
                i = line_i;
                j = line_j;
            }
            line_j++;
        }
        grid.push_back(linevec);
        line_i++;
        line_j = 0;
    }
    return std::make_pair(grid, std::make_pair(i, j));
}

std::unordered_set<std::pair<int, int>, hash_pair> part1(std::string& input) {
    std::unordered_set<std::pair<int, int>, hash_pair> pos_set;
    auto grid_and_pos = get_grid_and_pos(input);
    auto grid = grid_and_pos.first;
    auto pos = grid_and_pos.second;
    int dir_index = 0;
    std::vector<std::pair<int, int>> dir_order = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int M = grid.size();
    int N = grid[0].size();
    int res = 0;

    while (( pos.first >= 0 ) && ( pos.second >= 0 ) && ( pos.first < M ) && (pos.second < N )) {
        if (grid[pos.first][pos.second] == '#') {
            int di = dir_order[dir_index].first;
            int dj = dir_order[dir_index].second;
            pos.first = pos.first - di;
            pos.second = pos.second - dj;
            dir_index = (dir_index + 1) % dir_order.size();
        } else if ((grid[pos.first][pos.second] != 'X')) {
            res++;
            grid[pos.first][pos.second] = 'X';
            pos_set.insert(std::make_pair(pos.first, pos.second));
            // breaks
        }

        int di = dir_order[dir_index].first;
        int dj = dir_order[dir_index].second;
        pos.first = pos.first + di;
        pos.second = pos.second + dj;
    }

    // for ( auto line : grid ) {
    //     for ( char c : line ) {
    //         std::cout << c;
    //     }
    //     std::cout << std::endl;
    // }
    std::cout << "Part 1: " << res << std::endl;
    return pos_set;
}
// int part1(std::string& input, std::unordered_set<std::pair<int, int>, hash_pair>& pos_set) {
//     auto grid_and_pos = get_grid_and_pos(input);
//     auto grid = grid_and_pos.first;
//     auto pos = grid_and_pos.second;
//     int dir_index = 0;
//     std::vector<std::pair<int, int>> dir_order = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
//     int M = grid.size();
//     int N = grid[0].size();
//     int i = pos.first;
//     int j = pos.second;
//     int res = 0;

//     while (( i >= 0 ) && ( j >= 0 ) && ( i < M ) && (j < N )) {
//         if (grid[i][j] == '#') {
//             int di = dir_order[dir_index].first;
//             int dj = dir_order[dir_index].second;
//             i = i - di;
//             j = j - dj;
//             dir_index = (dir_index + 1) % dir_order.size();
//         } else if ((grid[i][j] != 'X')) {
//             res++;
//             grid[pos.first][pos.second] = 'X';
//             pos_set.insert(std::make_pair(i, j));
//             // breaks
//         } else {

//             int di = dir_order[dir_index].first;
//             int dj = dir_order[dir_index].second;
//             i += di;
//             j += dj;
//         }
//     }

//     // for ( auto line : grid ) {
//     //     for ( char c : line ) {
//     //         std::cout << c;
//     //     }
//     //     std::cout << std::endl;
//     // }
//     return res;
// }

int run_scan(std::string& input, std::unordered_set<std::pair<int, int>, hash_pair>& path_set) {
    std::unordered_map<std::pair<int, int>, int, hash_pair> visit_counts;

    // std::cout << "Running scan" << std::endl;
    auto grid_and_pos = get_grid_and_pos(input);
    auto grid = grid_and_pos.first;
    auto pos = grid_and_pos.second;
    auto init_pos = pos;
    int dir_index = 0;
    std::vector<std::pair<int, int>> dir_order = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int M = grid.size();
    int N = grid[0].size();
    int res = 0;

    for ( auto p : path_set ) {
        auto grid_and_pos = get_grid_and_pos(input);
        auto grid = grid_and_pos.first;
        auto pos = grid_and_pos.second;
        auto init_pos = pos;
        int dir_index = 0;
        std::vector<std::pair<int, int>> dir_order = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        int M = grid.size();
        int N = grid[0].size();
        char tmp = grid[p.first][p.second];
        grid[p.first][p.second] = '#';
        if (p == init_pos) {
            continue;
        }
        while (( pos.first >= 0 ) && ( pos.second >= 0 ) && ( pos.first < M ) && (pos.second < N )) {
            if (grid[pos.first][pos.second] == '#') {
                int di = dir_order[dir_index].first;
                int dj = dir_order[dir_index].second;
                pos.first = pos.first - di;
                pos.second = pos.second - dj;
                dir_index = (dir_index + 1) % dir_order.size();
            } else if ((grid[pos.first][pos.second] != 'X')) {
                grid[pos.first][pos.second] = 'X';
                visit_counts[std::make_pair(pos.first, pos.second)] = 1;
                // breaks
            } else {
                visit_counts[std::make_pair(pos.first, pos.second)] += 1;
                if (visit_counts[std::make_pair(pos.first, pos.second)] >= 5) {
                    res++;
                    break;
                }
            }

            int di = dir_order[dir_index].first;
            int dj = dir_order[dir_index].second;
            pos.first = pos.first + di;
            pos.second = pos.second + dj;
        }
        grid[p.first][p.second] = tmp;
    }



    return res;


}

// int part2(std::string& input) {
//     auto grid_and_pos = get_grid_and_pos(input);
//     auto grid = grid_and_pos.first;
//     auto pos = grid_and_pos.second;
//     int dir_index = 0;
//     std::vector<std::pair<int, int>> dir_order = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
//     int M = grid.size();
//     int N = grid[0].size();
//     int res = 0;

//     while (( pos.first >= 0 ) && ( pos.second >= 0 ) && ( pos.first < M ) && (pos.second < N )) {

//         if (grid[pos.first][pos.second] == '#') {
//             int di = dir_order[dir_index].first;
//             int dj = dir_order[dir_index].second;
//             pos.first = pos.first - di;
//             pos.second = pos.second - dj;
//             dir_index = (dir_index + 1) % dir_order.size();
//         } else if ((grid[pos.first][pos.second] != 'X')) {
//             grid[pos.first][pos.second] = 'X';
//         }

//         int di = dir_order[dir_index].first;
//         int dj = dir_order[dir_index].second;
//         pos.first = pos.first + di;
//         pos.second = pos.second + dj;

//         if ((pos != grid_and_pos.second) && (pos.first < M) && (pos.second < N) && (pos.first >= 0) && (pos.second >= 0)) {
//             auto grid_copy = grid;
//             res += run_scan(grid_copy, pos, grid_and_pos.second, dir_index);
//         }
//     }

//     for ( auto line : grid ) {
//         for ( char c : line ) {
//             std::cout << c;
//         }
//         std::cout << std::endl;
//     }
//     return res;
// }

int main() {
    std::string input = helpers::read_input("day6/input.txt");
    std::cout << input << std::endl;
    std::unordered_set<std::pair<int, int>, hash_pair> pos_set;
    auto path_set = part1(input); //pos_set.size() << std::endl; //
    std::cout << "Part 2: " << run_scan(input, path_set) << std::endl;
    return 0;
}
