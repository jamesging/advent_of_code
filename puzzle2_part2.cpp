#include <stdio.h>
#include <fstream>
#include <istream>
#include <map>
#include <vector>
#include <string>

std::string processFileContents(std::vector<std::string> &fileContents) {
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

std::string openAndReadFile(std::string fileName) {
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
	std::string commonString = openAndReadFile(argv[1]);

	printf("Answer is %s\n", commonString.c_str());
	return 0;
}
