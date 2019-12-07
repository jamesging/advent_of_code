//
//  puzzle5.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle5_hpp
#define puzzle5_hpp

#include <string>
#include <vector>
#include <set>

#include "puzzle.hpp"
#include "IntCodeComputer.hpp"

class puzzle5 : puzzle {
public:
    static void runPuzzle(...);
    
private:
    void runPartOne(std::vector<IntCodeComputer::opcode> &opcodes, std::vector<int> &data);
};

#endif /* puzzle5_hpp */
