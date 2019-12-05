//
//  puzzle12.cpp
//  AdventOfCode
//
//  Created by James Ging on 12/14/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#include "puzzle12.hpp"
#include "AOCUtils.hpp"

class puzzle12::cellRule {
public:
    std::vector<bool> cellState;
    bool result;
    cellRule(const std::vector<bool> &_state, const bool _result):cellState(_state),result(_result) {};
    
    bool applyState(std::list<bool> &state, const std::list<bool>::iterator it) const {
        if (std::distance(state.begin(), it) < 2 ||
            std::distance(it, state.end()) < 2) {
            return false;
        }
        auto inner = it;
        std::advance(inner, -2);
        for (int i = 0;i < cellState.size();i++) {
            if (*inner != cellState[i]) {
                return false;
            }
            inner++;
        }
        return true;
    }
};

void puzzle12::buildInitialState(const std::vector<std::string> &fileContents, std::vector<bool> &initialState) {
    initialState.push_back(false);
    initialState.push_back(false);
    initialState.push_back(false);
    const std::string &initLine = fileContents[0];
    size_t startPos = initLine.find_first_of(':')+2;
    for (size_t i = startPos;i < initLine.size();i++) {
        initialState.push_back(initLine.at(i) == '#');
    }
    initialState.push_back(false);
    initialState.push_back(false);
    initialState.push_back(false);
}

void puzzle12::parseCellRules(const std::vector<std::string> &fileContents, std::vector<cellRule> &rules) {
    auto it = fileContents.begin();
    it += 2;
    while(it != fileContents.end()) {
        std::vector<bool> state;
        for (int i = 0;i < (*it).find_first_of(' ');i++) {
            state.push_back((*it)[i] == '#');
        }
        rules.push_back(cellRule(state, (*it).at((*it).size()-1) == '#'));
        it++;
    }
}

std::list<bool> puzzle12::runGenerations(const std::vector<bool> &initialState,
                                         const std::vector<cellRule> &rules, const long numGenerations) {
    std::list<bool> state;
    for (auto b : initialState) {
        state.push_back(b);
    }
    std::list<bool> genState = state;
    int left = -3;
    for (long i = 0;i < numGenerations;i++) {
        bool genChanged = false;
        auto it = state.begin();
        auto genIt = genState.begin();
        while (it != state.end()) {
            bool anyRuleApplies = false;
            for (auto &rule : rules) {
                bool ruleApplies = rule.applyState(state, it);
                if (ruleApplies) {
                    genChanged = true;
                    *genIt = rule.result;
                    if (std::distance(genIt, genState.end()) == 3) {
                        genState.push_back(false);
                    }
                    if (std::distance(genState.begin(), genIt) == 2) {
                        genState.push_front(false);
                        left--;
                    }
                    anyRuleApplies = true;
                }
            }
            if (!anyRuleApplies) {
                *genIt = false;
            }
            it++;
            genIt++;
        }
        state = genState;
        printf("%ld-%d: ", i, genChanged);
        for (auto b : state) {
            printf("%c", b ? '#' : '.');
        }
        printf("\n");
    }
    printf("The left most pot number is now %d\n", left);
    int potSum = 0;
    int potIndex = left;
    for (auto b : state) {
        if (b) {
            potSum += potIndex;
        }
        potIndex++;
    }
    printf("The sum of all the plant containing pots is %d\n", potSum);
    return state;
}

void puzzle12::runPuzzle(const long numGenerations) {
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle12_input.txt", fileContents);
    puzzle12 puzzle;
    
    std::vector<bool> initialState;
    puzzle.buildInitialState(fileContents, initialState);
    for (auto b : initialState) {
        printf("%c", b ? '#' : '.');
    }
    printf("\n");
    std::vector<cellRule> rules;
    puzzle.parseCellRules(fileContents, rules);
    std::list<bool> finalState = puzzle.runGenerations(initialState, rules, numGenerations);
    for (auto b : finalState) {
        printf("%c", b ? '#' : '.');
    }
    printf("\n");
}
