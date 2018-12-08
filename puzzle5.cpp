#include <stdio.h>
#include <fstream>
#include <istream>
#include <map>
#include <set>
#include <vector>
#include <string>

int findAndRemoveCombo(std::string &str, int startPos) {
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

void findAndRemoveUnit(std::string &str, char removeMe) {
	auto newEnd = std::remove_if(str.begin(), str.end(), [removeMe](char c) {
		return c == removeMe || c == removeMe+32 || c == removeMe-32;
	});
	str.erase(newEnd, str.end());
}

int processFileContentsPartTwo(std::vector<std::string> &fileContents) {
	for(auto &line : fileContents) {
		std::set<char> distinctUnits;
		for(auto &lineChar : line) {
			if (distinctUnits.find(lineChar) != distinctUnits.end()
				|| distinctUnits.find(lineChar+32) != distinctUnits.end()
				|| distinctUnits.find(lineChar-32) != distinctUnits.end()) {
				continue;
			}
			distinctUnits.insert(lineChar);
		}
		int minSize = line.size();
		for(auto &setChar : distinctUnits) {
			std::string lineCopy = line;
			findAndRemoveUnit(lineCopy, setChar);
			lineCopy.shrink_to_fit();
			
			int i = 0;
			while((i = findAndRemoveCombo(lineCopy, i)) >= 0) {
			}
			int currSize = lineCopy.size();
			if (currSize < minSize) {
				minSize = currSize;
			}
		}
		return minSize;
	}
	return 0;
}

int processFileContents(std::vector<std::string> &fileContents) {
        for(auto &line : fileContents) {
		int i = 0;
		while((i = findAndRemoveCombo(line, i)) >= 0) {
		}
                return line.size();
        }
        return 0;
}

int openAndReadFile(std::string fileName, bool partTwo = false) {
        std::filebuf fb;
        std::vector<std::string> fileContents;
        if (fb.open(fileName, std::ios::in)) {
                std::istream fileStream(&fb);
                std::string currLine;
                while(std::getline(fileStream, currLine)) {
                        fileContents.push_back(currLine);
                }
		fb.close();
		if (partTwo) {
			return processFileContentsPartTwo(fileContents);
		}
                return processFileContents(fileContents);
        }
        return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
                printf("Incorrect usage. Try: puzzle2 [Input file name]\n");
                return 1;
        }
	int polymerSize = openAndReadFile(argv[1]);
	int partTwoSize = openAndReadFile(argv[1], true);

	printf("polymer is %d units long\n", polymerSize);
	printf("part two polymer is %d units long\n", partTwoSize);
	return 0;
}
