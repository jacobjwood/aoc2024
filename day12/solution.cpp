#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

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

std::vector<std::vector<std::string>> get_grid(std::string input) {
    std::vector<std::vector<std::string>> grid;
    std::vector<std::string> row;
    for (char c : input) {
        if (c == '\n') {
            grid.push_back(row);
            row.clear();
        } else {
            row.push_back(std::string(1, c));
        }
    }
    return grid;
}

void add_fence(int i, int j, int di, int dj, std::unordered_map<std::pair<int, int>, std::vector<int>, hash_pair>& horizontal_fences, std::unordered_map<std::pair<int, int>, std::vector<int>, hash_pair>& vertical_fences) {
    if (di != 0) {
        if (horizontal_fences.find(std::make_pair(i, di)) == horizontal_fences.end()) {
            horizontal_fences[std::make_pair(i, di)] = {j};
        } else {
            horizontal_fences[std::make_pair(i, di)].push_back(j);
        }
    } else {
        if (vertical_fences.find(std::make_pair(j, dj)) == horizontal_fences.end()) {
            vertical_fences[std::make_pair(j, dj)] = {i};
        } else {
            vertical_fences[std::make_pair(j, dj)].push_back(i);
        }
    }
}

bool comp(int a, int b) {
    return a <= b;
}

int scan_plot(int i, int j, std::vector<std::vector<std::string>>& grid, std::unordered_map<std::string, int>& plot_acc) {
    int perimeter = 0;
    int area = 0;
    std::unordered_set<std::pair<int, int>, hash_pair> seen;
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    std::string plot_type = grid[i][j];
    std::vector<std::pair<int, int>> stack = {{i, j}};
    std::unordered_map<std::pair<int, int>, std::vector<int>, hash_pair> horizontal_fences;
    std::unordered_map<std::pair<int, int>, std::vector<int>, hash_pair> vertical_fences;
    int M = grid.size();
    int N = grid[0].size();

    while (stack.size()) {
        auto curr = stack[stack.size() - 1];
        stack.pop_back();
        // std::cout << "AT ROW: " << curr.first << " COLUMN: " << curr.second << std::endl;
        if (seen.find(curr) != seen.end()) {
            continue;
        }
        area++;
        for (auto dir: directions) {
            int di = dir.first;
            int dj = dir.second;
            int next_i = curr.first + di;
            int next_j = curr.second + dj;
            if ((next_i >= M) || (next_j >= N) || (next_i < 0) || (next_j < 0)) {
                perimeter++;
                add_fence(curr.first, curr.second, di, dj, horizontal_fences, vertical_fences);
                // continue;
            } else if (grid[next_i][next_j] != plot_type) {
                perimeter++;
                add_fence(curr.first, curr.second, di, dj, horizontal_fences, vertical_fences);
                // continue;
            } else {
                stack.push_back(std::make_pair(next_i, next_j));
            }
        }
        seen.insert(curr);

    }

    // std::cout << "Perimeter: " << perimeter << " Area: " << area << std::endl;

    if (plot_acc.find(plot_type) == plot_acc.end()) {
        plot_acc[plot_type] = perimeter * area;
    } else {
        plot_acc[plot_type] += perimeter * area;
    }

    for (auto p: seen) {
        // std::cout << p.first << " " << p.second << std::endl;
        grid[p.first][p.second] = "0";
    }

    int hf_count = 0;
    for (auto p: horizontal_fences) {
        int row_hf = 1;
        std::sort(p.second.begin(), p.second.end(), comp);

        for ( int i = 1; i < p.second.size(); i++ ) {
            int delta = p.second[i] - p.second[i-1];
            if (delta > 1) {
                row_hf++;
            }
        }
        hf_count += row_hf;
    }

    int vf_count = 0;
    for (auto p: vertical_fences) {
        int row_vf = 1;
        std::sort(p.second.begin(), p.second.end(), comp);

        for ( int i = 1; i < p.second.size(); i++ ) {
            int delta = p.second[i] - p.second[i-1];
            if (delta > 1) {
                row_vf++;
            }
        }
        hf_count += row_vf;
    }

    int total_fences = hf_count + vf_count;
    return total_fences * area;


}

int solve(std::string input, bool is_part2) {
    int res = 0;
    auto grid = get_grid(input);
    std::unordered_map<std::string, int> plot_acc;
    int pt2 = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == "0") {
                continue;
            }
            pt2 += scan_plot(i, j, grid, plot_acc);
        }
    }

    for (auto p : plot_acc) {
        res += p.second;
    }

    if (!is_part2) {
        return res;
    } else {
        return pt2;
    }
}

int main() {
    std::string input = helpers::read_input("day12/input.txt");
    std::string example = R""""(OOOOO
OXOXO
OOOOO
OXOXO
OOOOO
)"""";
    std::string example2 = R""""(EEEEE
EXXXX
EEEEE
EXXXX
EEEEE
)"""";
    std::cout << example << std::endl;
    std::cout << "Part 1: " << solve(input, false) << std::endl;
    std::cout << "Part 2: " << solve(input, true) << std::endl;
    return 0;
}
