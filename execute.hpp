#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

#include "types.hpp"

inline int execute(word_t *ram, int64_t *ac, word_t *pc, word_t *ir, sword_t *ar) {
    switch (*ir) {
    case 0x00: return -1;
    case 0x01: // ADD
        *ac += ram[*ar]; return 0;
    case 0x02: // SUB
        *ac -= ram[*ar]; return 0;
    case 0x03: // MUL
        *ac *= ram[*ar]; return 0;
    case 0x04: // DIV
        *ac /= ram[*ar]; return 0;
    case 0x05: // RSH
        *ac >>= ram[*ar]; return 0;
    case 0x06: // LSH
        *ac <<= ram[*ar]; return 0;
    case 0x07: // NOT
        *ac = ~*ac; return 0;
    case 0x08: // AND
        *ac &= ram[*ar]; return 0;
    case 0x09: // OR
        *ac |= ram[*ar]; return 0;
    case 0x0a: // XOR
        *ac ^= ram[*ar]; return 0;
    case 0x0b: // STA
        ram[*ar] = *ac; return 0;
    case 0x0c: // LDA
        *ac = ram[*ar]; return 0;
    case 0x0d: // INP/OUT
        if (*ar == 0) {
            cout << "-> "; cin >> *ac;
        } else if (*ar == 1) {
            cout << *ac << endl;
        } else if (*ar == 2) {
            cout << (char)*ac << endl;
        }
        return 0;
    case 0x0e: // JMP
        *pc = *ar - 1; return 0;
    default:
        cout << "CPU ERROR: Unrecognised instruction at " << *pc << endl;
        cout << std::hex << *ir << endl;
        return -1;
    }
}

#endif
