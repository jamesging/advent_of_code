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

const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::ADD = opcode_inst(OPCODE_ADD, 4);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::MULT = opcode_inst(OPCODE_MULT, 4);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::SAVE = opcode_inst(OPCODE_SAVE, 2);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::OUTPUT = opcode_inst(OPCODE_OUTPUT, 2);
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::HALT = opcode_inst(OPCODE_HALT, 1);

std::vector<int> IntCodeComputer::outputStream;

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
        default:
            printf("Invalid opcode instruction id %d\n", parsed_instruction);
            break;
    }
    return opcode_inst();
}

IntCodeComputer::opcode::opcode(const opcode_inst &instruction_type, std::vector<int> ints) {
    if (ints.size() != instruction_type.size) {
        printf("ERROR invalid number of ints %ld, expected %d!\n", ints.size(), instruction_type.size);
        return;
    }
    params = ints;
    
    if (params[0] > OPCODE_HALT) {
        char inst_buffer[50];
        snprintf(inst_buffer, 50, "%d", params[0]);
        std::string str_instruction = std::string(inst_buffer);
        str_instruction = str_instruction.substr(0, str_instruction.length() - 2);
        while (str_instruction.size() < ints.size() - 1) {
            str_instruction.insert(str_instruction.begin(), '0');
        }
        for (int i = ((int)ints.size()-2);i >= 0;i--) {
            int mode = str_instruction[i] - '0';
            modes.push_back(mode);
        }
        params[0] = instruction_type.inst;
    }
}

bool IntCodeComputer::opcode::operate(std::vector<int> &data) const {
    switch (params[0]) {
        case OPCODE_HALT:
            return false;
        case OPCODE_ADD:
            add(data);
            return true;
        case OPCODE_MULT:
            mult(data);
            return true;
        case OPCODE_SAVE:
            save(data);
            return true;
        case OPCODE_OUTPUT:
            output(data);
            return true;
    }
    return false;
}

void IntCodeComputer::opcode::add(std::vector<int> &data) const {
    int inputOne = (modes.size() > 0 && modes[0]) ? params[1] : data[params[1]];
    int inputTwo = (modes.size() > 1 && modes[1]) ? params[2] : data[params[2]];
    int addResult = inputOne + inputTwo;
    data[params[3]] = addResult;
}

void IntCodeComputer::opcode::mult(std::vector<int> &data) const {
    int inputOne = (modes.size() > 0 && modes[0]) ? params[1] : data[params[1]];
    int inputTwo = (modes.size() > 1 && modes[1]) ? params[2] : data[params[2]];
    int multResult = inputOne * inputTwo;
    data[params[3]] = multResult;
}

void IntCodeComputer::opcode::save(std::vector<int> &data) const {
    data[params[1]] = input;
}

void IntCodeComputer::opcode::output(std::vector<int> &data) const {
    int outputData = (modes.size() > 0 && modes[0]) ? params[1] : data[params[1]];
    outputStream.push_back(outputData);
//    printf("output: %d\n", outputData);
}

void IntCodeComputer::parseOpcodes(const std::vector<std::string> &fileContents,
                                   std::vector<opcode> &opcodes,
                                   std::vector<int> &data,
                                   const int input) {
    std::vector<int> opcode_ints;
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
        for (int i = 0; i < data.size();i++) {
            printf("%d: %d\n", i, data[i]);
        }
        printf("\n");
        for (int i : data) {
//            printf("%d\n", i);
            opcode_ints.push_back(i);
            if (opcode_ints.size() == 1) {
                instruction_type = opcode::get_instruction_type(opcode_ints[0]);
            }
            if (instruction_type.size == -1) {
                opcode_ints.clear();
            } else if (opcode_ints.size() == instruction_type.size) {
                opcodes.push_back(opcode(instruction_type, opcode_ints));
                if (instruction_type.inst == opcode::OPCODE_SAVE) {
                    printf("Storing input: %d\n", input);
                    opcodes.back().input = input;
                }
                opcodes.back().operate(data);
                opcode_ints.clear();
            }
        }
    }
}
