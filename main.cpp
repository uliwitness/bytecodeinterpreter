#include <iostream>
#include <vector>
#include "Instruction.hpp"
#include "BytecodeInterpreter.hpp"

using namespace std;
using namespace bytecodeinterpreter;

int main(int argc, char ** argv) {
    cout << "bytecodeinterpreter 1.0\n" << endl;

    Instruction code[] = {
            Instruction{PUSH_INT, 0, 0}, // x
            Instruction{LOAD_INT, 0, 0}, // load x
            Instruction{PUSH_INT, 0, 10}, // load 10
            Instruction{COMP_INT_LT, 0, 0}, // x < 10
            Instruction{JUMP_BY_IF_ZERO, 0, 10}, // if x >= 10 bail!

            Instruction{PUSH_INT, 0, 4000},
            Instruction{PUSH_INT, 0, 1042},
            Instruction{ADD_INT, 0, 0},
            Instruction{PRINT_INT, 0, 0},

            Instruction{LOAD_INT, 0, 0}, // load x
            Instruction{PUSH_INT, 0, 1}, // load 1
            Instruction{ADD_INT, 0, 0}, // x + 1
            Instruction{STORE_INT, 0, 0}, // x = (x + 1)
            Instruction{JUMP_BY, 0, -12}, // loop back to condition.
            Instruction{EXIT, 0, 0}
    };

    BytecodeInterpreter::Run(code);

    cout << "\ndone." << endl;

    return 0;
}
