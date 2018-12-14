//
//  puzzle9.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/12/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle9_h
#define puzzle9_h

#include "puzzle.hpp"

#include <map>

class puzzle9 : puzzle {
public:
    static void runPuzzle(const int _numPlayers, const int _highestMarble, const int _scoringValue);
    
protected:
    static int numPlayers, highestMarble, scoringValue;
    
    std::pair<int, long> playMarbleGame();
};

#endif /* puzzle9_h */
