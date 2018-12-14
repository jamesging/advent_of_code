//
//  puzzle5.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle5_h
#define puzzle5_h

#include "puzzle.hpp"

#include <string>
#include <vector>

class puzzle5 : puzzle {
public:
    static void runPuzzle(...);
    
private:
    int findAndRemoveCombo(std::string &str, const int startPos);
    void findAndRemoveUnit(std::string &str, char removeMe);
    size_t reducePolymerPartOne(const std::vector<std::string> &fileContents);
    size_t reducePolymerPartTwo(const std::vector<std::string> &fileContents);
};

#endif /* puzzle5_h */
