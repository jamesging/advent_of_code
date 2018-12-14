//
//  puzzle11.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/14/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle11_hpp
#define puzzle11_hpp

#include <stdio.h>

#include "puzzle.hpp"

#include <map>
#include <vector>

class puzzle11 : puzzle {
public:
    static void runPuzzle(const int _serialNum = 8);
    
protected:
    class fuelCell;
    class grid;
    
    static int serialNum;

    int getRegionPower(const grid &powerGrid, const int startX, const int startY, const int size);
    std::pair<int, int> findBestRegion(const grid &puzzleGrid);
    std::pair<int, std::pair<int, int>> findBestRegionPartTwo(const grid &puzzleGrid);
};

#endif /* puzzle11_hpp */
