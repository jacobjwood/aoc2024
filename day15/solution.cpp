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

std::tuple<std::pair<int, int>, std::vector<std::vector<char>>, std::string> get_warehouse_instructions(std::string& input) {
    std::vector<std::vector<char>> warehouse;
    std::string instructions;
    std::pair<int, int> pos;
    std::istringstream iss(input);
    std::string line;
    bool next = 0;
    int i = 0;
    int j = 0;

    for (line; std::getline(iss, line); ) {
        j = 0;
        std::vector<char> line_vec;
        if (line.empty()) {
            next = 1;
            continue;
        }

        if (next) {
            for (char c: line) {
                instructions += c;
            }
        }
        else {
            for (char c : line) {
                if (c == '@') {
                    pos = std::make_pair(i, j);
                }
                line_vec.push_back(c);
                j++;
            }
            warehouse.push_back(line_vec);
        }
        i++;
    }
    return {pos, warehouse, instructions};
}

std::tuple<std::pair<int, int>, std::vector<std::vector<char>>, std::string> get_warehouse_instructions_pt2(std::string& input) {
    std::vector<std::vector<char>> warehouse;
    std::string instructions;
    std::pair<int, int> pos;
    std::istringstream iss(input);
    std::string line;
    bool next = 0;
    int i = 0;
    int j = 0;

    for (line; std::getline(iss, line); ) {
        j = 0;
        std::vector<char> line_vec;
        if (line.empty()) {
            next = 1;
            continue;
        }

        if (next) {
            for (char c: line) {
                instructions += c;
            }
        }
        else {
            for (char c : line) {
                if (c == '@') {
                    pos = std::make_pair(i, j);
                    line_vec.push_back(c);
                    line_vec.push_back('.');
                } else if (c == '#') {
                    line_vec.push_back(c);
                    line_vec.push_back(c);
                } else if (c == 'O') {
                    line_vec.push_back('[');
                    line_vec.push_back(']');
                } else {
                    line_vec.push_back('.');
                    line_vec.push_back('.');
                }
                j += 2;
            }
            warehouse.push_back(line_vec);
        }
        i++;
    }
    return {pos, warehouse, instructions};
}

std::pair<int, int> mutate_warehouse(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse, char dir) {
    std::pair<int, int> direction;
    switch (dir) {
        case '^':
            direction = {-1, 0};
            break;
        case '>':
            direction = {0, 1};
            break;
        case '<':
            direction = {0, -1};
            break;
        case 'v':
            direction = {1, 0};
            break;
    }

    int new_i = pos.first + direction.first;
    int new_j = pos.second + direction.second;
    if (warehouse[new_i][new_j] == '#') {
        return pos;
    } else if (warehouse[new_i][new_j] == '.') {
        std::pair<int, int> new_pos = {new_i, new_j};
        warehouse[pos.first][pos.second] = '.';
        warehouse[new_pos.first][new_pos.second] = '@';
        return new_pos;
    }

    int track_i = new_i;
    int track_j = new_j;
    while (warehouse[track_i][track_j] == 'O') {
        track_i += direction.first;
        track_j += direction.second;
    }

    if (warehouse[track_i][track_j] == '.') {
        warehouse[track_i][track_j] = 'O';
        std::pair<int, int> new_pos = {new_i, new_j};
        warehouse[pos.first][pos.second] = '.';
        warehouse[new_pos.first][new_pos.second] = '@';
        return new_pos;
    } else {
        return pos;
    }

}

