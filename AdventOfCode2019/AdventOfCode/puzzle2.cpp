#include "puzzle2.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle2::runPartOne(const std::vector<IntCodeComputer::opcode> &opcodes, std::vector<int> data) {
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

void puzzle2::runPartTwo(const std::vector<IntCodeComputer::opcode> &opcodes, const int goal, std::vector<int> data) {
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
    std::vector<IntCodeComputer::opcode> opcodes;
    std::vector<int> data;
    IntCodeComputer::parseOpcodes(fileContents, opcodes, data);
    puzzle.runPartOne(opcodes, data);
    //magic puzzle goal number: 19690720
    puzzle.runPartTwo(opcodes, 19690720, data);
}
