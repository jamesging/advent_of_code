#include "puzzle5.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle5::runPartOne(std::vector<IntCodeComputer::opcode> &opcodes, std::vector<int> &data) {
    for (int i = 0; i < data.size();i++) {
        printf("%d: %d\n", i, data[i]);
    }
    printf("\n");
    
    printf("output:\n");
    for (int i : IntCodeComputer::outputStream) {
        printf("%d,", i);
    }
    printf("\n");
}

void puzzle5::runPuzzle(...) {
    puzzle5 puzzle;
    std::vector<std::string> fileContents;
    int puzzleInput = 1;
    AOCUtils::openAndReadFile("input_data/puzzle5_input.txt", fileContents);
    std::vector<IntCodeComputer::opcode> opcodes;
    std::vector<int> data;
    IntCodeComputer::parseOpcodes(fileContents, opcodes, data, puzzleInput);
    
    puzzle.runPartOne(opcodes, data);
}
