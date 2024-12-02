#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <sstream>

int part1(std::string& input) {
    std::istringstream iss(input);
    std::vector<std::vector<int>> parsed;
    std::string line;
    for (std::string line; std::getline(iss, line); ) {
        std::vector<int> parsed_line;
        for (auto s_num: helpers::split_nonempty(line, ' ')) {
            parsed_line.push_back(std::stoi(s_num));
        }
        parsed.push_back(parsed_line);
    }

    int num_safe = 0;
    for (auto line: parsed) {
        int dir = 0;
        num_safe++;
        for (int i = 1; i < line.size(); i++) {
            int delta = (line[i] - line[i-1]);

            if ((std::abs(delta) == 0) || (std::abs(delta) > 3)) {
                num_safe--;
                break;
            }

            if (i == 1) {
                dir = (delta) > 0;
            } else if (dir != (delta > 0)) {
                num_safe--;
                break;
            }
        }
    }

    return num_safe;

}

int checkline(std::vector<int> line, int tolerance) {
    int dir;
    for (int i = 1; i < line.size(); i++) {
        int delta = (line[i] - line[i-1]);

        if ((std::abs(delta) == 0) || (std::abs(delta) > 3)) {
            if (tolerance) {
                std::vector<int> linecopy(line);
                std::vector<int> linecopy2(line);
                linecopy.erase(linecopy.begin()+i-1);
                line.erase(line.begin()+i);
                if (i > 1) {
                    linecopy2.erase(linecopy2.begin()+i-2);
                    return (checkline(linecopy, 0) || checkline(line, 0) || checkline(linecopy2, 0));
                }
                return (checkline(linecopy, 0) || checkline(line, 0));
            }
            return 0;
        }

        if (i == 1) {
            dir = (delta) > 0;
        } else if (dir != (delta > 0)) {
            if (tolerance) {
                std::vector<int> linecopy(line);
                std::vector<int> linecopy2(line);
                linecopy.erase(linecopy.begin()+i-1);
                line.erase(line.begin()+i);
                if (i > 1) {
                    linecopy2.erase(linecopy2.begin()+i-2);
                    return (checkline(linecopy, 0) || checkline(line, 0) || checkline(linecopy2, 0));
                }
                return (checkline(linecopy, 0) || checkline(line, 0));
            }

            return 0;
        }
    }

    return 1;
}

int part2(std::string& input) {
    std::istringstream iss(input);
    std::vector<std::vector<int>> parsed;
    std::string line;
    for (std::string line; std::getline(iss, line); ) {
        std::vector<int> parsed_line;
        for (auto s_num: helpers::split_nonempty(line, ' ')) {
            parsed_line.push_back(std::stoi(s_num));
        }
        parsed.push_back(parsed_line);
    }

    int num_safe = 0;
    for (auto line: parsed) {
        int l = 0;
        int r = 1;
        int tolerance = 1;
        num_safe += checkline(line, tolerance);
    }

    return num_safe;

}

int main() {
    std::string input = helpers::read_input("day2/input.txt");
    const char *test = R""""(7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9)"""";
    // std::string input(test);
    std::cout << input << std::endl;
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}