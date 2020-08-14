#include "puzzle9.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle9::runPartOne(const std::vector<std::string> &fileContents) {
    IntCodeComputer computer;
    computer.parseProgram(fileContents, 1);
    printf("Part one result:\n");
    for(auto &i : computer.outputStream) {
        printf("%lld,", i);
    }
    printf("\n");
}

void puzzle9::runPartTwo(const std::vector<std::string> &fileContents) {
    IntCodeComputer computer;
    computer.parseProgram(fileContents, 2);
    printf("Part two result:\n");
    for(auto &i : computer.outputStream) {
        printf("%lld,", i);
    }
    printf("\n");
}


void puzzle9::runPuzzle(...) {
    puzzle9 puzzle;
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle9_input.txt", fileContents);
    
    puzzle.runPartOne(fileContents);
    puzzle.runPartTwo(fileContents);
}
