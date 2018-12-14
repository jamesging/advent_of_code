#include "puzzle8.hpp"
#include "AOCUtils.hpp"

#include <map>
#include <set>

int puzzle8::totalNodes = 0;

class puzzle8::node {
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

std::pair<int, int> puzzle8::parseNodes(const std::vector<std::string> &fileContents) {
	int totalMetadata = 0;
    int partTwoSum = 0;
	for(auto &line : fileContents) {
		std::vector<int> plateContents;
		size_t startIndex = 0;
		size_t endIndex = 0;
		
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
        partTwoSum += lineNode.calculatePartTwoSum();
	}
    return std::make_pair(totalMetadata, partTwoSum);
}

void puzzle8::runPuzzle(...) {
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle8_input.txt", fileContents);
    puzzle8 puzzle;
    std::pair<int, int> calculations = puzzle.parseNodes(fileContents);

	printf("Part one sum is %d\n", calculations.first);
	printf("Part two sum is %d\n", calculations.second);
}
