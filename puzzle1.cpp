#include <stdio.h>
#include <string>
#include <istream>
#include <fstream>

bool valueIsPositive(std::string str) {
        if (str.front() == '-') {
                return false;
        }
        return true;
}

int valueFromString(std::string str) {
	return atoi(&str[1]);
}

int openAndReadFile(std::string fileName) {
        std::filebuf fb;
        if (fb.open(fileName, std::ios::in)) {
                std::istream fileStream(&fb);
                int total = 0;
                std::string currLine;
                while (std::getline(fileStream, currLine)) {
                        total += valueIsPositive(currLine)
                                ? valueFromString(currLine)
                                : -1 * valueFromString(currLine);
                } 
                return total;
        }
	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Incorrect usage. Try: puzzle1 [Input file name]\n");
		return 1;
	}
	int total = openAndReadFile(argv[1]);

	printf("Total value: %d\n", total);
	return 0;
}
