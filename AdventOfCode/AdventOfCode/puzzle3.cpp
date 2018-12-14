#include "puzzle3.hpp"

#include "AOCUtils.hpp"

#include <set>

class puzzle3::point {
public:
	int x, y;
	
	point(int _x, int _y) {
		x = _x;
		y = _y;
	}

	bool operator==(const point &otherPoint) const {
		if (x == otherPoint.x && y == otherPoint.y) {
			return true;
		}
		return false;
	}

	bool operator<(const point &other) const {
		if (x < other.x) {
			return true;
		}
		if (x == other.x) {
			return y < other.y;
		}
		return false;
	}
};

class puzzle3::box {
protected:
	point topLeft, topRight, bottomLeft, bottomRight;
	int boxId;

public:
	box(int left, int top, int width, int height, int _boxId) :
		topLeft(left, top),
		topRight(left+width-1, top),
		bottomLeft(left, top+height-1),
		bottomRight(left+width-1, top+height-1),
		boxId(_boxId) {
	}

	bool contains(const point &point) const {
		if (point.x >= topLeft.x && point.x <= bottomRight.x) {
			if (point.y >= topLeft.y && point.y <= bottomRight.y) {
				return true;
			}
		}
		return false;
	}

	std::set<point> overlapArea(const box &otherBox) const {
		std::set<point> retVal; 
		for(int x = topLeft.x; x <= topRight.x;x++) {
			for(int y = topLeft.y; y <= bottomRight.y;y++) {
				if (otherBox.contains(point(x, y))) {
					retVal.insert(point(x, y));
				}
			}
		}
		return retVal;
	}

	void printBox() const {
		printf("Box %d: %d,%d %d,%d %d,%d %d,%d\n", boxId, topLeft.x, topLeft.y,
               topRight.x, topRight.y, bottomLeft.x, bottomLeft.y, bottomRight.x,
               bottomRight.y);
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

void puzzle3::parseBoxParts(const std::string &line, std::vector<std::string> &boxParts) {
    size_t i = 0, j = 0;
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
}

void puzzle3::buildBox(std::map<int, box> &boxes, const std::vector<std::string> &boxParts) {
    int boxId = -1, x = 0, y = 0, width = 0, height = 0;
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

void puzzle3::buildBoxes(const std::vector<std::string> &fileContents,
                        std::map<int, box> &boxes) {
	for(auto &line : fileContents) {
		std::vector<std::string> boxParts;
        parseBoxParts(line, boxParts);
        buildBox(boxes, boxParts);
	}
	printf("Built %ld boxes\n", boxes.size());
}

std::pair<int, int> puzzle3::calculateOverlappingArea(const std::map<int, box> &boxes) {
	std::set<point> allOverlaps;
    int nonOverlappingBoxId = -1;
	for(auto &box : boxes) {
		bool boxOverlaps = false;
		//box.second.printBox();
		for(auto &otherBox : boxes) {
			if (otherBox.first == box.first) {
				continue;
			}
			std::set<point> overlap = box.second.overlapArea(otherBox.second);
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
            nonOverlappingBoxId = box.first;
		}
	}
				
    return std::make_pair(allOverlaps.size(), nonOverlappingBoxId);
}

void puzzle3::runPuzzle(...) {
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle3_input.txt", fileContents);
    puzzle3 puzzle;
    std::map<int, box> boxes;
    puzzle.buildBoxes(fileContents, boxes);
    
    std::pair<int, int> overlappedArea = puzzle.calculateOverlappingArea(boxes);

	printf("Overlapping area is %d\n", overlappedArea.first);
    printf("Box %d doesn't overlap any other boxes\n", overlappedArea.second);
}
