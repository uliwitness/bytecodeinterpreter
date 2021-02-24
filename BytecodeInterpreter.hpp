#pragma once

#include "Instruction.hpp"
#include <cstdint>
#include <vector>

namespace bytecodeinterpreter {

    using namespace std;

    struct InterpreterRegisters {
        vector <int16_t> stack;
        Instruction *currentInstruction;
    };

    typedef void (*InstructionFunction)(InterpreterRegisters& registers);

    void ExitInstruction(InterpreterRegisters& registers);
    void AddIntInstruction(InterpreterRegisters& registers);
    void PushIntInstruction(InterpreterRegisters& registers);
    void PrintIntInstruction(InterpreterRegisters& registers);
    void CompareIntLessThanInstruction(InterpreterRegisters& registers);
    void LoadIntInstruction(InterpreterRegisters& registers);
    void StoreIntInstruction(InterpreterRegisters& registers);
    void JumpByIfZeroInstruction(InterpreterRegisters& registers);
    void JumpByInstruction(InterpreterRegisters& registers);

    extern InstructionFunction gInstructionFunctions[NUM_INSTRUCTIONS];

    class BytecodeInterpreter {
    public:
        static void Run(Instruction* code);
    };

} /* namespace bytecodeinterpreter */