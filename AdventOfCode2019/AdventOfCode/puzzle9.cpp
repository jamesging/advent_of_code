#include "puzzle9.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle9::runPuzzle(...) {
    puzzle9 puzzle;
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle9_input.txt", fileContents);
    
    IntCodeComputer computer;
    computer.parseProgram(fileContents, 1);
    for(auto &i : computer.outputStream) {
        printf("%lld,", i);
    }
    printf("\n");
}
