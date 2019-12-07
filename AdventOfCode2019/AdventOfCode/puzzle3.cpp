#include "puzzle3.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle3::addWireOnGrid(int x, int y, grid_map &grid, wire_dist &wires, const int wireNum) {
    wires[wireNum]++;
    
    if (grid.find(x) == grid.end()) {
        grid[x] = std::map<int, std::map<int, int> >();
        grid[x][y] = std::map<int, int>();
        grid[x][y][wireNum] = wires[wireNum];
        return;
    }
    
    if (grid[x].find(y) == grid[x].end()) {
        grid[x][y] = std::map<int, int>();
        grid[x][y][wireNum] = wires[wireNum];
        return;
    }
    
    if (grid[x][y].find(wireNum) == grid[x][y].end()) {
        grid[x][y][wireNum] = wires[wireNum];
    }
    
    if (wires.size() > 1) {
        bool hasAllWires = true;
        int stepDist = 0;
        for (auto &wire : wires) {
            if (grid[x][y].find(wire.first) == grid[x][y].end()) {
                hasAllWires = false;
                break;
            }
            stepDist += grid[x][y][wire.first];
        }
        
        if (hasAllWires) {
            int dist = abs(x) + abs(y);
            if (dist < minDist) {
                minDist = dist;
            }
            if (stepDist < minSteps) {
                minSteps = stepDist;
            }
        }
    }
}

void puzzle3::moveWire(int &x, int &y, char dir, int dist, grid_map &grid, wire_dist &wires, const int wireNum) {
    int origX = x, origY = y;
    switch (dir) {
        case 'U':
            y += dist;
            for(int i = origY+1; i <= y;i++) {
                addWireOnGrid(origX, i, grid, wires, wireNum);
            }
            break;
        case 'D':
            y -= dist;
            for(int i = origY-1; i >= y;i--) {
                addWireOnGrid(origX, i, grid, wires, wireNum);
            }
            break;
        case 'L':
            x -= dist;
            for(int i = origX-1; i >= x;i--) {
                addWireOnGrid(i, origY, grid, wires, wireNum);
            }
            break;
        case 'R':
            x += dist;
            for(int i = origX+1; i <= x;i++) {
                addWireOnGrid(i, origY, grid, wires, wireNum);
            }
            break;
        default:
            printf("Invalid direction %c\n", dir);
            break;
    }
    
}

void puzzle3::parseWires(const std::vector<std::string> &fileContents, grid_map &grid, wire_dist &wires) {
    int wireNumber = 1;
    for (auto &line : fileContents) {
        wires[wireNumber] = 0;
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
                    moveWire(xPos, yPos, dir, atoi(dist.c_str()), grid, wires, wireNumber);
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
    grid_map grid;
    wire_dist wires;
    AOCUtils::openAndReadFile("input_data/puzzle3_input.txt", fileContents);
    
    puzzle.parseWires(fileContents, grid, wires);
    printf("Part One minimum distance is %d\n", puzzle.minDist);
    printf("Part Two minimum steps is %d\n", puzzle.minSteps);
    
//    int part1Total = puzzle.sumFuelForMasses(fileContents);
//    int part2Total = puzzle.sumFuelForMasses(fileContents, true);
//    
//    printf("Part One total fuel: %d\n", part1Total);
//    printf("Part Two total fuel: %d\n", part2Total);
}
