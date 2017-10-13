#include <iostream>
#include <bitset>

#include "execute.hpp"
#include "types.hpp"

using std::cout;
using std::endl;
using std::cin;
using std::bitset;

const word_t PROGRAM_OFFSET = 0; // How far into the memory the program begins

word_t ram[4096]; // Random access memory
int64_t ac; // Accumulator - stores the result of the last calculation
word_t pc; // Program counter - store address of the next instruction
word_t ir; // Instruction register - stores top 4 bits of instruction
sword_t ar; // Address register - stores bottom 12 bits of instruction

inline word_t getopcode(word_t i) { return i >> 12; }
inline sword_t getoperand(word_t i) { return i & 0x0fff; }
inline void printram(uint16_t start, uint16_t length) {
    for (size_t i = start; i < start + length; i++) {
        cout << i << ": \t" <<
            bitset<4>(getopcode(ram[i])).to_string() << '\t' <<
            bitset<12>(getoperand(ram[i])).to_string() << endl;
    }
}

word_t program[] = {
    0x7000, // INP
    0x7001, // OUT
    0x0000, // HLT
};

int main() {
    pc = PROGRAM_OFFSET;

    // Load the program into the ram
    for (size_t i = 0; i < sizeof(program) / (sizeof(word_t)); i++) { // Divided by 2 cause 2 bytes per 16 bit word
        ram[i + PROGRAM_OFFSET] = program[i];
    }

    // Execute program
    do {
        // FETCH/DECODE
        ir = getopcode(ram[pc]);
        ar = getoperand(ram[pc]);

        // EXECUTE
        if (execute(ram, &ac, &pc, &ir, &ar) == -1) goto hlt;
    } while (++pc < sizeof(ram) / (sizeof(word_t)));

hlt:
    system("pause");
}
