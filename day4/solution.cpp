#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <sstream>
#include <string>
#include <vector>

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



int main() {
    std::string input = helpers::read_input("day4/input.txt");
    std::cout << input << std::endl;
    auto grid = get_grid(input);
    std::string match = "XMAS";
    int M = grid.size();
    int N = grid[0].size();
    for ( int i = 0; i < M; i++ ) {
        for ( int j = 0; j < N; j++ ) {
            // tuple only has explicit constructors
            std::vector<std::pair<int, int>> dirs = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};
            if (grid[i][j] == match[0]) {
                // i, j, i, j prev, match idx
                std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, int>> stack;
                


                std::cout << "MATCH" << std::endl;
            }

        }

    }

    return 0;
}