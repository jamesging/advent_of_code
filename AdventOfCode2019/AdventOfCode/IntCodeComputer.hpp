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
        const static int OPCODE_OFFSET = 9;
        const static int OPCODE_HALT = 99;
        struct opcode_inst {
            long inst;
            int param_count;
        public:
            opcode_inst(long instruction_id, int num_params):
            inst(instruction_id),
            param_count(num_params) {}
            
            opcode_inst() { param_count = -1; }
        };
        
        std::vector<int> modes;
    public:
        opcode(const long ptr, const std::vector<long long> &data);
        
        const static opcode_inst ADD;
        const static opcode_inst MULT;
        const static opcode_inst SAVE;
        const static opcode_inst OUTPUT;
        const static opcode_inst JMPT;
        const static opcode_inst JMPF;
        const static opcode_inst LT;
        const static opcode_inst EQ;
        const static opcode_inst OFFSET;
        const static opcode_inst HALT;
        
        static opcode_inst get_instruction_type(const long instruction);
        
        bool operate(IntCodeComputer &computer) const;
        void add(IntCodeComputer &computer) const;
        void mult(IntCodeComputer &computer) const;
        bool save(IntCodeComputer &computer) const;
        void output(IntCodeComputer &computer) const;
        void jump(IntCodeComputer &computer, bool if_not_zero) const;
        void less_than(IntCodeComputer &computer) const;
        void equals(IntCodeComputer &computer) const;
        void offset_addr_base(IntCodeComputer &computer) const;
    };
    
    IntCodeComputer() {
        inst_ptr = 0;
        addr_base = 0;
        waitForInput = false;
        halted = false;
        waiting = false;
        memory = std::vector<long long>();
        user_input = std::vector<long long>();
    };
    
    void parseProgram(const std::vector<std::string> &fileContents,
                             const long long input = 0);
    void continueProcessing();
    void addInput(long long newInput, bool continue_program = false) {
        user_input.push_back(newInput);
        if (continue_program) {
            continueProcessing();
        }
    };
    void setWaitForInput(bool newSetting) { waitForInput = newSetting; };
    const long long fetchData(long ptr, int mode = 0);
    void storeData(long ptr, int mode, long long data);
    void checkAndExpandMemory(long ptr, int mode);
    const bool isHalted() const { return halted; };
    const bool isWaitingForInput() const { return waiting; };
    std::vector<long long> outputStream;
    long inst_ptr;
    long addr_base;
    
    std::vector<long long> memory;
    
private:
    std::vector<long long> user_input;
    bool waitForInput;
    bool halted, waiting;
};

#endif /* IntCodeComputer_hpp */
