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
const IntCodeComputer::opcode::opcode_inst IntCodeComputer::opcode::OFFSET = opcode_inst(OPCODE_OFFSET, 2);
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
        case OPCODE_OFFSET:
            return OFFSET;
        default:
            printf("Invalid opcode instruction id %d\n", parsed_instruction);
            break;
    }
    return opcode_inst();
}

IntCodeComputer::opcode::opcode(const int ptr, const std::vector<long long> &data) {
    int instruction = (int)data[ptr];
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

bool IntCodeComputer::opcode::operate(IntCodeComputer &computer) const {
    switch (get_instruction_type((int)computer.memory[computer.inst_ptr]).inst) {
        case OPCODE_HALT:
            computer.halted = true;
            return false;
        case OPCODE_ADD:
            add(computer);
            return true;
        case OPCODE_MULT:
            mult(computer);
            return true;
        case OPCODE_SAVE:
            return save(computer);
        case OPCODE_OUTPUT:
            output(computer);
            return true;
        case OPCODE_JMPT:
            jump(computer, true);
            return true;
        case OPCODE_JMPF:
            jump(computer, false);
            return true;
        case OPCODE_LT:
            less_than(computer);
            return true;
        case OPCODE_EQ:
            equals(computer);
            return true;
        case OPCODE_OFFSET:
            offset_addr_base(computer);
            return true;
    }
    return false;
}

void IntCodeComputer::opcode::add(IntCodeComputer &computer) const {
    long long inputOne = computer.fetchData(computer.inst_ptr+1, modes[0]);
    long long inputTwo = computer.fetchData(computer.inst_ptr+2, modes[1]);
    long long addResult = inputOne + inputTwo;
    computer.storeData(computer.inst_ptr+3, modes[2], addResult);
    computer.inst_ptr += 4;
}

void IntCodeComputer::opcode::mult(IntCodeComputer &computer) const {
    long long inputOne = computer.fetchData(computer.inst_ptr+1, modes[0]);
    long long inputTwo = computer.fetchData(computer.inst_ptr+2, modes[1]);
    long long multResult = inputOne * inputTwo;
    computer.storeData(computer.inst_ptr+3, modes[2], multResult);
    computer.inst_ptr += 4;
}

bool IntCodeComputer::opcode::save(IntCodeComputer &computer) const {
    if (computer.waitForInput && !computer.user_input.size()) {
        computer.waiting = true;
        return false;
    }
    if (!computer.user_input.size()) {
        return false;
    }
    computer.storeData(computer.inst_ptr+1, modes[0], computer.user_input.back());
    computer.user_input.pop_back();
    computer.inst_ptr += 2;
    return true;
}

void IntCodeComputer::opcode::output(IntCodeComputer &computer) const {
    computer.outputStream.push_back(computer.fetchData(computer.inst_ptr+1, modes[0]));
    computer.inst_ptr += 2;
}

void IntCodeComputer::opcode::jump(IntCodeComputer &computer, bool if_not_zero) const {
    bool nonZero = computer.fetchData(computer.inst_ptr+1, modes[0]);
    long long newPtr = computer.inst_ptr + 3;
    if ((if_not_zero && nonZero) || (!if_not_zero && !nonZero)) {
        newPtr = computer.fetchData(computer.inst_ptr+2, modes[1]);
    }
    computer.inst_ptr = (int)newPtr;
}

void IntCodeComputer::opcode::less_than(IntCodeComputer &computer) const {
    long long inputOne = computer.fetchData(computer.inst_ptr+1, modes[0]);
    long long inputTwo = computer.fetchData(computer.inst_ptr+2, modes[1]);
    long long result = 0;
    if (inputOne < inputTwo) {
        result = 1;
    }
    computer.storeData(computer.inst_ptr+3, modes[2], result);
    
    computer.inst_ptr += 4;
}

void IntCodeComputer::opcode::equals(IntCodeComputer &computer) const {
    long long inputOne = computer.fetchData(computer.inst_ptr+1, modes[0]);
    long long inputTwo = computer.fetchData(computer.inst_ptr+2, modes[1]);
    int result = 0;
    if (inputOne == inputTwo) {
        result = 1;
    }
    computer.storeData(computer.inst_ptr+3, modes[2], result);
    
    computer.inst_ptr += 4;
}

void IntCodeComputer::opcode::offset_addr_base(IntCodeComputer &computer) const {
    long long inputOne = computer.fetchData(computer.inst_ptr+1, modes[0]);
    computer.addr_base += inputOne;
    if (computer.addr_base < 0) {
        printf("what the hell happened here?\n");
    }
    computer.inst_ptr += 2;
}

void IntCodeComputer::parseProgram(const std::vector<std::string> &fileContents,
                                   const long long input) {
    user_input.push_back(input);
    opcode_inst instruction_type;
    for (auto &line : fileContents) {
        size_t startPos = 0, endPos = line.find_first_of(',', startPos);
        while (startPos != std::string::npos && startPos <= endPos) {
            memory.push_back(atol(line.substr(startPos, endPos).c_str()));
            startPos = endPos+1;
            endPos = line.find_first_of(',', startPos);
            if (endPos == std::string::npos) {
                endPos = line.length()-1;
            }
        }
    }
    continueProcessing();
}

void IntCodeComputer::continueProcessing() {
    int instructions_run = 0;
    while (opcode(inst_ptr, memory).operate(*this)) {
        //        printf("Pointer: %d\n", inst_ptr);
        //        for(int i = 0; i < data.size();i++) {
        //            printf("%d: %d\n", i, data[i]);
        //        }
        //        printf("\n");
        instructions_run++;
        if (instructions_run % 1000 == 0) {
            printf("Computer has run %d instructions since continuing\n", instructions_run);
        }
    }
}

const long long IntCodeComputer::fetchData(int ptr, int mode) {
    switch (mode) {
        case 0:
            checkAndExpandMemory(ptr, mode);
            return memory[memory[ptr]];
        case 1:
            checkAndExpandMemory(ptr, mode);
            return memory[ptr];
        case 2:
            checkAndExpandMemory(ptr, mode);
            return memory[memory[ptr] + addr_base];
        default:
            printf("Invalid memory mode %d\n", mode);
            return -1;
    };
}

void IntCodeComputer::storeData(int ptr, int mode, long long data) {
    checkAndExpandMemory(ptr, mode);
    if (mode < 2) {
        memory[memory[ptr]] = data;
    } else {
        memory[memory[ptr] + addr_base] = data;
    }
}

void IntCodeComputer::checkAndExpandMemory(int ptr, int mode) {
    if (ptr >= memory.size() || memory[ptr] >= memory.size()) {
        if (ptr >= memory.size()) {
            long long slotsToAdd = ptr - memory.size();
            if (slotsToAdd <= 0) {
                for (int i = 0;i < slotsToAdd;i++) {
                    memory.push_back(0);//super slow, but for some reason .resize gives allocation errors
                }
            }
        }
        if (mode == 0) {
            if (memory[ptr] >= memory.size()) {
                long long slotsToAdd = memory[ptr] - memory.size();
                if (slotsToAdd > 0) {
                    for (int i = 0;i < slotsToAdd;i++) {
                        memory.push_back(0);
                    }
                }
            }
        }
        if (mode == 2) {
            if (memory[ptr] + addr_base >= memory.size()) {
                long long slotsToAdd = (memory[ptr] + addr_base) - memory.size();
                if (slotsToAdd > 0) {
                    for (int i = 0;i < slotsToAdd;i++) {
                        memory.push_back(0);
                    }
                }
            }
        }
    }
}
