#include "puzzle2.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle2::runPartOne(const std::vector<std::string> &fileContents) {
    IntCodeComputer computer;
    computer.parseProgram(fileContents, 5);
    //magic input numbers from the puzzle: 12, 2
    computer.memory[1] = 12;
    computer.memory[2] = 2;
    
    
    printf("Part One program finished!\n");
    for (long long dataInt : computer.memory) {
        printf("%lld,", dataInt);
    }
    printf("\n");
}

void puzzle2::runPartTwo(const std::vector<std::string> &fileContents, const int goal) {
    IntCodeComputer computer;
    computer.parseProgram(fileContents, 5);
    
    for(int i = 0;i < 100;i++) {
        for (int j = 0; j < 100;j++) {
            std::vector<long long> dataCopy = computer.memory;
            dataCopy[1] = i;
            dataCopy[2] = j;
            if (dataCopy[0] == goal) {
                printf("Found the goal! %d and %d produce %lld\n", i, j, dataCopy[0]);
                printf("Part Two answer is %d\n", (100 * i) + j);
                return;
            }
        }
    }
}

void puzzle2::runPuzzle(...) {
    puzzle2 puzzle;
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle2_input.txt", fileContents);
    
    puzzle.runPartOne(fileContents);
    //magic puzzle goal number: 19690720
    puzzle.runPartTwo(fileContents, 19690720);
}
