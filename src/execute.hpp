#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <iostream>
#include <cmath>
#include <ctime>
#include <limits>

using std::cout;
using std::endl;
using std::cin;

#include "types.hpp"

inline int execute(word_t *ram, int64_t *ac, word_t *pc, word_t *ir, sword_t *ar) {
    srand(time(NULL));
    ram[0xf0] = rand() % 0xffffffff;

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
        if (*ar == 0) { // input ac
            while (!(cin >> *ac)) {
                cout << "INVALID INPUT ERROR: try again" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } else if (*ar == 1) { // output ac
            cout << *ac;
        } else if (*ar == 2) { // output ac as ascii
            cout << (char)*ac;
        } else if (*ar == 3) { // input ascii
            char in;
            while (!(cin >> in)) {
                cout << "INVALID INPUT ERROR: trye again" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            *ac = in;
        }
        return 0;
    case 0x0e: // JMP
        *pc = *ar - 1; return 0;
    case 0x0f: // JZ
        if (*ac == 0) *pc = *ar - 1;
        return 0;
    case 0x10: // JNZ
        if (*ac == 0) *pc = *ar - 1;
        return 0;
    case 0x11: // JG
        if (*ac > 0) *pc = *ar - 1;
        return 0;
    case 0x12: //JL
        if (*ac < 0) *pc = *ar - 1;
        return 0;
    case 0x13: // JGE
        if (*ac >= 0) *pc = *ar - 1;
        return 0;
    case 0x14: //JLE
        if (*ac <= 0) *pc = *ar - 1;
        return 0;
    case 0x15: // INC
        *ac += 1;
        return 0;
    case 0x16: // DEC
        *ac -= 1;
        return 0;
    default:
        cout << "CPU ERROR: Unimplemented instruction" << *pc << endl;
        cout << std::hex << *ir << endl;
        return -1;
    }
}

#endif
