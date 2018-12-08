#include <stdio.h>
#include <fstream>
#include <istream>
#include <map>
#include <set>
#include <vector>
#include <string>

class boxPoint {
public:
	int x, y;
	
	boxPoint(int _x, int _y) {
		x = _x;
		y = _y;
	}

	bool operator==(const boxPoint &otherPoint) const {
		if (x == otherPoint.x && y == otherPoint.y) {
			return true;
		}
		return false;
	}

	bool operator<(const boxPoint &other) const {
		if (x < other.x) {
			return true;
		}
		if (x == other.x) {
			return y < other.y;
		}
		return false;
	}
};

class box {
protected:
	boxPoint topLeft, topRight, bottomLeft, bottomRight;
	int boxId;

public:
	box(int left, int top, int width, int height, int _boxId) :
		topLeft(left, top),
		topRight(left+width-1, top),
		bottomLeft(left, top+height-1),
		bottomRight(left+width-1, top+height-1),
		boxId(_boxId) {
	}

	bool contains(const boxPoint &point) const {
		if (point.x >= topLeft.x && point.x <= bottomRight.x) {
			if (point.y >= topLeft.y && point.y <= bottomRight.y) {
				return true;
			}
		}
		return false;
	}

	std::set<boxPoint> overlapArea(const box &otherBox) const {
		std::set<boxPoint> retVal; 
		for(int x = topLeft.x; x <= topRight.x;x++) {
			for(int y = topLeft.y; y <= bottomRight.y;y++) {
				if (otherBox.contains(boxPoint(x, y))) {
					retVal.insert(boxPoint(x, y));
				}
			}
		}
		return retVal;
	}

	void printBox() const {
		printf("Box %d: %d,%d %d,%d %d,%d %d,%d\n", boxId, topLeft.x, topLeft.y,
	topRight.x, topRight.y, bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y);
		for (int y = 0;y <= bottomLeft.y+1;y++) {
			for (int x = 0;x <= topRight.x+1;x++) {
				if (x >= topLeft.x && y >= topLeft.y
					&& x <= topRight.x && y <= bottomLeft.y) {
					printf("%d", boxId);
				} else {
					printf(".");
				}
			}
			printf("\n");
		}
	}
};

int processFileContents(std::vector<std::string> &fileContents) {
	std::map<int, box> boxes;
	for(auto &line : fileContents) {
		std::vector<std::string> boxParts;
		int i = 0, j = 0;
		while ((j = line.find_first_of(' ', i+1))) {
			boxParts.push_back(line.substr(i,
				j == line.npos
					? line.size() - i
					: (j - i))
			);
			if (j == line.npos) {
				break;
			}
			i = j+1;
		}
		int boxId = -1, x, y, width, height;
		for(auto &boxPart : boxParts) {
			if (boxPart == "@") {
				continue;
			}
			if (boxId == -1) {
				boxId = std::stoi(&boxPart[1]);
				continue;
			}
			if (boxPart.find(",") != boxPart.npos) {
				auto comma = boxPart.find(",");
				x = std::stoi(boxPart.substr(0, comma));
				y = std::stoi(boxPart.substr(comma + 1,
					(boxPart.size() - comma) - 1));
				continue;
			}
			if (boxPart.find("x") != boxPart.npos) {
				auto sizeX = boxPart.find("x");
				width = std::stoi(boxPart.substr(0, sizeX));
                                height = std::stoi(boxPart.substr(sizeX + 1,
					(boxPart.size() - sizeX) - 1));
				continue;
			}
		}
		boxes.emplace(std::make_pair(boxId, box(x, y, width, height, boxId)));
	}
	printf("Built %ld boxes\n", boxes.size());
	std::set<boxPoint> allOverlaps;
	for(auto &box : boxes) {
		bool boxOverlaps = false;
		//box.second.printBox();
		for(auto &otherBox : boxes) {
			if (otherBox.first == box.first) {
				continue;
			}
			std::set<boxPoint> overlap = box.second.overlapArea(otherBox.second);
			if (overlap.size() > 0) {
				boxOverlaps = true;
			}
			for(auto &overlapPoint : overlap) {
				if (allOverlaps.find(overlapPoint) == allOverlaps.end()) {
					allOverlaps.insert(overlapPoint);
				}
			}
		}
		if (!boxOverlaps) {
			printf("box %d doesn't overlap any other boxes\n", box.first);
		}
	}
				
	return allOverlaps.size();
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
	int overlappedArea = openAndReadFile(argv[1]);

	printf("Overlapping area is %d\n", overlappedArea);
	return 0;
}
