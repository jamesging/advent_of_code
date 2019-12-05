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
    int fuelForMass(const int mass, const bool withFuel = false);
    static void runPuzzle(...);
    
private:
    int sumFuelForMasses(const std::vector<std::string> &fileContents, const bool calcFuel = false);
};

#endif /* puzzle1_hpp */
