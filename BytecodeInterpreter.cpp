#include "BytecodeInterpreter.hpp"
#include <iostream>

namespace bytecodeinterpreter {

    using namespace std;

    InstructionFunction gInstructionFunctions[NUM_INSTRUCTIONS] = {
            ExitInstruction,
            AddIntInstruction,
            PushIntInstruction,
            PopIntInstruction,
            PrintIntInstruction,
            CompareIntLessThanInstruction,
            LoadIntInstruction,
            StoreIntInstruction,
            JumpByIfZeroInstruction,
            JumpByInstruction,
            LoadIntBasepointerRelativeInstruction,
            StoreIntBasepointerRelativeInstruction,
            CallInstruction,
            ReturnInstruction,
    };

    /*static*/ void BytecodeInterpreter::Run(Instruction* code, vector<int16_t> arguments, int16_t* result) {
        InterpreterRegisters registers{ .currentInstruction = code };

        if (result) {
            registers.stack.push_back(0);
        }
        registers.stack.insert(registers.stack.end(), arguments.begin(), arguments.end());

        registers.stack.push_back(0); // push old baseIndex.
        registers.returnAddressStack.push_back(nullptr);
        registers.baseIndex = registers.stack.size();

        while (registers.currentInstruction != nullptr) {
            gInstructionFunctions[registers.currentInstruction->opcode](registers);
        }

        size_t numArgs = arguments.size();
        while( numArgs-- ) {
            registers.stack.pop_back();
        }

        if (result) {
            *result = registers.stack[0];
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

    //! POP_INT
    void PopIntInstruction(InterpreterRegisters& registers) {
        registers.stack.pop_back();
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

    //! LOAD_INT_BASEPOINTER_RELATIVE
    void LoadIntBasepointerRelativeInstruction(InterpreterRegisters &registers) {
        registers.stack.push_back(registers.stack[registers.currentInstruction->p2 + registers.baseIndex]);
        ++registers.currentInstruction;
    }

    //! STORE_INT_BASEPOINTER_RELATIVE
    void StoreIntBasepointerRelativeInstruction(InterpreterRegisters &registers) {
        registers.stack[registers.currentInstruction->p2 + registers.baseIndex] = registers.stack.back();
        registers.stack.pop_back();
        ++registers.currentInstruction;
    }

    //! CALL
    void CallInstruction(InterpreterRegisters &registers) {
        registers.stack.push_back(int16_t(registers.baseIndex)); // DANGER! Jump address is limited to 16 bits signed!
        registers.returnAddressStack.push_back(registers.currentInstruction + 1);
        registers.baseIndex = registers.stack.size();
        registers.currentInstruction += registers.currentInstruction->p2;
    }

    //! RETURN
    void ReturnInstruction(InterpreterRegisters &registers) {
        Instruction * returnAddress = registers.returnAddressStack.back();
        registers.returnAddressStack.pop_back();
        registers.baseIndex = registers.stack.back();
        registers.stack.pop_back();
        registers.currentInstruction = returnAddress;
    }

}