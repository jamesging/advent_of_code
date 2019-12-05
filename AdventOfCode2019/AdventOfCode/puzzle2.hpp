//
//  puzzle2.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle2_hpp
#define puzzle2_hpp

#include <string>
#include <vector>
#include <set>

#include "puzzle.hpp"

class puzzle2 : puzzle {
public:
    static void runPuzzle(...);
    
private:
    struct opcode {
        const static int OPCODE_SIZE = 4;
        const static int OPCODE_ADD = 1;
        const static int OPCODE_MULT = 2;
        const static int OPCODE_HALT = 99;
        
        int instruction, input1, input2, output;
    public:
        opcode(int inst, int in1, int in2, int out):
        instruction(inst),
        input1(in1),
        input2(in2),
        output(out) {}
        
        opcode(std::vector<int> ints);
        
        bool operate(std::vector<int> &data) const;
        void add(std::vector<int> &data) const;
        void mult(std::vector<int> &data) const;
    };
    
    void parseOpcodes(const std::vector<std::string> &fileContents, std::vector<opcode> &opcodes, std::vector<int> &data);
    
    void runPartOne(const std::vector<opcode> &opcodes, std::vector<int> data);
    void runPartTwo(const std::vector<opcode> &opcodes, const int goal, std::vector<int> data);
};

#endif /* puzzle2_hpp */
