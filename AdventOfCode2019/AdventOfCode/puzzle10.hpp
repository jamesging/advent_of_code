//
//  puzzle10.hpp
//  AdventOfCode
//
//  Created by James Ging on 8/13/20.
//  Copyright © 2020 James Ging. All rights reserved.
//

#ifndef puzzle10_hpp
#define puzzle10_hpp

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>

#include "puzzle.hpp"

#define PI 3.14159f
#define EPSILON 0.00001f

class puzzle10 : puzzle {
public:
    static void runPuzzle(...);
    
    struct asteroid {
        int x, y;
        std::set<const asteroid *> visibleAsteroids;
        std::map<const asteroid *, std::vector<const asteroid *> > obscuredAsteroids;
        std::vector<const asteroid *> destroyedAsteroids;
        
        asteroid(int _x, int _y): x(_x), y(_y) {};
        
        bool checkAsteroidVisible(asteroid &other, std::vector<asteroid> &asteroids, const bool saveResult = true);
        bool alreadyChecked(const asteroid &other) const;
        bool alreadyKnownVisible(const asteroid &other) const;
        
        float fireLaser(float laserAngle, std::set<const asteroid *> &remainingAsteroids);
        
        float asOriginAngle(const asteroid &other) const {
            float subX = other.x - x;
            float subY = other.y - y;
            
            float angle = std::atan2(subY, subX) + 1.5708f;
            if (angle < 0.f) {
                angle += 2 * PI;
            }
            
            return angle;
        }
        
    public:
        inline bool operator==(const asteroid &other) const {
            return other.x == x && other.y == y;
        }
        
        inline float distance(const asteroid &other) const {
            return std::abs(std::sqrt(std::pow(other.x - x, 2) + std::pow(other.y - y, 2)));
        }
        inline float distance(const asteroid *other) const {
            return std::abs(std::sqrt(std::pow(other->x - x, 2) + std::pow(other->y - y, 2)));
        }
        inline float distance(const float _x, const float _y) const {
            return std::abs(std::sqrt(std::pow(_x - x, 2) + std::pow(_y - y, 2)));
        }
        
        void calculateLaserOrder();
    };
    
private:
    static asteroid *bestBase;
    void mapAsteroids(const std::vector<std::string> &fileContents, std::vector<asteroid> &asteroids);
    void calculateVisibleAsteroids(std::vector<asteroid> &asteroids);
    void runPartOne(const std::vector<std::string> &fileContents, std::vector<asteroid> &asteroids);
    void runPartTwo(const std::vector<std::string> &fileContents, std::vector<asteroid> &asteroids);
};


#endif /* puzzle10_hpp */
