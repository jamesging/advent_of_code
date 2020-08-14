//
//  puzzle10.cpp
//  AdventOfCode
//
//  Created by James Ging on 8/13/20.
//  Copyright © 2020 James Ging. All rights reserved.
//

#include "puzzle10.hpp"
#include "AOCUtils.hpp"

#include <cmath>

static const int targetAsteroidNumber = 200;

puzzle10::asteroid *puzzle10::bestBase = nullptr;

void puzzle10::runPartOne(const std::vector<std::string> &fileContents, std::vector<asteroid> &asteroids) {
    bestBase = &(asteroids.front());
    for (asteroid &anAsteroid : asteroids) {
        if (anAsteroid.visibleAsteroids.size() > bestBase->visibleAsteroids.size()) {
            bestBase = &anAsteroid;
        }
    }
    printf("Base asteroid can see %ld asteroids, and %ld asteroids are obscured. There are %ld asteroids total\n",
           bestBase->visibleAsteroids.size(), bestBase->obscuredAsteroids.size(), asteroids.size());
}

void puzzle10::runPartTwo(const std::vector<std::string> &fileContents, std::vector<asteroid> &asteroids) {
    bestBase->calculateLaserOrder();
}

void puzzle10::mapAsteroids(const std::vector<std::string> &fileContents, std::vector<asteroid> &asteroids) {
    int yVal = 0;
    for (const std::string &row : fileContents) {
        int xVal = 0;
        for (const char coord : row) {
            if (coord == '#') {
                asteroids.push_back(asteroid(xVal, yVal));
            }
            xVal++;
        }
        yVal++;
    }
}

void puzzle10::calculateVisibleAsteroids(std::vector<asteroid> &asteroids) {
    for (auto asteroidIter = asteroids.begin(); asteroidIter != asteroids.end(); asteroidIter++) {
        asteroid &anAsteroid = *asteroidIter;
        for (auto checkIter = asteroids.begin(); checkIter != asteroids.end(); checkIter++) {
            anAsteroid.checkAsteroidVisible(*checkIter, asteroids);
        }
    }
}

void puzzle10::asteroid::calculateLaserOrder() {
    float laserAngle = 0.f / (180 / PI);
    size_t totalAsteroids = visibleAsteroids.size() + obscuredAsteroids.size();
    while (destroyedAsteroids.size() < totalAsteroids) {
        laserAngle = fireLaser(laserAngle, visibleAsteroids);
    }
}

float puzzle10::asteroid::fireLaser(float laserAngle, std::set<const asteroid *> &remainingAsteroids) {
    std::map<float, const asteroid *> closestAsteroids;
    for (const asteroid *anAsteroid : remainingAsteroids) {
        if (anAsteroid == this) {
            continue;
        }
        float angle = asOriginAngle(*anAsteroid);
        bool aheadOfLaser = angle > laserAngle;
        if (!aheadOfLaser) {
            continue;
        }
        
        auto currentClosest = closestAsteroids.find(angle);
        
        if (currentClosest != closestAsteroids.end()) {
            if (distance(*(*currentClosest).second) < angle) {
                continue;
            }
        }
        closestAsteroids[angle] = anAsteroid;
    }
    if (closestAsteroids.size() <= 0) {
        return 0.f;
    }
    const asteroid *closestAsteroid = (*(closestAsteroids.begin())).second;
    if (destroyedAsteroids.size() + 1 == targetAsteroidNumber) {
        printf("Removing asteroid %d, %d at number %ld\n", closestAsteroid->x, closestAsteroid->y, destroyedAsteroids.size() + 1);
    }
    destroyedAsteroids.push_back(closestAsteroid);
    
    std::vector<const asteroid *> clearedAsteroids;
    
    for (auto &obscuredIter : obscuredAsteroids) {
        std::vector<const asteroid *> &obscuredBy = obscuredIter.second;
        obscuredBy.erase(std::remove_if(obscuredBy.begin(), obscuredBy.end(), [obscuredIter, closestAsteroid](const asteroid *obscuring) {
            return obscuring == closestAsteroid;
        }), obscuredBy.end());
        if (obscuredBy.size() == 0) {
            visibleAsteroids.insert(obscuredIter.first);
            clearedAsteroids.push_back(obscuredIter.first);
        }
    }
    for (const asteroid *cleared: clearedAsteroids) {
        obscuredAsteroids.erase(obscuredAsteroids.find(cleared));
    }
    
    remainingAsteroids.erase(remainingAsteroids.find(closestAsteroid));
    
    float firedAngle = asOriginAngle(*closestAsteroid) + EPSILON;
    closestAsteroids.erase(closestAsteroids.begin());
    return firedAngle;
}

bool puzzle10::asteroid::checkAsteroidVisible(asteroid &other, std::vector<asteroid> &asteroids, const bool saveResult) {
    if (other == *this) {
        return false;
    }
    if (saveResult && alreadyChecked(other)) {
        return true;
    }
    float ourDist = distance(other);
    bool obscured = false;
    for (asteroid &anAsteroid : asteroids) {
        if (anAsteroid == other || anAsteroid == *this) {
            continue;
        }
        float distMe = distance(anAsteroid);
        float distOther = other.distance(anAsteroid);
        if (((distMe + distOther) - ourDist) < EPSILON) {
            if (saveResult) {
                if (obscuredAsteroids.find(&other) == obscuredAsteroids.end()) {
                    obscuredAsteroids[&other] = std::vector<const asteroid *>();
                }
                obscuredAsteroids[&other].push_back(&anAsteroid);
                if (!alreadyKnownVisible(anAsteroid)) {
                    checkAsteroidVisible(anAsteroid, asteroids);
                }
            } else {
                return true;
            }
            obscured = true;
        }
    }
    
    if (saveResult && !obscured) {
        visibleAsteroids.insert(&other);
        other.visibleAsteroids.insert(this);
    }
    return false;
}

bool puzzle10::asteroid::alreadyChecked(const asteroid &other) const {
    if (alreadyKnownVisible(other)) {
        return true;
    }
    return obscuredAsteroids.find(&other) != obscuredAsteroids.end();
}

bool puzzle10::asteroid::alreadyKnownVisible(const asteroid &other) const {
    return visibleAsteroids.find(&other) != visibleAsteroids.end();
}

void puzzle10::runPuzzle(...) {
    puzzle10 puzzle;
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle10_input.txt", fileContents);
    
    std::vector<asteroid> asteroids;
    puzzle.mapAsteroids(fileContents, asteroids);
    
    puzzle.calculateVisibleAsteroids(asteroids);
    
    puzzle.runPartOne(fileContents, asteroids);
    puzzle.runPartTwo(fileContents, asteroids);
}
