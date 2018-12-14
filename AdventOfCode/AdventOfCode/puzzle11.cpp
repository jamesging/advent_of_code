//
//  puzzle11.cpp
//  AdventOfCode
//
//  Created by James Ging on 12/14/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#include "puzzle11.hpp"

#include <math.h>
#include <list>

int puzzle11::serialNum;

class puzzle11::fuelCell {
public:
    int x, y;
    int power;
    fuelCell(int _x, int _y):x(_x),y(_y),power(getPowerLevel()) { };
    
    int getRackId() const {
        return x + 10;
    }
    
    int getPowerLevel() const {
        int rackId = getRackId();
        int powerLevel = (rackId * y) + serialNum;
        powerLevel *= rackId;
        powerLevel = floor((powerLevel / 100) % 10) - 5;
        return powerLevel;
    }
};

class puzzle11::grid {
public:
    std::map<int, std::vector<fuelCell> > fuelCells;
    std::map<int, std::map<int, int> > xSums;
    
    void buildGrid() {
        for (int i = 0;i < 300;i++) {
            for (int j = 0;j < 300;j++) {
                fuelCells[i].push_back(fuelCell(i, j));
            }
        }
    }
    
    void calcSums() {
        for (int x = 0;x < fuelCells.size();x++) {
            int xSum = 0;
            for (int y = 0;y < fuelCells[x].size();y++) {
                xSum += fuelCells[x][y].power;
                xSums[x][y] = xSum;
            }
        }
    }
};

int puzzle11::getRegionPower(const grid &powerGrid, const int startX, const int startY, const int size) {
    int totalPower = 0;
    for (int x = startX;x < startX+size;x++) {
        int min = startY == 0 ? 0 : powerGrid.xSums.at(x).at(startY-1);
        int max = powerGrid.xSums.at(x).at(startY+(size-1));
        totalPower += (max - min);
    }
    
    return totalPower;
}

std::pair<int, int> puzzle11::findBestRegion(const grid &puzzleGrid) {
    std::pair<int, int> bestPair = std::make_pair(1, 1);
    int bestPairPower = 0;
    for (int i = 0;i < 298;i++) {
        for (int j = 0;j < 298;j++) {
            int regionPower = getRegionPower(puzzleGrid, i, j, 3);
            if (regionPower > bestPairPower) {
                bestPair = std::make_pair(i, j);
                bestPairPower = regionPower;
            }
        }
    }
    return bestPair;
}

std::pair<int, std::pair<int, int>> puzzle11::findBestRegionPartTwo(const grid& puzzleGrid) {
    std::pair<int, int> bestPair = std::make_pair(1, 1);
    int bestPairPower = 0;
    int bestPairSize = 0;
    for (int i = 0;i < 300;i++) {
        for (int j = 0;j < 300;j++) {
            int maxSize = i > j ? 300 - i : 300 - j;
            for (int k = 0;k <= maxSize;k++) {
                int regionPower = getRegionPower(puzzleGrid, i, j, k);
                if (regionPower > bestPairPower) {
                    bestPair = std::make_pair(i, j);
                    bestPairPower = regionPower;
                    bestPairSize = k;
                }
            }
        }
    }
    printf("Best pair power for part two was %d\n", bestPairPower);
    return std::make_pair(bestPairSize, bestPair);
}

void puzzle11::runPuzzle(const int _serialNum) {
    serialNum = _serialNum;
    puzzle11 puzzle;
    grid puzzleGrid;
    puzzleGrid.buildGrid();
    puzzleGrid.calcSums();
    
    std::pair<int, int> mostPower = puzzle.findBestRegion(puzzleGrid);
    std::pair<int, std::pair<int, int> > mostPowerPartTwo = puzzle.findBestRegionPartTwo(puzzleGrid);
    int partTwoSize = mostPowerPartTwo.first;
    int partTwoX = mostPowerPartTwo.second.first;
    int partTwoY = mostPowerPartTwo.second.second;

    printf("The most region power for serial number %d is %d,%d\n", serialNum, mostPower.first, mostPower.second);
    printf("The most region power for serial number %d part two is at %d,%d with size %d\n",
           serialNum, partTwoX, partTwoY, partTwoSize);
}
