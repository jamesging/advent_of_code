#include <stdio.h>
#include <fstream>
#include <istream>
#include <map>
#include <vector>
#include <string>

int parseMinutesFromString(std::string &str) {
	size_t minuteStart = str.find_last_of(':');
	std::string minuteStr = str.substr(minuteStart+1, 
		str.find_last_of(']'));
	return std::stoi(minuteStr);
}

std::map<int, std::map<int, int> > processFileContents(std::vector<std::string> &fileContents) {
	std::map<int, std::map<int, int> > retVal;
	int guardOnShift;
	bool asleep = false;
	int sleepStarted;
	for(auto &line : fileContents) {
		if (line.find("begins shift") != line.npos) {
			size_t guardIdStart = line.find_first_of('#');
			std::string guardStr = line.substr(guardIdStart+1,
				line.find_first_of(' ', guardIdStart));
			guardOnShift = std::stoi(guardStr);
			continue;
		}
		if (line.find("falls asleep") != line.npos) {
			sleepStarted = parseMinutesFromString(line);
			continue;
		}
		if (line.find("wakes up") != line.npos) {
			int sleepEnded = parseMinutesFromString(line);
			int sleepTime = sleepEnded - sleepStarted;
			if (retVal.find(guardOnShift) != retVal.end()) {
				std::map<int, int> guardMinutesSlept = retVal[guardOnShift];
				for(int i = sleepStarted; i < sleepEnded; i++) {
					if (guardMinutesSlept.find(i) != guardMinutesSlept.end()) {
						guardMinutesSlept[i] = guardMinutesSlept[i] + 1;
					} else {
						guardMinutesSlept[i] = 1;
					}
				}
				retVal[guardOnShift] = guardMinutesSlept;
			} else {
				std::map<int, int> guardMinutesSlept;
				for(int i = sleepStarted; i < sleepEnded; i++) {
					guardMinutesSlept[i] = 1;
				}
				retVal[guardOnShift] = guardMinutesSlept;
			}
			continue;
		}
	}
	return retVal;
}

std::map<int, std::map<int, int> > openAndReadFile(std::string fileName) {
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
        return std::map<int, std::map<int, int> >();
}

std::pair<int, int> laziestGuard(std::map<int, std::map<int, int> > &sleepingGuards) {
	int maxSleptTime = 0;
	std::pair<int, int> lazyGuard;
	for(auto &sleepingGuard : sleepingGuards) {
		int sleptTime;
		int minuteSleptOnMost;
		int minuteSleptOnMostMax = 0;
		for(auto &sleptMinutes : sleepingGuard.second) {
			sleptTime += sleptMinutes.second;
			if (sleptMinutes.second > minuteSleptOnMostMax) {
				minuteSleptOnMost = sleptMinutes.first;
				minuteSleptOnMostMax = sleptMinutes.second;
			}
		}
		if (sleptTime > maxSleptTime) {
			lazyGuard = std::make_pair(sleepingGuard.first, minuteSleptOnMost);
			maxSleptTime = sleptTime;
			sleptTime = 0;
		}
	}
	return lazyGuard;
}

std::pair<int, int> laziestGuardPartTwo(std::map<int, std::map<int, int> > &sleepingGuards) {
	int totalMax = 0;
        std::pair<int, int> lazyGuard;
        for(auto &sleepingGuard : sleepingGuards) {
                int minuteSleptOnMost;
                int minuteSleptOnMostMax = 0;
                for(auto &sleptMinutes : sleepingGuard.second) {
                        if (sleptMinutes.second > minuteSleptOnMostMax) {
                                minuteSleptOnMost = sleptMinutes.first;
                                minuteSleptOnMostMax = sleptMinutes.second;
                        }
                }
                if (minuteSleptOnMostMax > totalMax) {
                        lazyGuard = std::make_pair(sleepingGuard.first, minuteSleptOnMost);
			totalMax = minuteSleptOnMostMax;
                        minuteSleptOnMostMax = 0;
                }
        }
        return lazyGuard;
}

int main(int argc, char **argv) {
	if (argc != 2) {
                printf("Incorrect usage. Try: puzzle2 [Input file name]\n");
                return 1;
        }
	std::map<int, std::map<int, int> > sleepingGuards = openAndReadFile(argv[1]);
	std::pair<int, int> lazyGuard = laziestGuard(sleepingGuards);
	std::pair<int, int> lazyGuardTwo = laziestGuardPartTwo(sleepingGuards);
	

	printf("%d is the laziest guard and he slept on the %d minute most\n", lazyGuard.first, lazyGuard.second);
	printf("The answer is: %d*%d=%d\n", lazyGuard.first, lazyGuard.second, lazyGuard.first * lazyGuard.second);
	printf("%d is the guard who slept on the same minute the most on %d\n", lazyGuardTwo.first, lazyGuardTwo.second);
	printf("The answer to part two is: %d*%d=%d\n", lazyGuardTwo.first, lazyGuardTwo.second, lazyGuardTwo.first * lazyGuardTwo.second);
	return 0;
}
