//
//  puzzle9.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle9_hpp
#define puzzle9_hpp

#include <string>
#include <vector>
#include <set>

#include "puzzle.hpp"
#include "IntCodeComputer.hpp"

class puzzle9 : puzzle {
public:
    static void runPuzzle(...);
    
private:
    void runPartOne(const std::vector<std::string> &fileContents);
    void runPartTwo(const std::vector<std::string> &fileContents);
};

#endif /* puzzle9_hpp */
