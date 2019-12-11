//
//  main.cpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#include <iostream>
#include "puzzle1.hpp"
#include "puzzle2.hpp"
#include "puzzle3.hpp"
#include "puzzle4.hpp"
#include "puzzle5.hpp"
#include "puzzle6.hpp"

int main(int argc, const char * argv[]) {
    while (true) {
        printf("Which puzzle do you want to run? Current options are [1-12].\nOr quit with 'q'\n?>\t");
        std::string readCommand;
        std::cin >> readCommand;
        if (readCommand == "q") {
            return 0;
        }
        int puzzleNum = std::stoi(readCommand);
        switch (puzzleNum) {
            case 1:
                puzzle1::runPuzzle();
                break;
            case 2:
                puzzle2::runPuzzle();
                break;
            case 3:
                puzzle3::runPuzzle();
                break;
            case 4:
                puzzle4::runPuzzle();
                break;
            case 5:
                puzzle5::runPuzzle();
                break;
            case 6:
                puzzle6::runPuzzle();
                break;
        }
    }
    return 0;
}
