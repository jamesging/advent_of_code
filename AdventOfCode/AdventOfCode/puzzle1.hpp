//
//  puzzle1.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle1_hpp
#define puzzle1_hpp

#include <string>
#include <vector>
#include <set>

#include "puzzle.hpp"

class puzzle1 : puzzle {
public:
    bool valueIsPositive(const std::string &str) const;
    int valueFromString(const std::string &str) const;
    static void runPuzzle(...);
    
private:
    int runPart1(const std::vector<std::string> &fileContents);
    int runPart2(const std::vector<std::string> &fileContents,
                 std::set<int> &pastFrequencies, int total);
};

#endif /* puzzle1_hpp */
