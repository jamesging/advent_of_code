#include "puzzle5.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle5::runPartOne(const std::vector<std::string> &fileContents) {
    IntCodeComputer computer;
    computer.parseProgram(fileContents, 1);
    
    printf("output:\n");
    for (long i : computer.outputStream) {
        printf("%ld,", i);
    }
    printf("\n");
}

void puzzle5::runPartTwo(const std::vector<std::string> &fileContents) {
    IntCodeComputer computer;
    computer.parseProgram(fileContents, 5);
    
    printf("output:\n");
    for (long i : computer.outputStream) {
        printf("%ld,", i);
    }
    printf("\n");
}

void puzzle5::runPuzzle(...) {
    puzzle5 puzzle;
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle5_input.txt", fileContents);
    
    puzzle.runPartOne(fileContents);
    puzzle.runPartTwo(fileContents);
}