void print_warehouse(std::vector<std::vector<char>>& warehouse) {
    for (auto line : warehouse) {
        for (auto c: line) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool is_pushable(std::vector<std::vector<char>>& warehouse, std::vector<std::pair<int, int>>& stack, std::vector<char>& changes, std::pair<int, int> pos, std::pair<int, int> direction) {
    
    bool can_push = 0;
    std::pair<int, int> new_pos = {pos.first + direction.first, pos.second + direction.second};

    if ((warehouse[new_pos.first][new_pos.second] == '#')) {
        return false;
    } else if ((warehouse[new_pos.first][new_pos.second] == '.')) {
        return true;
    } else {
        std::pair<int, int> left = {new_pos.first, new_pos.second - (warehouse[new_pos.first][new_pos.second] == ']')};
        std::pair<int, int> right = {new_pos.first, new_pos.second + (warehouse[new_pos.first][new_pos.second] == '[')};

        can_push = is_pushable(warehouse, stack, changes, left, direction) && is_pushable(warehouse, stack, changes, right, direction);
        if (can_push) {
            stack.push_back(left);
            stack.push_back(right);
            changes.push_back(warehouse[left.first][left.second]);
            changes.push_back(warehouse[right.first][right.second]);
        }
        return can_push;
    }



}

std::pair<int, int> mutate_warehouse_pt2(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse, char dir) {
    std::pair<int, int> direction;
    switch (dir) {
        case '^':
            direction = {-1, 0};
            break;
        case '>':
            direction = {0, 1};
            break;
        case '<':
            direction = {0, -1};
            break;
        case 'v':
            direction = {1, 0};
            break;
    }

    int new_i = pos.first + direction.first;
    int new_j = pos.second + direction.second;
    if (warehouse[new_i][new_j] == '#') {
        return pos;
    } else if (warehouse[new_i][new_j] == '.') {
        std::pair<int, int> new_pos = {new_i, new_j};
        warehouse[pos.first][pos.second] = '.';
        warehouse[new_pos.first][new_pos.second] = '@';
        return new_pos;
    }

    int track_i = new_i;
    int track_j = new_j;
    std::vector<std::pair<int, int>> update_stack;
    if ((direction == std::make_pair(0, 1)) || (direction == std::make_pair(0, -1))) {


        while ((warehouse[track_i][track_j] == '[') || (warehouse[track_i][track_j] == ']')) {
            update_stack.push_back(std::make_pair(track_i, track_j));
            track_i += direction.first;
            track_j += direction.second;
        }


        if (warehouse[track_i][track_j] == '.') {
            while (update_stack.size()) {
                auto last = update_stack[update_stack.size() - 1];
                warehouse[track_i][track_j] = warehouse[last.first][last.second];
                track_i = last.first;
                track_j = last.second;
                update_stack.pop_back();
            }
            std::pair<int, int> new_pos = {new_i, new_j};
            warehouse[pos.first][pos.second] = '.';
            warehouse[new_pos.first][new_pos.second] = '@';
            return new_pos;
        } else {
            return pos;
        }
    } else {
        std::vector<std::pair<int, int>> stack;
        std::vector<char> changes;

        // return pos;
        

        if (is_pushable(warehouse, stack, changes, pos, direction)) {

            for (auto curr : stack) {
                warehouse[curr.first][curr.second] = '.';
            }
            while (stack.size()) {
                auto curr = stack[stack.size() - 1];
                auto change = changes[changes.size() - 1];
                warehouse[curr.first + direction.first][curr.second] = change;
                stack.pop_back();
                changes.pop_back();
            }
            std::pair<int, int> new_pos = {pos.first + direction.first, pos.second};
            warehouse[pos.first][pos.second] = '.';
            warehouse[new_pos.first][new_pos.second] = '@';
            if (warehouse[new_pos.first][new_pos.second + 1] == ']') {
                warehouse[new_pos.first][new_pos.second + 1] = '.';
            }

            if (warehouse[new_pos.first][new_pos.second - 1] == '[') {
                warehouse[new_pos.first][new_pos.second - 1] = '.';
            }
            
            return new_pos;
        } else {
            return pos;
        };
    }
}


int part1(std::string input) {
    auto [pos, warehouse, instructions] = get_warehouse_instructions(input);
    for (int ins = 0; ins < instructions.size(); ++ins ) {
        pos = mutate_warehouse(pos, warehouse, instructions[ins]);
    }

    int res = 0;
    for (int i = 0; i < warehouse.size(); ++i ) {
        for (int j = 0; j < warehouse[0].size(); ++ j) {
            if (warehouse[i][j] == 'O') {
                res += 100 * i + j;
            }
        }
    }
    return res;
}

int part2(std::string input) {
    auto [pos, warehouse, instructions] = get_warehouse_instructions_pt2(input);
    for (int ins = 0; ins < instructions.size(); ++ins ) {
        pos = mutate_warehouse_pt2(pos, warehouse, instructions[ins]);
    }
    
    int res = 0;
    for (int i = 0; i < warehouse.size(); ++i ) {
        for (int j = 0; j < warehouse[0].size(); ++ j) {
            if (warehouse[i][j] == '[') {
                res += 100 * i + j;
            }
        }
    }
    
    return res;
}

int main() {
    std::string input = helpers::read_input("day15/input.txt");
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}