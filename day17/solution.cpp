#include <iostream>
#include <fstream>
#include "helpers.hpp"
#include <vector>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include <cmath>

struct ProgramState {
    int A;
    int B;
    int C;
    std::vector<int> program;
    int ptr;
    std::string output;
    std::vector<int> output_vec;

    void print_state() {
        std::cout << "A: " << A << ", B: " << B << ", C: " << C << std::endl;
        std::cout << "Pointer: " << ptr << std::endl;
        std::cout << "Output: " << output << std::endl;
        for (auto p : program ) {
            std::cout << p << ",";
        }
        std::cout << std::endl;
        for (int i = 0; i < ptr; ++i) {
            std::cout << "  ";
        }
        std::cout << "^" << std::endl;
    }

    int get_combo_operand() {
        int op = program[this->ptr + 1];
        switch (op) {
            case 4: return this->A;
            case 5: return this->B;
            case 6: return this->C;
            case 7: throw std::invalid_argument("This is reserved");
            default: return op;
        }
    }

    void adv() {
        int op = get_combo_operand();
        this->A = this->A / std::pow(2, op);
        this->ptr += 2;
    }

    void bxl() {
        this->B = this->B ^ this->program[this->ptr + 1];
        this->ptr += 2;
    }

    void bst() {
        this->B = get_combo_operand() % 8;
        this->ptr += 2;
    }

    void jnz() {
        if (this->A == 0) {
            this->ptr += 2;
            return;
        }

        this->ptr = this->program[this->ptr+1];
    }

    void bxc() {
        this->B = this->B ^ this->C;
        this->ptr += 2;
    }

    void out() {
        int op = get_combo_operand();
        output += std::to_string(op % 8);
        output += ",";
        output_vec.push_back(op % 8);
        this->ptr += 2;
    }

    void bdv() {
        int op = get_combo_operand();
        this->B = this->A / std::pow(2, op);
        this->ptr += 2;
    }

    void cdv() {
        int op = get_combo_operand();
        this->C = this->A / std::pow(2, op);
        this->ptr += 2;
    }

    void iterate() {
        int ins = this->program[this->ptr];
        switch (ins) {
            case 0: 
                adv();
                break;
            case 1: 
                bxl();
                break;
            case 2: 
                bst();
                break;
            case 3: 
                jnz();
                break;
            case 4: 
                bxc();
                break;
            case 5: 
                out();
                break;
            case 6: 
                bdv();
                break;
            case 7:
                cdv();
                break;
            default: break;
        }
    }

    bool on_track() {
        if (!this->output_vec.size()) {
            return true;
        }

        return std::vector(this->program.begin(), this->program.begin() + this->output_vec.size()) == this->output_vec;
        for (int i = 0; i < this->output_vec.size(); i++) {
            if (this->output_vec[i] != this->program[i]) {
                return false;
            }
        }
        return true;
    }
};

ProgramState parse_input(std::string input) {
    std::istringstream iss(input);
    std::string line;
    int a = 0;
    int b = 0;
    int c = 0;
    std::vector<int> program;
    int line_idx = 0;
    for (line; std::getline(iss, line); ) {
        if (line_idx == 0) {
            a = std::stoi(helpers::split(line, ": ")[1]);
        } else if (line_idx == 1) {
            b = std::stoi(helpers::split(line, ": ")[1]);
        } else if (line_idx == 2) {
            c = std::stoi(helpers::split(line, ": ")[1]);
        } else if (line_idx == 4) {
            auto instructions_str = helpers::split(line, ": ")[1];
            auto split = helpers::split(instructions_str, ',');
            for (std::string c : split) {
                program.push_back(std::stoi(c));
            }
        }
        line_idx++;
    }
    return {a, b, c, program, 0, ""};
}


std::string part1(std::string input) {
    auto ps = parse_input(input);
    ps.print_state();
    while (ps.ptr < ps.program.size()) {
        ps.iterate();
        // ps.print_state();
    }
    return ps.output;
}

int part2(std::string input) {
    int a_try = 1000000000;
    while (true) {
        std::cout << a_try << std::endl;
        auto ps = parse_input(input);
        ps.A = a_try;
        while(ps.ptr < ps.program.size()) {
            ps.iterate();
            if (!ps.on_track()) {
                break;
            }
            // std::cout << ps.output << std::endl;
        }

        if (!ps.on_track()) {
            a_try++;
            continue;
        }

        for (auto i : ps.output_vec) {
            std::cout << i << ",";
        }
        std::cout << std::endl;
        for (auto i : ps.program) {
            std::cout << i << ",";
        }
        std::cout << std::endl;



        if (ps.output_vec == ps.program) {
            return a_try;
        }
        a_try++;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
    }  
}

int main() {
    std::string input = helpers::read_input("day17/input.txt");
    std::string example = R""""(Register A: 729
Register B: 0
Register C: 0

Program: 0,1,5,4,3,0)"""";
    std::string example2 = R""""(Register A: 2024
Register B: 0
Register C: 0

Program: 0,3,5,4,3,0)"""";
    std::cout << input << std::endl;
    std::cout << "Part 1: " << part1(input) << std::endl;
    std::cout << "Part 2: " << part2(input) << std::endl;
    return 0;
}