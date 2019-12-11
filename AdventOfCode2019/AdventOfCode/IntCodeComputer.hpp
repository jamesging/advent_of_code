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
        const static int OPCODE_JMPT = 5;
        const static int OPCODE_JMPF = 6;
        const static int OPCODE_LT = 7;
        const static int OPCODE_EQ = 8;
        const static int OPCODE_HALT = 99;
        struct opcode_inst {
            int inst, param_count;
        public:
            opcode_inst(int instruction_id, int num_params):
            inst(instruction_id),
            param_count(num_params) {}
            
            opcode_inst() { param_count = -1; }
        };
        
        std::vector<int> modes;
        int pointer;
    public:
        opcode(const int ptr, const std::vector<int> &data);
        
        const static opcode_inst ADD;
        const static opcode_inst MULT;
        const static opcode_inst SAVE;
        const static opcode_inst OUTPUT;
        const static opcode_inst JMPT;
        const static opcode_inst JMPF;
        const static opcode_inst LT;
        const static opcode_inst EQ;
        const static opcode_inst HALT;
        
        static opcode_inst get_instruction_type(const int instruction);
        
        bool operate(IntCodeComputer &computer, std::vector<int> &data) const;
        void add(IntCodeComputer &computer, std::vector<int> &data) const;
        void mult(IntCodeComputer &computer, std::vector<int> &data) const;
        void save(IntCodeComputer &computer, std::vector<int> &data) const;
        void output(IntCodeComputer &computer, std::vector<int> &data) const;
        void jump(IntCodeComputer &computer, std::vector<int> &data, bool if_not_zero) const;
        void less_than(IntCodeComputer &computer, std::vector<int> &data) const;
        void equals(IntCodeComputer &computer, std::vector<int> &data) const;
    };
    
    IntCodeComputer() {
        inst_ptr = 0;
        user_input = 0;
    };
    
    void parseProgram(const std::vector<std::string> &fileContents,
                             std::vector<int> &data,
                             const int input = 0);
    const int fetchData(const std::vector<int> &data, int ptr, int mode = 0);
    std::vector<int> outputStream;
    int inst_ptr;
    
private:
    int user_input;
};

#endif /* IntCodeComputer_hpp */
