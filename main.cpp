#include <iostream>
#include <cstdint>
#include <bitset>

using std::cout;
using std::endl;
using std::cin;
using std::bitset;

typedef uint16_t word_t; // Word length = 16 bits
typedef int16_t sword_t; // Signed word

const word_t program_offset = 0; // How far into the memory the program begins

word_t ram[4096]; // Random access memory
sword_t ac; // Accumulator - stores the result of the last calculation
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
    0b0000, // HLT
};

int main() {
    pc = program_offset;

    // Load the program into the ram
    for (size_t i = 0; i < sizeof(program) / (sizeof(word_t)); i++) { // Divided by 2 cause 2 bytes per 16 bit word
        ram[i + program_offset] = program[i];
    }

    // Execute program..
    // Iterate from the start of the program to the end of the ram.
    do {
        // FETCH/DECODE
        ir = getopcode(ram[pc]);
        ar = getoperand(ram[pc]);

        // EXECUTE
        switch (ir) {
        case 0x0: // HLT
            goto hlt;
        case 0x1: // ADD
            ac += ar;
            break;
        case 0x2:
            ac -= ar;
            break;
        case 0x3:
            ac *= ar;
            break;
        case 0x4:
            try {
                ac /= ar;
            } catch (const std::exception &ex) {
                cout << "CPU ERROR: Division by zero at " << pc << endl;
                goto hlt;
            }
            break;
        case 0x5:
            ram[ar] = ac;
            break;
        case 0x6:
            ac = ram[ar];
            break;
        case 0x7:
            if (ar == 0) {
                cout << "signed 16 bit integer INPUT: ";
                cin >> ac;
            } else cout << ac << endl;
            break;
        case 0x8:
            if (ac == 0) pc = ar - 1;
            break;
        case 0x9:
            if (ac != 0) pc = ar - 1;
            break;
        case 0xa:
            pc = ar - 1;
            break;
        case 0xb: break;
        case 0xc: break;
        case 0xd: break;
        case 0xe: break;
        case 0xf: break;
        default:
            cout << "CPU ERROR: Unrecognised instruction at " << pc << endl;
            goto hlt;
        }
    } while (++pc < sizeof(ram) / (sizeof(word_t)));

hlt:cout << "Execution finished." << endl;
    system("pause");
}
