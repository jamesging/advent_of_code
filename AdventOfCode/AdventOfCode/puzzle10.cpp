//
//  puzzle10.cpp
//  AdventOfCode
//
//  Created by James Ging on 12/12/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#include "puzzle10.hpp"
#include "AOCUtils.hpp"

#include <iostream>
#include <set>

class puzzle10::point {
public:
    int x, y;
    point(int _x, int _y):x(_x),y(_y) {}
    
    point operator-(const point &other) const {
        return point(abs(x - other.x), abs(y - other.y));
    }

    void operator+=(const point &other) {
        x += other.x;
        y += other.y;
    }
    
    void operator-=(const point &other) {
        x -= other.x;
        y -= other.y;
    }
    
    bool operator==(const point &other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const point &other) const {
        return x != other.x || y != other.y;
    }
    
    bool operator<(const point &right) const {
        if (x < right.x) {
            return true;
        } else if (x == right.x && y < right.y) {
            return true;
        }
        return false;
    }
    
    int manhattanDist(const point &other) const {
        point diff = *this - other;
        return diff.x + diff.y;
    }
};

class puzzle10::lightPoint {
public:
    point current, velocity;

    lightPoint(point _origin, point _velocity):current(_origin),velocity(_velocity) {}

    void doStep() {
        current += velocity;
    }
    
    void unStep() {
        current -= velocity;
    }

    bool operator==(const lightPoint &other) const {
        return current == other.current && velocity == other.velocity;
    }
    
    bool operator!=(const lightPoint &other) const {
        return current != other.current || velocity != other.velocity;
    }
    
    bool operator<(const lightPoint &right) const {
        if (current < right.current) {
            return true;
        } else if (current == right.current && velocity < right.velocity) {
            return true;
        }
        return false;
    }
};

int puzzle10::valueFromString(const std::string &str) const {
    return atoi(&str[0]);
}

puzzle10::point puzzle10::parsePointFromString(const std::string &str) const {
    size_t posXIdx = str.find_first_of('<')+1;
    std::string posXStr = str.substr(posXIdx, str.find_first_of(',') - posXIdx);
    int posX = valueFromString(posXStr);
    size_t posYIdx = str.find_first_of(',')+1;
    std::string posYStr = str.substr(posYIdx, str.size() - posYIdx);
    int posY = valueFromString(posYStr);
    return point(posX, posY);
}

void puzzle10::parsePoints(const std::vector<std::string> &fileContents, std::vector<lightPoint> &points) {
    //position=< 9,  1> velocity=< 0,  2>
    for (auto &line : fileContents) {
        std::string posStr = line.substr(0, line.find_first_of('>'));
        size_t velIdx = line.find("velocity");
        std::string velStr = line.substr(velIdx, line.size() - (velIdx+1));
        points.push_back(lightPoint(parsePointFromString(posStr), parsePointFromString(velStr)));
    }
}

void puzzle10::calculateAABB(const std::vector<lightPoint> &points, int &minX, int &maxX, int &minY, int &maxY) {
    std::set<point> currPoints;
    for (auto &point : points) {
        currPoints.insert(point.current);
    }
    return calculateAABB(currPoints, minX, maxX, minY, maxY);
}

void puzzle10::calculateAABB(const std::set<point> &points, int &minX, int &maxX, int &minY, int &maxY) {
    for (auto &point : points) {
        if (point.x > maxX) {
            maxX = point.x;
        }
        if (point.x < minX) {
            minX = point.x;
        }
        if (point.y < minY) {
            minY = point.y;
        }
        if (point.y > maxY) {
            maxY = point.y;
        }
    }
}

size_t puzzle10::findPointRegions(const std::vector<lightPoint> &points, std::vector<std::set<puzzle10::point> > &regions) {
    std::set<point> currPoints;
    for (auto &point : points) {
        currPoints.insert(point.current);
    }
    while (currPoints.size() > 8) {
        int regionsMade = 0;
        for(auto &point : currPoints) {
            std::set<puzzle10::point> pointRegion;
            pointRegion.insert(point);
            while (true) {
                int pointsAdded = 0;
                for (auto &other : currPoints) {
                    if (pointRegion.find(other) != pointRegion.end()) {
                        continue;
                    }
                    for (auto &regionPoint : pointRegion) {
                        if ((other.x == regionPoint.x-1 || other.x == regionPoint.x+1 || other.x == regionPoint.x)
                            && (other.y == regionPoint.y-1 || other.y == regionPoint.y+1 || other.y == regionPoint.y)) {
                            pointsAdded++;
                            pointRegion.insert(other);
                        }
                    }
                }
                if (pointsAdded == 0) {
                    break;
                }
            }
            if (pointRegion.size() > 1) {
                regions.push_back(pointRegion);
                for (auto &point : pointRegion) {
                    currPoints.erase(point);
                }
                regionsMade++;
                break;
            } else if (pointRegion.size() == 1) {
                regionsMade = 0;
                break;
            }
        }
        if (regionsMade == 0) {
            break;
        }
    }
    if(currPoints.size() == 0) {
        printf("All points accounted for in regions\n");
        for (auto &pointRegion : regions) {
            int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
            calculateAABB(pointRegion, minX, maxX, minY, maxY);
            printPoints(pointRegion, minX, maxX, minY, maxY);
        }
    }
    return currPoints.size();
}

void puzzle10::printPoints(const std::vector<lightPoint> &points, const int minX, const int maxX, const int minY, const int maxY) {
    std::set<point> currPoints;
    for (auto &point : points) {
        currPoints.insert(point.current);
    }
    printPoints(currPoints, minX, maxX, minY, maxY);
}

void puzzle10::printPoints(const std::set<point> &points, const int minX, const int maxX, const int minY, const int maxY) {
    printf("Printing %ld points\n", points.size());
    for (int y = minY;y <= maxY;y++) {
        for (int x = minX;x <= maxX;x++) {
            bool isPoint = false;
            for (auto &point : points) {
                if (point.x == x && point.y == y) {
                    printf("X");
                    isPoint = true;
                    break;
                }
            }
            if (!isPoint) {
                printf(".");
            }
        }
        printf("\n");
    }
}

void puzzle10::stepPoints(std::vector<lightPoint> &points) {
    int steps = 0;
    while(true) {
        for(auto &point : points) {
            point.doStep();
        }
        steps++;
        std::vector<std::set<puzzle10::point> > stepRegions;
        size_t wanderingPoints = findPointRegions(points, stepRegions);
        if (stepRegions.size() > 0) {
            printf("Found %ld regions in step %d\n", stepRegions.size(), steps);
        }
        if (wanderingPoints == 0 || steps > 40000) {
            std::string continueStepping;
            printf("On step %d with %ld wandering points, continue stepping(y/n)?\n?>\t", steps, wanderingPoints);
            std::cin >> continueStepping;
            if (continueStepping != "y" && continueStepping != "Y") {
                break;
            }
        }
    }
}

void puzzle10::runPuzzle(...) {
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle10_input.txt", fileContents);
    puzzle10 puzzle;

    std::vector<lightPoint> points;
    puzzle.parsePoints(fileContents, points);
    puzzle.stepPoints(points);
}
