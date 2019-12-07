//
//  puzzle4.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle4_hpp
#define puzzle4_hpp

#include <string>
#include <vector>
#include <set>

#include "puzzle.hpp"

class puzzle4 : puzzle {
public:
    static void runPuzzle(...);
    
private:
    static const size_t PW_BUFFER_SIZE = 7;//6 characters plus null terminator
    
    void satisfiesCriteria(const int password, int &validCount, int &validCountPartTwo);
};

#endif /* puzzle4_hpp */
