#include <stdio.h>
#include <fstream>
#include <istream>
#include <map>
#include <set>
#include <vector>
#include <string>

static int totalNodes = 0;

class node {
public:
	std::vector<int> nodeInts;
	std::vector<node> childNodes;
	std::vector<int> metadataNodes;
	int childNodeCount;
	int metadataNodeCount;
	int metadataSum = 0;

	node(std::vector<int>::iterator &it) {
		totalNodes++;
		childNodeCount = *it++;
		metadataNodeCount = *it++;
		calculateChildNodes(it);
		for (int i = 0;i < metadataNodeCount;i++) {
			metadataNodes.push_back(*it);
			metadataSum += *it++;
		}
	};

	void calculateChildNodes(std::vector<int>::iterator &it) {
		while (childNodes.size() < childNodeCount) {
			childNodes.push_back(it);
		}
	}

	int calculateTreeMetadataSum() const {
		int totalSum = metadataSum;
		for (auto &childNode : childNodes) {
			totalSum += childNode.calculateTreeMetadataSum();
		}
		return totalSum;
	}

	int calculatePartTwoSum() const {
		int partTwoSum = 0;
		if (childNodeCount > 0) {
			for (auto &metadataInt : metadataNodes) {
				if (childNodes.size() >= metadataInt) {
					partTwoSum += childNodes[metadataInt-1].calculatePartTwoSum();
				}
			}
		} else {
			return metadataSum;
		}
		return partTwoSum;
	}
};

int processFileContents(std::vector<std::string> &fileContents) {
	int totalMetadata = 0;
	for(auto &line : fileContents) {
		std::vector<int> plateContents;
		int startIndex = 0;
		int endIndex = 0;
		
		while ((endIndex = line.find_first_of(' ', startIndex)) != line.npos) {
			std::string intStr = line.substr(startIndex, endIndex - startIndex);
			plateContents.push_back(std::stoi(intStr));
			startIndex = endIndex+1;
		}
		if (endIndex == line.npos) {
			std::string intStr = line.substr(startIndex, line.size()-startIndex);
                        plateContents.push_back(std::stoi(intStr));
		}
		auto it = plateContents.begin();
		node lineNode(it);
		totalMetadata += lineNode.calculateTreeMetadataSum();
	}
	return totalMetadata;
}

int processFileContentsPartTwo(std::vector<std::string> &fileContents) {
	int totalMetadata = 0;
        for(auto &line : fileContents) {
                std::vector<int> plateContents;
                int startIndex = 0;
                int endIndex = 0;

                while ((endIndex = line.find_first_of(' ', startIndex)) != line.npos) {
                        std::string intStr = line.substr(startIndex, endIndex - startIndex);
                        plateContents.push_back(std::stoi(intStr));
                        startIndex = endIndex+1;
                }
                if (endIndex == line.npos) {
                        std::string intStr = line.substr(startIndex, line.size()-startIndex);
                        plateContents.push_back(std::stoi(intStr));
                }
                auto it = plateContents.begin();
                node lineNode(it);
                totalMetadata += lineNode.calculatePartTwoSum();
        }
        return totalMetadata;
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
                printf("Incorrect usage. Try: puzzle8 [Input file name]\n");
                return 1;
        }
	int metadataSum = openAndReadFile(argv[1]);
	int partTwoSum = openAndReadFile(argv[1], true);

	printf("Metadata sum is %d\n", metadataSum);
	printf("Part two sum is %d\n", partTwoSum);
	return 0;
}
