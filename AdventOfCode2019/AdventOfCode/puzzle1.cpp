#include "puzzle1.hpp"
#include "AOCUtils.hpp"
#include <math.h>

int puzzle1::fuelForMass(int mass, const bool calcFuel) {
    int massFuel = floor(mass/3)-2;
    if (calcFuel) {
        int fuelFuel = fuelForMass(massFuel, false);
        while (fuelFuel > 0) {
            massFuel += fuelFuel;
            fuelFuel = fuelForMass(fuelFuel, false);
        }
    }
    return massFuel;
}

int puzzle1::sumFuelForMasses(const std::vector<std::string> &fileContents, const bool calcFuel) {
    int totalMass = 0;
    for (auto &line : fileContents) {
        int mass = atoi(&line[0]);
        totalMass += fuelForMass(mass, calcFuel);
    }
    return totalMass;
}

void puzzle1::runPuzzle(...) {
    puzzle1 puzzle;
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle1_input.txt", fileContents);
    
    int part1Total = puzzle.sumFuelForMasses(fileContents);
    int part2Total = puzzle.sumFuelForMasses(fileContents, true);
    
    printf("Part One total fuel: %d\n", part1Total);
    printf("Part Two total fuel: %d\n", part2Total);
}
