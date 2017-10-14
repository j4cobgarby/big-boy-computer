#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <iostream>
#include <cmath>

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
        if (*ar == 0) { // input ac
            cout << "-> "; cin >> *ac;
        } else if (*ar == 1) { // output ac
            cout << *ac << endl;
        } else if (*ar == 2) { // output ac as ascii
            cout << (char)*ac << endl;
        } else if ((*ar & 0xf) == 3) { // plot pixel
            unsigned short int adr = *ar >> 16;
            unsigned short int r = (*ar & 0xf000) >> 12;
            unsigned short int g = (*ar & 0xf00) >> 8;
            unsigned short int b = (*ar & 0xf0) >> 4;
            unsigned int vram_offset = 8192 - 256;
            ram[vram_offset+adr] = (r << 20) | (g << 12) | (b << 4);
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
    default:
        cout << "CPU ERROR: Unrecognised instruction at " << *pc << endl;
        cout << std::hex << *ir << endl;
        return -1;
    }
}

#endif
