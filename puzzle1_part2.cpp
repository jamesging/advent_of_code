#include <stdio.h>
#include <string>
#include <istream>
#include <fstream>
#include <set>
#include <vector>

bool valueIsPositive(std::string str) {
        if (str.front() == '-') {
                return false;
        }
        return true;
}

int valueFromString(std::string str) {
	return atoi(&str[1]);
}

int processFileContents(std::vector<std::string> &fileContents,
	std::set<int> &pastFrequencies, int total) {
	for(auto &currLine : fileContents) { 
        	total += valueIsPositive(currLine)
                	? valueFromString(currLine)
                	: -1 * valueFromString(currLine);
                if (pastFrequencies.find(total) != pastFrequencies.end()) {
                	return total;
                }
		pastFrequencies.insert(total);
	}
	return processFileContents(fileContents, pastFrequencies, total);
}

int openAndReadFile(std::string fileName) {
        std::filebuf fb;
	std::set<int> pastFrequencies;
	std::vector<std::string> fileContents;
        if (fb.open(fileName, std::ios::in)) {
                std::istream fileStream(&fb);
		std::string currLine;
		while(std::getline(fileStream, currLine)) {
			fileContents.push_back(currLine);
		}
		return processFileContents(fileContents, pastFrequencies, 0);
        }
	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Incorrect usage. Try: puzzle1_part2 [Input file name]\n");
		return 1;
	}
	int total = openAndReadFile(argv[1]);

	printf("Repeated value: %d\n", total);
	return 0;
}
