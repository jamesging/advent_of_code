//
//  IntCodeComputer.cpp
//  AdventOfCode
//
//  Created by James Ging on 12/6/19.
//  Copyright © 2019 James Ging. All rights reserved.
//

#include <string>

#include "IntCodeComputer.hpp"

typedef IntCodeComputer::opcode::opcode_inst opcode_inst;

const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::ADD = opcode_inst(OPCODE_ADD, 3);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::MULT = opcode_inst(OPCODE_MULT, 3);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::SAVE = opcode_inst(OPCODE_SAVE, 1);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::OUTPUT = opcode_inst(OPCODE_OUTPUT, 1);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::JMPT = opcode_inst(OPCODE_JMPT, 2);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::JMPF = opcode_inst(OPCODE_JMPF, 2);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::LT = opcode_inst(OPCODE_LT, 3);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::EQ = opcode_inst(OPCODE_EQ, 3);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::HALT = opcode_inst(OPCODE_HALT, 0);

opcode_inst IntCodeComputer::opcode::get_instruction_type(const int instruction) {
    int parsed_instruction = instruction;
    if (instruction > OPCODE_HALT) {
        char inst_buffer[50];
        snprintf(inst_buffer, 50, "%d", instruction);
        std::string str_instruction = std::string(inst_buffer);
        str_instruction = str_instruction.substr(str_instruction.length() - 2, 2);
        parsed_instruction = atoi(str_instruction.c_str());
    }
    switch (parsed_instruction) {
        case OPCODE_ADD:
            return ADD;
        case OPCODE_MULT:
            return MULT;
        case OPCODE_SAVE:
            return SAVE;
        case OPCODE_OUTPUT:
            return OUTPUT;
        case OPCODE_HALT:
            return HALT;
        case OPCODE_JMPT:
            return JMPT;
        case OPCODE_JMPF:
            return JMPF;
        case OPCODE_LT:
            return LT;
        case OPCODE_EQ:
            return EQ;
        default:
            printf("Invalid opcode instruction id %d\n", parsed_instruction);
            break;
    }
    return opcode_inst();
}

IntCodeComputer::opcode::opcode(const int ptr, const std::vector<int> &data) {
    pointer = ptr;
    int instruction = data[ptr];
    opcode_inst instruction_type = opcode::get_instruction_type(instruction);
    
    modes.insert(modes.begin(), instruction_type.param_count, 0);
    
    if (instruction > OPCODE_HALT) {
        char inst_buffer[50];
        snprintf(inst_buffer, 50, "%d", instruction);
        std::string str_instruction = std::string(inst_buffer);
        str_instruction = str_instruction.substr(0, str_instruction.length() - 2);
        while (str_instruction.size() < instruction_type.param_count) {
            str_instruction.insert(str_instruction.begin(), '0');
        }
        for (int i = (instruction_type.param_count-1);i >= 0;i--) {
            int mode = str_instruction[i] - '0';
            modes[(instruction_type.param_count-1)-i] = mode;
        }
    }
}

bool IntCodeComputer::opcode::operate(IntCodeComputer &computer, std::vector<int> &data) const {
    switch (get_instruction_type(data[pointer]).inst) {
        case OPCODE_HALT:
            return false;
        case OPCODE_ADD:
            add(computer, data);
            return true;
        case OPCODE_MULT:
            mult(computer, data);
            return true;
        case OPCODE_SAVE:
            save(computer, data);
            return true;
        case OPCODE_OUTPUT:
            output(computer, data);
            return true;
        case OPCODE_JMPT:
            jump(computer, data, true);
            return true;
        case OPCODE_JMPF:
            jump(computer, data, false);
            return true;
        case OPCODE_LT:
            less_than(computer, data);
            return true;
        case OPCODE_EQ:
            equals(computer, data);
            return true;
    }
    return false;
}

void IntCodeComputer::opcode::add(IntCodeComputer &computer, std::vector<int> &data) const {
    int inputOne = computer.fetchData(data, pointer+1, modes[0]);
    int inputTwo = computer.fetchData(data, pointer+2, modes[1]);
    int addResult = inputOne + inputTwo;
    data[data[pointer+3]] = addResult;
    computer.inst_ptr += 4;
}

void IntCodeComputer::opcode::mult(IntCodeComputer &computer, std::vector<int> &data) const {
    int inputOne = computer.fetchData(data, pointer+1, modes[0]);
    int inputTwo = computer.fetchData(data, pointer+2, modes[1]);
    int multResult = inputOne * inputTwo;
    data[data[pointer+3]] = multResult;
    computer.inst_ptr += 4;
}

void IntCodeComputer::opcode::save(IntCodeComputer &computer, std::vector<int> &data) const {
    data[data[pointer+1]] = computer.user_input;
    computer.inst_ptr += 2;
}

void IntCodeComputer::opcode::output(IntCodeComputer &computer, std::vector<int> &data) const {
    computer.outputStream.push_back(computer.fetchData(data, pointer+1, modes[0]));
    computer.inst_ptr += 2;
}

void IntCodeComputer::opcode::jump(IntCodeComputer &computer, std::vector<int> &data, bool if_not_zero) const {
    bool nonZero = computer.fetchData(data, pointer+1, modes[0]);
    int newPtr = pointer + 3;
    if ((if_not_zero && nonZero) || (!if_not_zero && !nonZero)) {
        newPtr = computer.fetchData(data, pointer+2, modes[1]);
    }
    computer.inst_ptr = newPtr;
}

void IntCodeComputer::opcode::less_than(IntCodeComputer &computer, std::vector<int> &data) const {
    int inputOne = computer.fetchData(data, pointer+1, modes[0]);
    int inputTwo = computer.fetchData(data, pointer+2, modes[1]);
    int result = 0;
    if (inputOne < inputTwo) {
        result = 1;
    }
    data[data[pointer+3]] = result;
    
    computer.inst_ptr += 4;
}

void IntCodeComputer::opcode::equals(IntCodeComputer &computer, std::vector<int> &data) const {
    int inputOne = computer.fetchData(data, pointer+1, modes[0]);
    int inputTwo = computer.fetchData(data, pointer+2, modes[1]);
    int result = 0;
    if (inputOne == inputTwo) {
        result = 1;
    }
    data[data[pointer+3]] = result;
    
    computer.inst_ptr += 4;
}

void IntCodeComputer::parseProgram(const std::vector<std::string> &fileContents,
                                   std::vector<int> &data,
                                   const int input) {
    user_input = input;
    opcode_inst instruction_type;
    for (auto &line : fileContents) {
        size_t startPos = 0, endPos = line.find_first_of(',', startPos);
        while (startPos != std::string::npos && startPos <= endPos) {
            data.push_back(atoi(line.substr(startPos, endPos).c_str()));
            startPos = endPos+1;
            endPos = line.find_first_of(',', startPos);
            if (endPos == std::string::npos) {
                endPos = line.length()-1;
            }
        }
    }
    int instructions_run = 0;
    while (data[inst_ptr] != opcode::OPCODE_HALT) {
//        printf("Pointer: %d\n", inst_ptr);
//        for(int i = 0; i < data.size();i++) {
//            printf("%d: %d\n", i, data[i]);
//        }
//        printf("\n");
        opcode(inst_ptr, data).operate(*this, data);
        instructions_run++;
        if (instructions_run % 1000 == 0) {
            printf("Computer has run %d instructions\n", instructions_run);
        }
    }
}

const int IntCodeComputer::fetchData(const std::vector<int> &data, int ptr, int mode) {
    return mode ? data[ptr] : data[data[ptr]];
}
