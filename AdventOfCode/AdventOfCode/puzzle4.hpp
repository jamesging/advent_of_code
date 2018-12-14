//
//  puzzle4.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle4_h
#define puzzle4_h

#include "puzzle.hpp"

#include <string>
#include <map>

class puzzle4 : puzzle {
public:
    static void runPuzzle(...);
    
private:
    int parseMinutesFromString(const std::string &str);
    void parseGuardSchedules(const std::vector<std::string> &fileContents, std::map<int,
                             std::map<int, int> > &guardSchedule);
    std::pair<int, int> laziestGuard(const std::map<int, std::map<int, int> > &sleepingGuards);
    std::pair<int, int> laziestGuardPartTwo(const std::map<int, std::map<int, int> > &sleepingGuards);
};

#endif /* puzzle4_h */
