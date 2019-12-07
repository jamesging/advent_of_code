//
//  IntCodeComputer.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/6/19.
//  Copyright © 2019 James Ging. All rights reserved.
//

#ifndef IntCodeComputer_hpp
#define IntCodeComputer_hpp

#include <vector>

class IntCodeComputer {
public:
    struct opcode {
        const static int OPCODE_ADD = 1;
        const static int OPCODE_MULT = 2;
        const static int OPCODE_SAVE = 3;
        const static int OPCODE_OUTPUT = 4;
        const static int OPCODE_HALT = 99;
        struct opcode_inst {
            int inst, size;
        public:
            opcode_inst(int instruction_id, int num_params):
            inst(instruction_id),
            size(num_params) {}
            
            opcode_inst() { size = -1; }
        };
        
        std::vector<int> params;
        std::vector<int> modes;
        int input;
    public:
        opcode(const opcode_inst &instruction_type, std::vector<int> ints);
        
        const static opcode_inst ADD;
        const static opcode_inst MULT;
        const static opcode_inst SAVE;
        const static opcode_inst OUTPUT;
        const static opcode_inst HALT;
        
        static opcode_inst get_instruction_type(const int instruction);
        
        bool operate(std::vector<int> &data) const;
        void add(std::vector<int> &data) const;
        void mult(std::vector<int> &data) const;
        void save(std::vector<int> &data) const;
        void output(std::vector<int> &data) const;
    };
    
    static void parseOpcodes(const std::vector<std::string> &fileContents,
                             std::vector<opcode> &opcodes,
                             std::vector<int> &data,
                             const int input = 0);
    static std::vector<int> outputStream;
};

#endif /* IntCodeComputer_hpp */
