#include "puzzle7.hpp"
#include "AOCUtils.hpp"
#include <math.h>

std::vector<long long> &puzzle7::amplifier::amplify(const std::vector<std::string> &program) {
    if (!computer.isHalted() && !computer.isWaitingForInput()) {
        computer.parseProgram(program, phase_setting);
    } else {
        if (computer.isWaitingForInput()) {
            computer.continueProcessing();
        } else {
            printf("Computer is in a weird state\n");
        }
    }
    
    return computer.outputStream;
}

void puzzle7::buildPhaseSettings(std::vector<std::vector<int> > &phases, const int min, const int max) {
    for (int i = min;i < max;i++) {
        for (int j = min;j < max;j++) {
            if (j == i) continue;
            for (int k = min;k < max;k++) {
                if (k == i || k == j) continue;
                for (int l = min;l < max;l++) {
                    if (l == k || l == j || l == i) continue;
                    for (int m = min;m < max;m++) {
                        if (m == l || m == k || m == j || m == i) continue;
                        phases.push_back({i, j, k, l, m});
                    }
                }
            }
        }
    }
}

void puzzle7::runPartOne(const std::vector<std::string> &fileContents) {
    
    std::vector<std::vector<int> > phases;
    buildPhaseSettings(phases, 0, 5);
    
    long long max_output = LONG_LONG_MIN;
    
    for(auto phase_set : phases) {
        std::vector<long> inputs = {0};
        for (int i = 0;i < 5;i++) {
            amplifier amp = amplifier(phase_set[i], inputs.back());
            amp.computer.addInput(amp.input);
            std::vector<long long> amplifierOutput = amp.amplify(fileContents);
            
            inputs.push_back(amplifierOutput[0]);
        }
        if (inputs.back() > max_output) {
            max_output = inputs.back();
        }
    }
    
    printf("Part one max thrust signal: %lld\n", max_output);
}

void puzzle7::runPartTwo(const std::vector<std::string> &fileContents) {
    std::vector<std::vector<int> > phases;
    buildPhaseSettings(phases, 5, 10);
    
    long long max_output = LONG_LONG_MIN;
    
    for(auto phase_set : phases) {
        std::vector<amplifier> amps;
        std::vector<int> inputs = {0};
        for (int i = 0;i < 5;i++) {
            amps.push_back(amplifier(phase_set[i]));
            amps.back().computer.setWaitForInput(true);
        }
        amps.front().computer.addInput(inputs.back());
        bool halted = false;
        int active_computer = 0;
        std::vector<long long> amplifierOutput;
        while (!halted) {
            amplifierOutput = amps[active_computer].amplify(fileContents);
            bool allHalted = true;
            for(auto &amp : amps) {
                if (!amp.computer.isHalted()) {
                    allHalted = false;
                    break;
                }
            }
            if (allHalted) {
                halted = true;
            } else {
                long long amp_output = amps[active_computer].computer.outputStream.back();
                active_computer++;
                if (active_computer > 4) {
                    active_computer = 0;
                }
                amps[active_computer].computer.addInput(amp_output);
            }
        }
        if (amps.back().computer.outputStream.back() > max_output) {
            max_output = amps.back().computer.outputStream.back();
        }
    }
    
    printf("Part two max thrust signal: %lld\n", max_output);
}


void puzzle7::runPuzzle(...) {
    puzzle7 puzzle;
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle7_input.txt", fileContents);
    
    puzzle.runPartOne(fileContents);
    puzzle.runPartTwo(fileContents);
}
