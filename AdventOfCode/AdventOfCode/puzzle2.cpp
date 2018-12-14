#include "puzzle2.hpp"
#include "AOCUtils.hpp"

#include <map>

int puzzle2::calculateChecksumPartOne(const std::vector<std::string> &fileContents) {
	int numTwo = 0;
	int numThree = 0;
	for(auto &line : fileContents) {
		std::map<char, int> lineChars;
		for(auto &lineChar : line) {
			if (lineChars.find(lineChar) == lineChars.end()) {
				lineChars[lineChar] = 1;
			} else {
				lineChars[lineChar] = lineChars[lineChar] + 1;
			}
		}
		bool hasTwo = false;
		bool hasThree = false;
		for (auto &lineChar : lineChars) {
			if (!hasTwo && lineChar.second == 2) {
				hasTwo = true;
				numTwo++;
			}
			if (!hasThree && lineChar.second == 3) {
				hasThree = true;
				numThree++;
			}
			if (hasTwo && hasThree) {
				break;
			}
		}
	}
	return numTwo * numThree;
}

std::string puzzle2::findMatchingBoxes(const std::vector<std::string> &fileContents) {
    for(auto &line : fileContents) {
        for (auto &otherLine : fileContents) {
            std::string commonString;
            for(int i = 0;i < line.size();i++) {
                if (line[i] == otherLine[i]) {
                    commonString.push_back(line[i]);
                }
            }
            if (commonString.size() == line.size() - 1) {
                return commonString;
            }
        }
    }
    return "No Match Found";
}

void puzzle2::runPuzzle(...) {
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle2_input.txt", fileContents);
    puzzle2 puzzle;
    int checkSum = puzzle.calculateChecksumPartOne(fileContents);
    std::string matchingBoxes = puzzle.findMatchingBoxes(fileContents);
    
    printf("Part One checksum is %d\n", checkSum);
    printf("Part Two matching box characters are %s\n", matchingBoxes.c_str());
}
