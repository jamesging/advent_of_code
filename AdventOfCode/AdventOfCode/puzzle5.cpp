#include "puzzle5.hpp"
#include "AOCUtils.hpp"

#include <set>

int puzzle5::findAndRemoveCombo(std::string &str, const int startPos) {
	for(int i = startPos < 0 ? 0 : startPos;i < str.size();i++) {
		char atI = str[i];
		if (i == str.size() - 1) {
			break;
		}
		char next = str[i+1];
		if (atI == next+32 || atI == next-32) {
			str.erase(i, 2);
			if (i == 0 || i == 1) {
				return 0;
			}
			return i - 1;
		}
	}
	return -1;
}

void puzzle5::findAndRemoveUnit(std::string &str, char removeMe) {
	auto newEnd = std::remove_if(str.begin(), str.end(), [removeMe](char c) {
		return c == removeMe || c == removeMe+32 || c == removeMe-32;
	});
	str.erase(newEnd, str.end());
}

size_t puzzle5::reducePolymerPartTwo(const std::vector<std::string> &fileContents) {
    std::string line = fileContents[0];
    std::set<char> distinctUnits;
    for(auto &lineChar : line) {
        if (distinctUnits.find(lineChar) != distinctUnits.end()
            || distinctUnits.find(lineChar+32) != distinctUnits.end()
            || distinctUnits.find(lineChar-32) != distinctUnits.end()) {
            continue;
        }
        distinctUnits.insert(lineChar);
    }
    size_t minSize = line.size();
    for(auto &setChar : distinctUnits) {
        std::string lineCopy = line;
        findAndRemoveUnit(lineCopy, setChar);
        lineCopy.shrink_to_fit();
        
        int i = 0;
        while((i = findAndRemoveCombo(lineCopy, i)) >= 0) {
        }
        size_t currSize = lineCopy.size();
        if (currSize < minSize) {
            minSize = currSize;
        }
    }
    return minSize;
}

size_t puzzle5::reducePolymerPartOne(const std::vector<std::string> &fileContents) {
    std::string line = fileContents[0];
    int i = 0;
    while((i = findAndRemoveCombo(line, i)) >= 0) {}
    return line.size();
}

void puzzle5::runPuzzle(...) {
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle5_input.txt", fileContents);
    puzzle5 puzzle;
    
    size_t partOnePolymerSize = puzzle.reducePolymerPartOne(fileContents);
    size_t partTwoPolymerSize = puzzle.reducePolymerPartTwo(fileContents);

	printf("Part one polymer is %ld units long\n", partOnePolymerSize);
	printf("Part two polymer is %ld units long\n", partTwoPolymerSize);
}
