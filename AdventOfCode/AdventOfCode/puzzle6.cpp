#include "puzzle6.hpp"
#include "AOCUtils.hpp"

#include <math.h>

int puzzle6::regionDistance = 16;

class puzzle6::point {
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

std::pair<puzzle6::point, bool> puzzle6::getClosestPoint(const point &fromPoint, const std::map<point, int> &points)  {
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

bool puzzle6::isInfinite(const point &aPoint, const std::map<point, int> &points,
	const int minX, const int maxX, const int minY, const int maxY) {
	int xStart, yStart, xEnd, yEnd;
	if (aPoint.x - minX < abs(aPoint.x - maxX)) {
		xStart = minX;
		xEnd = aPoint.x;
	} else {
		xStart = aPoint.x;
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

void puzzle6::parsePoints(const std::vector<std::string> &fileContents, std::vector<point> &points) {
    for(auto &line : fileContents) {
        std::string xStr = line.substr(0, line.find_first_of(','));
        int x = std::stoi(line.substr(0, line.find_first_of(',')));
        int y = std::stoi(line.substr(line.find_first_of(',')+1, line.size()));
        points.push_back(point(x, y));
    }
}

void puzzle6::mapPoints(const std::vector<point> &coordinates, std::map<point, int> &points,
                        int &minX, int &maxX, int &minY, int &maxY) {
    minX = INT_MAX;
    minY = INT_MAX;
    maxX = 0;
    maxY = 0;
    for(auto &point : coordinates) {
        points[point] = 0;
        if (point.x < minX) {
            minX = point.x;
        }
        if (point.x > maxX) {
            maxX = point.x;
        }
        if (point.y < minY) {
            minY = point.y;
        }
        if (point.y > maxY) {
            maxY = point.y;
        }
    }
}

int puzzle6::findLargestRegion(const std::vector<point> &coordinates) {
    std::map<point, int> points;
    int minX, maxX, minY, maxY;
    mapPoints(coordinates, points, minX, maxX, minY, maxY);

	for(int x = minX;x <= maxX;x++) {
		for(int y = minY;y <= maxY;y++) {
			point thisPoint(x, y);
			std::pair<point, bool> closestPoint = getClosestPoint(thisPoint, points);
			if (!closestPoint.second) {
				points[closestPoint.first] = points[closestPoint.first] + 1;
			}
		}
	}

	int mostSquares = 0;
	point mostSquaresPoint(0, 0);
	int totalSquares = 0;
	for(auto &aPoint : points) {
		totalSquares += aPoint.second;
		if (aPoint.second > mostSquares) {
			if (isInfinite(aPoint.first, points, minX, maxX, minY, maxY)) {
				continue;
			}
			mostSquares = aPoint.second;
			mostSquaresPoint = aPoint.first;
		}
	} 
	return mostSquares;
}

size_t puzzle6::findDensestRegion(const std::vector<point> &coordinates) {
	std::map<point, int> points;
    int minX, maxX, minY, maxY;
    mapPoints(coordinates, points, minX, maxX, minY, maxY);
    
	std::vector<point> regionPoints;
    for(int x = minX;x <= maxX;x++) {
        for(int y = minY;y <= maxY;y++) {
            int distSum = 0;
            point thisPoint(x, y);
            for(auto &pntPair : points) {
                distSum += thisPoint.manhattanDist(pntPair.first);
                if (distSum >= regionDistance) {
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

void puzzle6::runPuzzle(const int regionMaxDist, ...) {
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle6_input.txt", fileContents);
    regionDistance = regionMaxDist;
    
    puzzle6 puzzle;
    
    std::vector<point> points;
    puzzle.parsePoints(fileContents, points);
    
    int largestRegionArea = puzzle.findLargestRegion(points);
    size_t partTwoSize = puzzle.findDensestRegion(points);

	printf("Maximum area is %d\n", largestRegionArea);
	printf("Part two region size is %ld\n", partTwoSize);
}
