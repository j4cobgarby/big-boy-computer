#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

#include "types.hpp"

inline int execute(word_t *ram, int64_t *ac, word_t *pc, word_t *ir, sword_t *ar) {
    switch (*ir) {
    case 0x0: // HLT
        return -1;
    case 0x1: // ADD
        *ac += *ar;
        break;
    case 0x2: // SUB
        *ac -= *ar;
        break;
    case 0x3: // MUL
        *ac *= *ar;
        break;
    case 0x4: // DIV
        try {
            *ac /= *ar;
        } catch (const std::exception &ex) {
            cout << "CPU ERROR: Division by zero at " << *pc << endl;
            return -1;
        }
        break;
    case 0x5: // STA
        ram[*ar] = *ac;
        break;
    case 0x6: // LDA
        *ac = ram[*ar];
        break;
    case 0x7: // INP/OUT
        if (*ar == 0) {
            cout << "-> ";
            cin >> *ac;
        } else cout << *ac << endl;
        break;
    case 0x8: // JMZ
        if (*ac == 0) *pc = *ar - 1;
        break;
    case 0x9: // JNZ
        if (*ac != 0) *pc = *ar - 1;
        break;
    case 0xa: // JMP
        *pc = *ar - 1;
        break;
    case 0xb: break;
    case 0xc: break;
    case 0xd: break;
    case 0xe: break;
    case 0xf: break;
    default:
        cout << "CPU ERROR: Unrecognised instruction at " << *pc << endl;
        return -1;
    }

    return 0;
}

#endif
