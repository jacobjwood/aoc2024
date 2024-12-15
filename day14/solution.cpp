#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <unordered_map>
#include <sstream>
#include <chrono>
#include <thread>

struct Robot {
    int p_i;
    int p_j;
    int v_i;
    int v_j;
};

std::unordered_map<int, Robot> get_init_positions(std::string input) {
    std::istringstream iss(input);
    std::string line;
    std::unordered_map<int, Robot> res;
    int line_idx = 0;
    for ( line; std::getline(iss, line); ) {
        auto pv = helpers::split(line, ' ');
        auto p = helpers::split(pv[0], '=')[1];
        auto v = helpers::split(pv[1], '=')[1];
        auto p_vec = helpers::split(p, ',');
        auto v_vec = helpers::split(v, ',');
        res[line_idx] = {std::stoi(p_vec[1]), std::stoi(p_vec[0]), std::stoi(v_vec[1]), std::stoi(v_vec[0])};

        //std::cout << p[1] << " " << v[1] << std::endl;
        line_idx++;
    }
    return res;
}

int part1(std::string input, int width, int height) {
    int middle_i = height / 2;
    int middle_j = width / 2;
    std::unordered_map<int, Robot> robot_positions = get_init_positions(input);
    int iterations = 100;
    int quad1 = 0;
    int quad2 = 0;
    int quad3 = 0;
    int quad4 = 0;
    for (auto rpair : robot_positions) {
        auto robot = rpair.second;
        robot.p_i = (height + ((robot.p_i + iterations * robot.v_i) % height)) % height;
        robot.p_j = (width + ((robot.p_j + iterations * robot.v_j) % width)) % width;
        bool i_low = (robot.p_i < middle_i);
        bool j_low = (robot.p_j < middle_j);
        quad1 += (i_low && j_low);
        quad2 += (i_low && !j_low && !(robot.p_j == middle_j));
        quad3 += (!i_low && !(robot.p_i == middle_i) && j_low);
        quad4 += (!i_low && !(robot.p_i == middle_i) && !(robot.p_j == middle_j) && !j_low);
    }
    return quad1 * quad2 * quad3 * quad4;
}

int part2(std::string input, int width, int height) {
    std::unordered_map<int, Robot> robot_positions = get_init_positions(input);
    int iterations = 100;
    int quad1 = 0;
    int quad2 = 0;
    int quad3 = 0;
    int quad4 = 0;
    // std::vector<std::string> grid;
    // for (int i = 0; i < height; i++ ) {
    //     std::string row = "";
    //     for (int j = 0; j < width; j++) {
    //         row += ".";
    //     }
    //     grid.push_back(row);
    // }

    int it_count = 0;
    for (int it = 0; it < 20000; it++) { 
        std::vector<std::string> grid;
        for (int i = 0; i < height; i++ ) {
            std::string row = "";
            for (int j = 0; j < width; j++) {
                row += ".";
            }
            grid.push_back(row);
        }
        for (auto rpair : robot_positions) {
            auto robot = rpair.second;
            if (it_count != 0) {
                robot.p_i = (height + ((robot.p_i + robot.v_i) % height)) % height;
                robot.p_j = (width + ((robot.p_j + robot.v_j) % width)) % width;
                it_count += 101;
            } else {
                robot.p_i = (height + ((robot.p_i + robot.v_i) % height)) % height;
                robot.p_j = (width + ((robot.p_j + robot.v_j) % width)) % width;
                it_count += 95;
            }
            grid[robot.p_i][robot.p_j] = 'X';
            robot_positions[rpair.first] = robot;
        }

        if (it == 7568) {

            std::cout << "ITERATION: " << it << std::endl;
            for (std::string row : grid) {
                std::cout << row << std::endl;
            }
            std::cout << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return it + 1;
        }
    }
}

int main() {
    std::string input = helpers::read_input("day14/input.txt");
    std::string example = R""""(p=0,4 v=3,-3
p=6,3 v=-1,-3
p=10,3 v=-1,2
p=2,0 v=2,-1
p=0,0 v=1,3
p=3,0 v=-2,-2
p=7,6 v=-1,-3
p=3,0 v=-1,-2
p=9,3 v=2,3
p=7,3 v=-1,2
p=2,4 v=2,-3
p=9,5 v=-3,-3)"""";
    std::cout << input << std::endl;
    std::cout << "Part 1 Example: " << part1(example, 11, 7) << std::endl;
    std::cout << "Part 1: " << part1(input, 101, 103) << std::endl;
    std::cout << "Part 2: " << part2(input, 101, 103) << std::endl;
    return 0;
}