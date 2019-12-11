//
//  puzzle2.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle2_hpp
#define puzzle2_hpp

#include <string>
#include <vector>
#include <set>

#include "puzzle.hpp"
#include "IntCodeComputer.hpp"

class puzzle2 : puzzle {
public:
    static void runPuzzle(...);
    
private:
    void runPartOne(const std::vector<std::string> &fileContents);
    void runPartTwo(const std::vector<std::string> &fileContents, const int goal);
};

#endif /* puzzle2_hpp */
