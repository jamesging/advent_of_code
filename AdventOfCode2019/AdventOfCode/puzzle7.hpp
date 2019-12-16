//
//  puzzle7.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle7_hpp
#define puzzle7_hpp

#include <string>
#include <vector>
#include <set>

#include "puzzle.hpp"
#include "IntCodeComputer.hpp"

class puzzle7 : puzzle {
public:
    static void runPuzzle(...);
    
private:
    struct amplifier {
        IntCodeComputer computer;
        int phase_setting;
        long long input;
        
    public:
        amplifier(int phase, long long in): phase_setting(phase), input(in) {};
        amplifier(int phase): phase_setting(phase) {};
        
        std::vector<long long> &amplify(const std::vector<std::string> &program);
    };
    
    void buildPhaseSettings(std::vector<std::vector<int> > &phases, const int min, const int max);
    
    void runPartOne(const std::vector<std::string> &fileContents);
    void runPartTwo(const std::vector<std::string> &fileContents);
};

#endif /* puzzle7_hpp */
