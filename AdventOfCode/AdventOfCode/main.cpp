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
#include "puzzle7.hpp"
#include "puzzle8.hpp"
#include "puzzle9.hpp"
#include "puzzle10.hpp"

int main(int argc, const char * argv[]) {
    while (true) {
        printf("Which puzzle do you want to run? Current options are [1-10].\nOr quit with 'q'\n?>\t");
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
                puzzle6::runPuzzle(10000);
                break;
            case 7:
                puzzle7::runPuzzle();
                break;
            case 8:
                puzzle8::runPuzzle();
                break;
            case 9:
                puzzle9::runPuzzle(477, 70851, 23);
                break;
            case 10:
                puzzle10::runPuzzle();
                break;
        }
    }
    return 0;
}
