#pragma once

#include <cstdint>

namespace bytecodeinterpreter {

    enum Opcode: uint8_t {
        EXIT,
        ADD_INT,
        PUSH_INT,
        POP_INT,
        PRINT_INT,
        COMP_INT_LT,
        LOAD_INT,
        STORE_INT,
        JUMP_BY_IF_ZERO,
        JUMP_BY,
        LOAD_INT_BASEPOINTER_RELATIVE,
        STORE_INT_BASEPOINTER_RELATIVE,
        CALL,
        RETURN,
        NUM_INSTRUCTIONS
    };

    class Instruction {
    public:
        Opcode opcode;
        uint8_t p1;
        int16_t p2;
    };

}

