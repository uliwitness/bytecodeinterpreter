#include "BytecodeInterpreter.hpp"
#include <iostream>

namespace bytecodeinterpreter {

    using namespace std;

    InstructionFunction gInstructionFunctions[NUM_INSTRUCTIONS] = {
        ExitInstruction,
        AddIntInstruction,
        PushIntInstruction,
        PrintIntInstruction,
        CompareIntLessThanInstruction,
        LoadIntInstruction,
        StoreIntInstruction,
        JumpByIfZeroInstruction,
            JumpByInstruction
            };

    /*static*/ void BytecodeInterpreter::Run(Instruction* code) {
        InterpreterRegisters registers{ .currentInstruction = code };

        while (registers.currentInstruction != nullptr) {
            gInstructionFunctions[registers.currentInstruction->opcode](registers);
        }
    }

    //! EXIT
    void ExitInstruction(InterpreterRegisters& registers) {
        registers.currentInstruction = nullptr;
    }

    //! ADD_INT
    void AddIntInstruction(InterpreterRegisters& registers) {
        int16_t rightHandSide = registers.stack.back();
        registers.stack.pop_back();
        int16_t leftHandSide = registers.stack.back();
        registers.stack.pop_back();
        registers.stack.push_back(leftHandSide + rightHandSide);
        ++registers.currentInstruction;
    }

    //! PUSH_INT
    void PushIntInstruction(InterpreterRegisters& registers) {
        registers.stack.push_back(registers.currentInstruction->p2);
        ++registers.currentInstruction;
    }

    //! PRINT_INT
    void PrintIntInstruction(InterpreterRegisters& registers) {
        int16_t number = registers.stack.back();
        registers.stack.pop_back();
        cout << "Number Printed: " << number << endl;
        ++registers.currentInstruction;
    }

    //! COMP_INT_LT
    void CompareIntLessThanInstruction(InterpreterRegisters& registers) {
        int16_t rightHandSide = registers.stack.back();
        registers.stack.pop_back();
        int16_t leftHandSide = registers.stack.back();
        registers.stack.pop_back();

        registers.stack.push_back(leftHandSide < rightHandSide);

        ++registers.currentInstruction;
    }

    //! LOAD_INT
    void LoadIntInstruction(InterpreterRegisters& registers) {
        registers.stack.push_back(registers.stack[registers.currentInstruction->p2]);
        ++registers.currentInstruction;
    }

    //! STORE_INT
    void StoreIntInstruction(InterpreterRegisters& registers) {
        registers.stack[registers.currentInstruction->p2] = registers.stack.back();
        registers.stack.pop_back();
        ++registers.currentInstruction;
    }

    //! JUMP_BY_IF_ZERO
    void JumpByIfZeroInstruction(InterpreterRegisters& registers) {
        int16_t condition = registers.stack.back();
        registers.stack.pop_back();
        if (condition == 0) {
            registers.currentInstruction += registers.currentInstruction->p2;
        } else {
            ++registers.currentInstruction; // no-op.
        }
    }

    //! JUMP_BY
    void JumpByInstruction(InterpreterRegisters& registers) {
        registers.currentInstruction += registers.currentInstruction->p2;
    }

}