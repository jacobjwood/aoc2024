#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
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

std::vector<std::vector<char>> parse_maze(std::string input) {
    std::vector<std::vector<char>> maze;
    std::vector<char> row;
    for (char c : input) {
        if (c == '\n') {
            maze.push_back(row);
            row.clear();
        } else {
            row.push_back(c);
        }
    }
    return maze;
}

struct ReindeerState {
    int score;
    std::pair<int, int> direction;
    std::pair<int, int> pos;
    bool turned;
};

std::pair<int, int> turn_left(std::pair<int, int> direction) {
    if (direction == std::make_pair(0, 1)) {
        return std::make_pair(-1, 0);
    }
    if (direction == std::make_pair(0, -1)) {
        return std::make_pair(1, 0);
    }
    if (direction == std::make_pair(1, 0)) {
        return std::make_pair(0, 1);
    }
    if (direction == std::make_pair(-1, 0)) {
        return std::make_pair(0, -1);
    }
    return std::make_pair(0, 0);
}

std::pair<int, int> turn_right(std::pair<int, int> direction) {
    if (direction == std::make_pair(0, 1)) {
        return std::make_pair(1, 0);
    }
    if (direction == std::make_pair(0, -1)) {
        return std::make_pair(-1, 0);
    }
    if (direction == std::make_pair(1, 0)) {
        return std::make_pair(0, -1);
    }
    if (direction == std::make_pair(-1, 0)) {
        return std::make_pair(0, 1);
    }
    return std::make_pair(0, 0);
}

std::pair<int, int> move(std::pair<int, int> pos, std::pair<int, int> direction) {
    return std::make_pair(pos.first + direction.first, pos.second + direction.second);
}


int part1(std::string input) {
    std::vector<std::vector<char>> maze = parse_maze(input);
    std::unordered_map<std::pair<int, int>, int, hash_pair> visited;
    std::vector<ReindeerState> states = {{0, std::make_pair(0, 1), std::make_pair(maze.size() - 2, 1), false}};
    int min_e = 1000000000;
    while (states.size()) {
        auto curr = states.back();
        states.pop_back();
        if (maze[curr.pos.first][curr.pos.second] == 'E') {
            min_e = std::min(min_e, curr.score);
        }
        if ((visited.find(curr.pos) != visited.end()) && (curr.score > visited[curr.pos] + 1000)) {
            continue;
        } else if ((visited.find(curr.pos) != visited.end()) && (curr.score < visited[curr.pos])) {
            visited[curr.pos] = curr.score;
        } else if (visited.find(curr.pos) == visited.end()) {
            visited[curr.pos] = curr.score;
        }

        std::pair<int, int> next_pos = std::make_pair(curr.pos.first + curr.direction.first, curr.pos.second + curr.direction.second);

        if (maze[next_pos.first][next_pos.second] != '#') {
            states.push_back({curr.score + 1, curr.direction, next_pos, false});
        }


        if (!curr.turned) {
            std::pair<int, int> next_left = turn_left(curr.direction);
            std::pair<int, int> next_right = turn_right(curr.direction);

            states.push_back({curr.score + 1000, next_left, curr.pos, true});
            states.push_back({curr.score + 1000, next_right, curr.pos, true});
        }

    }

    return min_e;
}

struct ReindeerState2 {
    int score;
    std::pair<int, int> direction;
    std::pair<int, int> pos;
    bool turned;
    std::vector<std::pair<int, int>> visited;
};

int part2(std::string input, int best_score) {

    std::vector<std::vector<char>> maze = parse_maze(input);
    std::unordered_map<std::pair<int, int>, int, hash_pair> visited;
    std::vector<ReindeerState2> states = {{0, std::make_pair(0, 1), std::make_pair(maze.size() - 2, 1), false, {std::make_pair(maze.size() - 2, 1)}}};
    std::unordered_set<std::pair<int, int>, hash_pair> best_seats;
    while (states.size()) {
        auto curr = states.back();
        states.pop_back();

        if (curr.score > best_score) {
            continue;
        }

        if (maze[curr.pos.first][curr.pos.second] == 'E') {
            for (auto pos : curr.visited) {
                best_seats.insert(pos);
            };
            best_seats.insert(curr.pos);
            continue;
        }

        if ((visited.find(curr.pos) != visited.end()) && (curr.score > visited[curr.pos] + 1000)) {
            continue;
        } else if ((visited.find(curr.pos) != visited.end()) && (curr.score < visited[curr.pos])) {
            visited[curr.pos] = curr.score;
        } else if (visited.find(curr.pos) == visited.end()) {
            visited[curr.pos] = curr.score;
        }

        std::pair<int, int> next_pos = std::make_pair(curr.pos.first + curr.direction.first, curr.pos.second + curr.direction.second);

        if (maze[next_pos.first][next_pos.second] != '#') {
            auto new_history = curr.visited;
            new_history.push_back(curr.pos);
            states.push_back({curr.score + 1, curr.direction, next_pos, false, new_history});
        }


        if (!curr.turned) {
            std::pair<int, int> next_left = turn_left(curr.direction);
            std::pair<int, int> next_right = turn_right(curr.direction);

            states.push_back({curr.score + 1000, next_left, curr.pos, true, curr.visited});
            states.push_back({curr.score + 1000, next_right, curr.pos, true, curr.visited});
        }

    }

    return best_seats.size();

}

int main() {
    std::string input = helpers::read_input("day16/input.txt");
    int part1_result = part1(input);
    std::cout << "Part 1: " << part1_result << std::endl;
    std::cout << "Part 2: " << part2(input, part1_result) << std::endl;
    return 0;
}
