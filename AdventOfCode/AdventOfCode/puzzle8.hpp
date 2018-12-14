//
//  puzzle8.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/12/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle8_h
#define puzzle8_h

#include "puzzle.hpp"

#include <vector>
#include <string>

class puzzle8 : puzzle {
public:
    static void runPuzzle(...);
    
protected:
    class node;
    
    static int totalNodes;
    
    std::pair<int, int> parseNodes(const std::vector<std::string> &fileContents);
};

#endif /* puzzle8_h */
