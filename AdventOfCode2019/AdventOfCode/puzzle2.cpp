#include "puzzle2.hpp"
#include "AOCUtils.hpp"
#include <math.h>

puzzle2::opcode::opcode(std::vector<int> ints) {
    if (ints.size() != OPCODE_SIZE) {
        printf("ERROR invalid number of ints %ld, expected %d!\n", ints.size(), OPCODE_SIZE);
        return;
    }
    instruction = ints[0];
    input1 = ints[1];
    input2 = ints[2];
    output = ints[3];
}

bool puzzle2::opcode::operate(std::vector<int> &data) const {
    switch (instruction) {
        case OPCODE_HALT:
            return false;
        case OPCODE_ADD:
            add(data);
            return true;
        case OPCODE_MULT:
            mult(data);
            return true;
    }
    return false;
}

void puzzle2::opcode::add(std::vector<int> &data) const {
    int addResult = data[input1] + data[input2];
    data[output] = addResult;
}

void puzzle2::opcode::mult(std::vector<int> &data) const {
    int multResult = data[input1] * data[input2];
    data[output] = multResult;
}

void puzzle2::parseOpcodes(const std::vector<std::string> &fileContents, std::vector<opcode> &opcodes, std::vector<int> &data) {
    std::vector<int> opcode_ints;
    for (auto &line : fileContents) {
        size_t startPos = 0, endPos = line.find_first_of(',', startPos);
        while (startPos != std::string::npos && startPos < endPos) {
            data.push_back(atoi(line.substr(startPos, endPos).c_str()));
            opcode_ints.push_back(data.back());
            if (opcode_ints.size() == 1 && opcode_ints.front() == opcode::OPCODE_HALT) {
                opcodes.push_back(opcode(opcode_ints.front(), -1, -1, -1));
                opcode_ints.clear();
            }
            if (opcode_ints.size() == opcode::OPCODE_SIZE) {
                opcodes.push_back(opcode(opcode_ints));
                opcode_ints.clear();
            }
            
            startPos = endPos+1;
            endPos = line.find_first_of(',', startPos);
            if (endPos == std::string::npos) {
                endPos = line.length()-1;
            }
        }
        
    }
}

void puzzle2::runPartOne(const std::vector<puzzle2::opcode> &opcodes, std::vector<int> data) {
    //magic input numbers from the puzzle: 12, 2
    data[1] = 12;
    data[2] = 2;
    
    for(auto &code : opcodes) {
        if (!code.operate(data)) {
            printf("Part One program finished!\n");
            for (int dataInt : data) {
                printf("%d,", dataInt);
            }
            printf("\n");
            break;
        }
    }
}

void puzzle2::runPartTwo(const std::vector<puzzle2::opcode> &opcodes, const int goal, std::vector<int> data) {
    for(int i = 0;i < 100;i++) {
        for (int j = 0; j < 100;j++) {
            std::vector<int> dataCopy = data;
            dataCopy[1] = i;
            dataCopy[2] = j;
            for(auto &code : opcodes) {
                if (!code.operate(dataCopy)) {
                    if (dataCopy[0] == goal) {
                        printf("Found the goal! %d and %d produce %d\n", i, j, dataCopy[0]);
                        printf("Part Two answer is %d\n", (100 * i) + j);
                        return;
                    }
                    break;
                }
            }
        }
    }
}

void puzzle2::runPuzzle(...) {
    puzzle2 puzzle;
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle2_input.txt", fileContents);
    std::vector<puzzle2::opcode> opcodes;
    std::vector<int> data;
    puzzle.parseOpcodes(fileContents, opcodes, data);
    puzzle.runPartOne(opcodes, data);
    //magic puzzle goal number: 19690720
    puzzle.runPartTwo(opcodes, 19690720, data);
}
