//
//  puzzle3.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle3_h
#define puzzle3_h

#include "puzzle.hpp"

#include <vector>
#include <string>
#include <map>

class puzzle3 : puzzle {
public:
    static void runPuzzle(...);

private:
    class box;
    class point;
    
    void parseBoxParts(const std::string &line, std::vector<std::string> &boxParts);
    void buildBox(std::map<int, box> &boxes, const std::vector<std::string> &boxParts);
    void buildBoxes(const std::vector<std::string> &fileContents, std::map<int, box> &boxes);
    std::pair<int, int> calculateOverlappingArea(const std::map<int, box> &boxes);
};

#endif /* puzzle3_h */
