//
//  puzzle2.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle2_h
#define puzzle2_h

#include <string>
#include <vector>

#include "puzzle.hpp"

class puzzle2 : puzzle {
public:
    static void runPuzzle(...);
    
private:
    int calculateChecksumPartOne(const std::vector<std::string> &fileContents);
    std::string findMatchingBoxes(const std::vector<std::string> &fileContents);
};

#endif /* puzzle2_h */
