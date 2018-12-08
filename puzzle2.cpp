#include <stdio.h>
#include <fstream>
#include <istream>
#include <map>
#include <vector>
#include <string>

int processFileContents(std::vector<std::string> &fileContents) {
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

int openAndReadFile(std::string fileName) {
        std::filebuf fb;
        std::vector<std::string> fileContents;
        if (fb.open(fileName, std::ios::in)) {
                std::istream fileStream(&fb);
                std::string currLine;
                while(std::getline(fileStream, currLine)) {
                        fileContents.push_back(currLine);
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
	int checkSum = openAndReadFile(argv[1]);

	printf("Checksum is %d\n", checkSum);
	return 0;
}
