//
//  puzzle3.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle3_hpp
#define puzzle3_hpp

#include <string>
#include <vector>
#include <map>
#include <set>

#include "puzzle.hpp"

class puzzle3 : puzzle {
public:
    int minDist = INT_MAX;
    
    static void runPuzzle(...);
    
private:
    void parseWires(const std::vector<std::string> &fileContents, std::map<int, std::map<int, int> > &grid);
    void addWireOnGrid(int x, int y, std::map<int, std::map<int, int> > &grid, const int wireNum);
    void moveWire(int &x, int &y, char dir, int dist, std::map<int, std::map<int, int> > &grid, const int wireNum);
};

#endif /* puzzle3_hpp */
