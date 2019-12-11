#include "puzzle2.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle2::runPartOne(const std::vector<std::string> &fileContents) {
    IntCodeComputer computer;
    std::vector<int> data;
    computer.parseProgram(fileContents, data, 5);
    //magic input numbers from the puzzle: 12, 2
    data[1] = 12;
    data[2] = 2;
    
    
    printf("Part One program finished!\n");
    for (int dataInt : data) {
        printf("%d,", dataInt);
    }
    printf("\n");
}

void puzzle2::runPartTwo(const std::vector<std::string> &fileContents, const int goal) {
    IntCodeComputer computer;
    std::vector<int> data;
    computer.parseProgram(fileContents, data, 5);
    
    for(int i = 0;i < 100;i++) {
        for (int j = 0; j < 100;j++) {
            std::vector<int> dataCopy = data;
            dataCopy[1] = i;
            dataCopy[2] = j;
            if (dataCopy[0] == goal) {
                printf("Found the goal! %d and %d produce %d\n", i, j, dataCopy[0]);
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
