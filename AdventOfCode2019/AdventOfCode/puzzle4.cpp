#include "puzzle4.hpp"
#include "AOCUtils.hpp"
#include <math.h>

void puzzle4::satisfiesCriteria(const int password, int &validCount, int &validCountPartTwo) {
    char pwBuffer[PW_BUFFER_SIZE];
    snprintf(pwBuffer, PW_BUFFER_SIZE, "%d", password);
    std::string pwString = pwBuffer;
    int prev = 0;
    bool containsADouble = false;
    bool containsAPartTwoDouble = false;
    for(int i = 0; i < pwString.length();i++) {
        char ch = pwString[i];
        if ((ch - '0') < prev) {
            return;
        }
        if (!containsADouble) {
            std::string doubleChar = std::string(2, ch);
            if (pwString.find(doubleChar) != std::string::npos) {
                containsADouble = true;
            }
        }
        if (!containsAPartTwoDouble) {
            std::string doubleChar = std::string(2, ch);
            if (pwString.find(doubleChar) != std::string::npos) {
                std::string tripleChar = std::string(3, ch);
                if (pwString.find(tripleChar) == std::string::npos) {
                    containsAPartTwoDouble = true;
                }
            }
        }
        prev = ch - '0';
    }
    if (containsADouble) {
        validCount++;
    }
    if (containsAPartTwoDouble) {
        validCountPartTwo++;
    }
}

void puzzle4::runPuzzle(...) {
    puzzle4 puzzle;
    //official range start and end are 236491 and 713787, we'll trim these right off due to the puzzle rules
    int rangeStart = 236491;
    int rangeEnd = 713787;
    int validCount = 0, validCountPartTwo = 0;
    for (int i = rangeStart; i <= rangeEnd;i++) {
        puzzle.satisfiesCriteria(i, validCount, validCountPartTwo);
    }
    printf("There are %d potential passwords out of %d checked for Part One\n", validCount, rangeEnd - rangeStart);
    printf("There are %d potential passwords out of %d checked for Part Two\n", validCountPartTwo, rangeEnd - rangeStart);
}
