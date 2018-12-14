//
//  puzzle10.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/12/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle10_hpp
#define puzzle10_hpp

#include "puzzle.hpp"

#include <set>
#include <vector>
#include <string>

class puzzle10 : puzzle {
public:
    static void runPuzzle(...);

protected:
    class point;
    class lightPoint;
    
    int valueFromString(const std::string &str) const;
    point parsePointFromString(const std::string &str) const;
    void parsePoints(const std::vector<std::string> &fileContents, std::vector<lightPoint> &points);
    void calculateAABB(const std::vector<lightPoint> &points, int &minX, int &maxX, int &minY, int &maxY);
    void calculateAABB(const std::set<point> &points, int &minX, int &maxX, int &minY, int &maxY);
    size_t findPointRegions(const std::vector<lightPoint> &points, std::vector<std::set<point> > &regions);
    void printPoints(const std::vector<lightPoint> &points, const int minX, const int maxX, const int minY, const int maxY);
    void printPoints(const std::set<point> &points, const int minX, const int maxX, const int minY, const int maxY);
    void stepPoints(std::vector<lightPoint> &points);
};

#endif /* puzzle10_hpp */
