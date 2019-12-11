#include "puzzle5.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle5::runPartOne(const std::vector<std::string> &fileContents) {
    IntCodeComputer computer;
    std::vector<int> data;
    computer.parseProgram(fileContents, data, 1);
    
    printf("output:\n");
    for (int i : computer.outputStream) {
        printf("%d,", i);
    }
    printf("\n");
}

void puzzle5::runPartTwo(const std::vector<std::string> &fileContents) {
    IntCodeComputer computer;
    std::vector<int> data;
    computer.parseProgram(fileContents, data, 5);
    
    printf("output:\n");
    for (int i : computer.outputStream) {
        printf("%d,", i);
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
