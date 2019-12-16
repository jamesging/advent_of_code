//
//  puzzle8.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle8_hpp
#define puzzle8_hpp

#include <string>
#include <vector>
#include <set>
#include <map>

#include "puzzle.hpp"

class puzzle8 : puzzle {
public:
    static void runPuzzle(...);
    
private:
    typedef std::map<int, std::map<int, int> > layer;
    
    void parsePixels(const std::vector<std::string> &fileContents, std::vector<layer> &layers, int width, int height);
    void drawImage(std::vector<layer> &layers);
};

#endif /* puzzle8_hpp */
