#include "puzzle1.hpp"
#include "AOCUtils.hpp"

bool puzzle1::valueIsPositive(const std::string &str) const {
        if (str.front() == '-') {
                return false;
        }
        return true;
}

int puzzle1::valueFromString(const std::string &str) const {
	return atoi(&str[1]);
}

int puzzle1::runPart1(const std::vector<std::string> &fileContents) {
    int total = 0;
    for(auto &line : fileContents) {
        total += valueIsPositive(line)
                ? valueFromString(line)
                : -1 * valueFromString(line);
    }
    return total;
}

int puzzle1::runPart2(const std::vector<std::string> &fileContents,
                      std::set<int> &pastFrequencies, int total) {
    while (true) {
        for(auto &line : fileContents) {
            total += valueIsPositive(line)
            ? valueFromString(line)
            : -1 * valueFromString(line);
            if (pastFrequencies.find(total) != pastFrequencies.end()) {
                return total;
            }
            pastFrequencies.insert(total);
        }
    }
    
    return 0;
}

void puzzle1::runPuzzle(...) {
    puzzle1 puzzle;
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle1_input.txt", fileContents);
    std::set<int> pastFrequencies;
    int part1Total = puzzle.runPart1(fileContents);
    int part2RepeatedTotal = puzzle.runPart2(fileContents, pastFrequencies, 0);
    
    printf("Part One total value: %d\n", part1Total);
    printf("Part Two repeated value: %d\n", part2RepeatedTotal);
}
