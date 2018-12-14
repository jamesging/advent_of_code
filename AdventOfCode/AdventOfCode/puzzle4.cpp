#include "puzzle4.hpp"
#include "AOCUtils.hpp"

int puzzle4::parseMinutesFromString(const std::string &str) {
	size_t minuteStart = str.find_last_of(':');
	std::string minuteStr = str.substr(minuteStart+1, 
		str.find_last_of(']'));
	return std::stoi(minuteStr);
}

void puzzle4::parseGuardSchedules(const std::vector<std::string> &fileContents,
                             std::map<int, std::map<int, int> > &guardSchedule) {
	int guardOnShift;
	int sleepStarted = 0;
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
			if (guardSchedule.find(guardOnShift) != guardSchedule.end()) {
				std::map<int, int> guardMinutesSlept = guardSchedule[guardOnShift];
				for(int i = sleepStarted; i < sleepEnded; i++) {
					if (guardMinutesSlept.find(i) != guardMinutesSlept.end()) {
						guardMinutesSlept[i] = guardMinutesSlept[i] + 1;
					} else {
						guardMinutesSlept[i] = 1;
					}
				}
				guardSchedule[guardOnShift] = guardMinutesSlept;
			} else {
				std::map<int, int> guardMinutesSlept;
				for(int i = sleepStarted; i < sleepEnded; i++) {
					guardMinutesSlept[i] = 1;
				}
				guardSchedule[guardOnShift] = guardMinutesSlept;
			}
			continue;
		}
	}
}

std::pair<int, int> puzzle4::laziestGuard(const std::map<int, std::map<int, int> > &sleepingGuards) {
	int maxSleptTime = 0;
	std::pair<int, int> lazyGuard;
	for(auto &sleepingGuard : sleepingGuards) {
		int sleptTime = 0;
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

std::pair<int, int> puzzle4::laziestGuardPartTwo(const std::map<int, std::map<int, int> > &sleepingGuards) {
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

void puzzle4::runPuzzle(...) {
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle4_input.txt", fileContents);
    puzzle4 puzzle;
    
    std::map<int, std::map<int, int> > sleepingGuards;
    puzzle.parseGuardSchedules(fileContents, sleepingGuards);
	std::pair<int, int> lazyGuard = puzzle.laziestGuard(sleepingGuards);
	std::pair<int, int> lazyGuardTwo = puzzle.laziestGuardPartTwo(sleepingGuards);
	

	printf("%d is the laziest guard and he slept on the %d minute most\n", lazyGuard.first, lazyGuard.second);
	printf("The answer is: %d*%d=%d\n", lazyGuard.first, lazyGuard.second, lazyGuard.first * lazyGuard.second);
	printf("%d is the guard who slept on the same minute the most on %d\n", lazyGuardTwo.first, lazyGuardTwo.second);
	printf("The answer to part two is: %d*%d=%d\n", lazyGuardTwo.first, lazyGuardTwo.second, lazyGuardTwo.first * lazyGuardTwo.second);
}
