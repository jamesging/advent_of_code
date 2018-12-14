//
//  puzzle6.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle6_h
#define puzzle6_h

#include "puzzle.hpp"

#include <map>
#include <vector>
#include <map>

class puzzle6 : puzzle {
public:
    static void runPuzzle(const int regionMaxDist = 32, ...);
    
private:
    static int regionDistance;
    
    class point;
    
    std::pair<point, bool> getClosestPoint(const point &fromPoint, const std::map<point, int> &points);
    bool isInfinite(const point &aPoint, const std::map<point, int> &points,
                    const int minX, const int maxX, const int minY, const int maxY);
    
    void parsePoints(const std::vector<std::string> &fileContents, std::vector<point> &points);
    void mapPoints(const std::vector<point> &coordinates, std::map<point, int> &points,
                   int &minX, int &maxX, int &minY, int &maxY);
    int findLargestRegion(const std::vector<point> &coordinates);
    size_t findDensestRegion(const std::vector<point> &coordinates);
};

#endif /* puzzle6_h */
