//
//  puzzle7.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/12/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle7_h
#define puzzle7_h

#include "puzzle.hpp"

#include <map>

class puzzle7 : puzzle {
public:
    static void runPuzzle(const int _workerCount = 5, const int _stepTime = 60);
    
protected:
    static int workerCount;
    static int stepTime;
    static int currentTime;
    
    class step;
    class worker;
    
    void addStepIfMissing(const char stepName, std::map<char, step> &steps);
    void runSteps(std::map<char, step> &steps, std::string &runOrder);
    void runStepsPartTwo(std::map<char, step> &steps, std::vector<worker> &workers,
                         std::string &runOrder, int &runTime);
    
    std::string parseInstructions(const std::vector<std::string> &fileContents);
    std::string parseInstructionsPartTwo(const std::vector<std::string> &fileContents);
};

#endif /* puzzle7_h */
