#include <stdio.h>
#include <math.h>
#include <fstream>
#include <istream>
#include <map>
#include <set>
#include <vector>
#include <string>

static int regionDistance = 16;

class point {
public:
	int x, y;
	point(int _x, int _y):x(_x),y(_y) {}

	point operator-(const point &other) const {
		return point(abs(x - other.x), abs(y - other.y));
	}

	bool operator==(const point &other) const {
		return x == other.x && y == other.y;
	}
	bool operator!=(const point &other) const {
		return x != other.x || y != other.y;
	}

	bool operator<(const point &right) const {
		if (x < right.x) {
			return true;
		} else if (x == right.x && y < right.y) {
			return true;
		}
		return false;
	}

	int manhattanDist(const point &other) const {
		point diff = *this - other;
		return diff.x + diff.y;
	}
};

std::pair<point, bool> getClosestPoint(const point &fromPoint, const std::map<point, int> &points)  {
	std::map<int, std::vector<point> > distToPoint;
	for(auto &pntPair : points) {
		point aPoint = pntPair.first;
		int dist = aPoint.manhattanDist(fromPoint);
		if (distToPoint.find(dist) == distToPoint.end()) {
			distToPoint[dist] = std::vector<point>();
		}
		distToPoint[dist].push_back(aPoint);
	}
	if (distToPoint.begin()->second.size() > 1) {
		return std::make_pair(fromPoint, true);
	} else {
		return std::make_pair(distToPoint.begin()->second[0], false);
	}
}

bool isInfinite(const point &aPoint, std::map<point, int> &points,
	int minX, int maxX, int minY, int maxY) {
	int xStart, yStart, xEnd, yEnd;
	if (aPoint.x - minX < abs(aPoint.x - maxX)) {
		xStart = minX;
		xEnd = aPoint.x;
	} else {
		xStart  = aPoint.x;
		xEnd = maxX;
	}
	if (aPoint.y - minY < abs(aPoint.y - maxY)) {
		yStart = minY;
		yEnd = aPoint.y;
	} else {
		yStart = aPoint.y;
		yEnd = maxY;
	}
	bool xFinite = false;
	for(int x = xStart;x <= xEnd;x++) {
		point fromPoint(x, aPoint.y);
		point closestPoint = getClosestPoint(fromPoint, points).first;
		if (closestPoint != aPoint) {
			xFinite = true;
			break;
		}
	}
	if (xFinite) {
		for(int y = yStart;y <= yEnd;y++) {
			point fromPoint(aPoint.x, y);
			point closestPoint = getClosestPoint(fromPoint, points).first;
			if (closestPoint != aPoint) {
				return false;
			}
		}
	}
	return true;
}

int processFileContents(std::vector<std::string> &fileContents) {
	std::map<point, int> points;
        for(auto &line : fileContents) {
		std::string xStr = line.substr(0, line.find_first_of(','));
		int x = std::stoi(line.substr(0, line.find_first_of(',')));
		int y = std::stoi(line.substr(line.find_first_of(',')+1, line.size()));
		points.emplace(point(x, y), 0);
        }
	int minX = INT_MAX, minY = INT_MAX, maxX = 0, maxY = 0;
	int maxDist = 0;
	for(auto &pntPair : points) {
		point aPoint = pntPair.first;
		if (aPoint.x < minX) {
			minX = aPoint.x;
		}
		if (aPoint.x > maxX) {
			maxX = aPoint.x;
		}
		if (aPoint.y < minY) {
			minY = aPoint.y;
		}
		if (aPoint.y > maxY) {
			maxY = aPoint.y;
		}
	}
	for(int x = minX;x <= maxX;x++) {
		for(int y = minY;y <= maxY;y++) {
			point thisPoint(x, y);
			std::pair<point, bool> closestPoint = getClosestPoint(thisPoint, points);
			if (!closestPoint.second) {
				points[closestPoint.first] = points[closestPoint.first] + 1;
			}
		}
	}

	printf("minX %d maxX %d minY %d maxY %d\n", minX, maxX, minY, maxY);
	int mostSquares = 0;
	point mostSquaresPoint(0, 0);
	int totalSquares = 0;
	for(auto &aPoint : points) {
		totalSquares += aPoint.second;
		if (aPoint.second > mostSquares) {
			if (isInfinite(aPoint.first, points, minX, maxX, minY, maxY)) {
				printf("Point %d,%d with %d is infinite, discarding\n", aPoint.first.x, aPoint.first.y, aPoint.second);
				continue;
			}
			mostSquares = aPoint.second;
			mostSquaresPoint = aPoint.first;
		}
	} 
	printf("most squares: %d, %d,%d\n", mostSquares, mostSquaresPoint.x, mostSquaresPoint.y);
	printf("total squares mapped: %d\n", totalSquares);
        return mostSquares;
}

int processFileContentsPartTwo(std::vector<std::string> &fileContents) {
	std::map<point, int> points;
        for(auto &line : fileContents) {
                std::string xStr = line.substr(0, line.find_first_of(','));
                int x = std::stoi(line.substr(0, line.find_first_of(',')));
                int y = std::stoi(line.substr(line.find_first_of(',')+1, line.size()));
                points.emplace(point(x, y), 0);
        }
	int minX = INT_MAX, minY = INT_MAX, maxX = 0, maxY = 0;
        int maxDist = 0;
        for(auto &pntPair : points) {
                point aPoint = pntPair.first;
                if (aPoint.x < minX) {
                        minX = aPoint.x;
                }
                if (aPoint.x > maxX) {
                        maxX = aPoint.x;
                }
                if (aPoint.y < minY) {
                        minY = aPoint.y;
                }
                if (aPoint.y > maxY) {
                        maxY = aPoint.y;
                }
        }
	std::vector<point> regionPoints;
        for(int x = minX;x <= maxX;x++) {
                for(int y = minY;y <= maxY;y++) {
			int distSum = 0;
                        point thisPoint(x, y);
			for(auto &pntPair : points) {
				distSum += thisPoint.manhattanDist(pntPair.first);
				if (distSum > regionDistance) {
					break;
				}
			}
			if (distSum < regionDistance) {
				regionPoints.push_back(thisPoint);
			}
                }
        }
	
        return regionPoints.size();
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
	if (argc != 3) {
                printf("Incorrect usage. Try: puzzle2 [Input file name] [region distance]\n");
                return 1;
        }
	regionDistance = atoi(argv[2]);
	int maxSize = openAndReadFile(argv[1]);
	int partTwoSize = openAndReadFile(argv[1], true);

	printf("Maximum area is %d\n", maxSize);
	printf("Part two region size is %d\n", partTwoSize);
	return 0;
}
