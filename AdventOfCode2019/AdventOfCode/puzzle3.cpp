#include "puzzle3.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle3::addWireOnGrid(int x, int y, std::map<int, std::map<int, int> > &grid, const int wireNum) {
    if (grid.find(x) == grid.end()) {
        grid[x] = std::map<int, int>();
        grid[x][y] = wireNum;
        return;
    }
    if (grid[x].find(y) == grid[x].end()) {
        grid[x][y] = wireNum;
        return;
    }
    if (grid[x][y] != wireNum) {
        int dist = abs(x) + abs(y);
        if (dist < minDist) {
            minDist = dist;
        }
    }
}

void puzzle3::moveWire(int &x, int &y, char dir, int dist, std::map<int, std::map<int, int> > &grid, const int wireNum) {
    int origX = x, origY = y;
    switch (dir) {
        case 'U':
            y += dist;
            for(int i = origY+1; i <= y;i++) {
                addWireOnGrid(origX, i, grid, wireNum);
            }
            break;
        case 'D':
            y -= dist;
            for(int i = origY-1; i >= y;i--) {
                addWireOnGrid(origX, i, grid, wireNum);
            }
            break;
        case 'L':
            x -= dist;
            for(int i = origX-1; i >= x;i--) {
                addWireOnGrid(i, origY, grid, wireNum);
            }
            break;
        case 'R':
            x += dist;
            for(int i = origX+1; i <= x;i++) {
                addWireOnGrid(i, origY, grid, wireNum);
            }
            break;
        default:
            printf("Invalid direction %c\n", dir);
            break;
    }
    
}

void puzzle3::parseWires(const std::vector<std::string> &fileContents, std::map<int, std::map<int, int> > &grid) {
    int wireNumber = 1;
    for (auto &line : fileContents) {
        int xPos = 0, yPos = 0;
        char dir = -1;
        for (int i = 0;i < line.size();i++) {
            char ch = line[i];
            switch (ch) {
                case ',':
                    break;
                case 'U':
                case 'D':
                case 'L':
                case 'R':
                    dir = ch;
                    break;
                default:
                    std::string dist = line.substr(i, line.find(',', i) - i);
                    i += dist.length();
                    moveWire(xPos, yPos, dir, atoi(dist.c_str()), grid, wireNumber);
                    dir = -1;
                    break;
            }
        }
        wireNumber++;
    }
}

void puzzle3::runPuzzle(...) {
    puzzle3 puzzle;
    std::vector<std::string> fileContents;
    std::map<int, std::map<int, int> > grid;
    AOCUtils::openAndReadFile("input_data/puzzle3_input.txt", fileContents);
    
    puzzle.parseWires(fileContents, grid);
    printf("Part One minimum distance is %d\n", puzzle.minDist);
    
//    int part1Total = puzzle.sumFuelForMasses(fileContents);
//    int part2Total = puzzle.sumFuelForMasses(fileContents, true);
//    
//    printf("Part One total fuel: %d\n", part1Total);
//    printf("Part Two total fuel: %d\n", part2Total);
}
