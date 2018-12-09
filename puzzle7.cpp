#include <stdio.h>
#include <fstream>
#include <istream>
#include <map>
#include <set>
#include <vector>
#include <string>

static int workerCount = 5;
static int stepTime = 60;
static int currentTime = 0;

class step {
public:
	std::vector<char> dependsOn;
	char stepName;
	bool hasRun = false;
	bool isRunning = false;
	step(char _name):stepName(_name) {};

	bool canRun(std::map<char, step> &steps) const {
		if (isRunning) {
			return false;
		}
		for(auto prevStep : dependsOn) {
			auto it = steps.find(prevStep);
			if (it == steps.end()) {
				printf("%c is a required step for %c, and does not exist\n", prevStep, stepName);
				return false;
			} else {
				if (!it->second.hasRun) {
					return false;
				}
			}
		}
		if (hasRun) {
			return false;
		}
		return true;
	}

	char runStep() {
		hasRun = true;
		isRunning = false;
		return stepName;
	}

	int runTime() const {
		return stepTime + stepName-64;
	}
};

class worker {
public:
	step *currentStep = NULL;
	int startedAt;
	int id;
	worker(int _id):id(_id) {};

	bool available(std::string &runOrder) {
		if (!currentStep) {
			return true;
		}
		bool finished = currentTime >= currentStep->runTime() + startedAt;
		if (finished) {
			currentStep->runStep();
			runOrder.push_back(currentStep->stepName);
			currentStep = NULL;
			startedAt = 0;
		}
		return finished;
	}

	void startStep(step &newStep) {
		currentStep = &newStep;
		startedAt = currentTime;
		newStep.isRunning = true;
	}
};

void addStepIfMissing(char stepName, std::map<char, step> &steps) {
	if (steps.find(stepName) == steps.end()) {
		step newStep(stepName);
		steps.emplace(stepName, newStep);
	}
}

void runSteps(std::map<char, step> &steps, std::string &runOrder) {
	int remainingCount = 0;
	for (auto &stepPair : steps) {
		step &step = stepPair.second;
		if (!step.hasRun) {
			remainingCount++;
		}
		if (step.canRun(steps)) {
			runOrder.push_back(step.runStep());
			break;
		}
	}
	if (remainingCount > 0) {
		runSteps(steps, runOrder);
	}
}

void runStepsPartTwo(std::map<char, step> &steps, std::vector<worker> &workers,
	std::string &runOrder, int &runTime) {
	bool remainingStep = false;
	bool ranStep = false;
	bool workersAvailable = false;
	for (auto &worker : workers) {
		if (worker.available(runOrder)) {
			if (!workersAvailable) {
				workersAvailable = true;
			}
			for (auto &stepPair : steps) {
				step &step = stepPair.second;
		
				if (!step.hasRun && !remainingStep) {
					remainingStep = true;
				}
				if (step.canRun(steps)) {
					int finishTime = currentTime + step.runTime();
					runTime = finishTime > runTime ? finishTime : runTime;
					worker.startStep(step);
					ranStep = true;
					break;
				}
			}
		}
	}
	if (!ranStep) {
		currentTime++;
	}
	if (remainingStep || !workersAvailable) {
		runStepsPartTwo(steps, workers, runOrder, runTime);
	}
}

std::string processFileContents(std::vector<std::string> &fileContents) {
	std::map<char, step> steps;
	for(auto &line : fileContents) {
		char stepName = line[line.find_first_of(' ')+1];
		char enablesStep = line[line.find("can")-2];
		addStepIfMissing(stepName, steps);
		addStepIfMissing(enablesStep, steps);
		auto it = steps.find(enablesStep);
		if (it == steps.end()) {
			printf("failed to find step %c\n", enablesStep);
		} else {
			it->second.dependsOn.push_back(stepName);
		}
	}
	std::string runOrder;
	runSteps(steps, runOrder);
	return runOrder;
}

std::string processFileContentsPartTwo(std::vector<std::string> &fileContents) {
	std::vector<worker> workers;
	for (int i = 0;i < workerCount;i++) {
		workers.push_back(worker(i));
	}
	std::map<char, step> steps;
	for(auto &line : fileContents) {
		char stepName = line[line.find_first_of(' ')+1];
                char enablesStep = line[line.find("can")-2];
                addStepIfMissing(stepName, steps);
                addStepIfMissing(enablesStep, steps);
                auto it = steps.find(enablesStep);
                if (it == steps.end()) {
                        printf("failed to find step %c\n", enablesStep);
                } else {
                        it->second.dependsOn.push_back(stepName);
                }
	}
	std::string runOrder;
	int runTime = 0;
	runStepsPartTwo(steps, workers, runOrder, runTime);
	printf("Total part two runTime: %d\n", runTime);
	return runOrder;
}

std::string openAndReadFile(std::string fileName, bool partTwo = false) {
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
        return "";
}

int main(int argc, char **argv) {
	if (argc != 4) {
                printf("Incorrect usage. Try: puzzle7 [Input file name] [step base time] [worker count]\n");
                return 1;
        }
	stepTime = atoi(argv[2]);
	workerCount = atoi(argv[3]);
	std::string stepOrder = openAndReadFile(argv[1]);
	std::string partTwoOrder = openAndReadFile(argv[1], true);

	printf("Step order is %s\n", stepOrder.c_str());
	printf("Part two step order is %s\n", partTwoOrder.c_str());
	return 0;
}
