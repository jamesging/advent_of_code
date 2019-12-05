//
//  puzzle12.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/14/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle12_hpp
#define puzzle12_hpp

#include <stdio.h>

#include "puzzle.hpp"

#include <list>
#include <vector>
#include <string>

class puzzle12 : puzzle {
public:
    static void runPuzzle(const long numGenerations = 20);
    
protected:
    class cellRule;
    
    void buildInitialState(const std::vector<std::string> &fileContents, std::vector<bool> &initialState);
    void parseCellRules(const std::vector<std::string> &fileContents, std::vector<cellRule> &rules);
    std::list<bool> runGenerations(const std::vector<bool> &initialState,
                                   const std::vector<cellRule> &rules, const long numGenerations);
};

#endif /* puzzle12_hpp */
