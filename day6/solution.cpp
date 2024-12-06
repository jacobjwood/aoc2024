#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <sstream>

std::pair<std::vector<std::vector<char>>, std::pair<int, int>> get_grid_and_pos(std::string &input) {
    std::vector<std::vector<char>> grid;
    std::istringstream iss(input);
    std::string line;
    int i, j = 0;
    int line_i, line_j = 0;

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

int part1(std::string& input) {
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
    return res;
}

int run_scan(std::vector<std::vector<char>>& grid, std::pair<int, int> mut_pos, int dir_index) {
    char tmp = grid[mut_pos.first][mut_pos.second];
    if ( tmp == '#' ) {
        return 0;
    }
    
    std::cout << "Running scan" << std::endl;
    grid[mut_pos.first][mut_pos.second] = '#';
    auto pos = mut_pos;
    std::vector<std::pair<int, int>> dir_order = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int M = grid.size();
    int N = grid[0].size();
    int x_count = 0;

    while (( pos.first >= 0 ) && ( pos.second >= 0 ) && ( pos.first < M ) && (pos.second < N )) {
        if (grid[pos.first][pos.second] == '#') {
            int di = dir_order[dir_index].first;
            int dj = dir_order[dir_index].second;
            pos.first = pos.first - di;
            pos.second = pos.second - dj;
            dir_index = (dir_index + 1) % dir_order.size();
        } else {
            if (grid[pos.first][pos.second] == 'X') {
                if(x_count > 0) {
                    grid[mut_pos.first][mut_pos.second] = tmp;
                    return 1;
                } else {
                    x_count++;
                }
            } else {
                x_count = 0;
            }
        }

        int di = dir_order[dir_index].first;
        int dj = dir_order[dir_index].second;
        pos.first = pos.first + di;
        pos.second = pos.second + dj;
    }




    grid[mut_pos.first][mut_pos.second] = tmp;
    return 0;


}

int part2(std::string& input) {
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
            grid[pos.first][pos.second] = 'X';
        }

        int di = dir_order[dir_index].first;
        int dj = dir_order[dir_index].second;
        pos.first = pos.first + di;
        pos.second = pos.second + dj;

        if (pos != grid_and_pos.second) {
            res += run_scan(grid, pos, dir_index);
        }
    }

    // for ( auto line : grid ) {
    //     for ( char c : line ) {
    //         std::cout << c;
    //     }
    //     std::cout << std::endl;
    // }
    return res;
}

int main() {
    std::string input = helpers::read_input("day6/input.txt");
    std::cout << input << std::endl;
    std::cout << "Part 1: " << part1(input) << std::endl;
    // std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}