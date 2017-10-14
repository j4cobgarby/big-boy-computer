#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

#include "types.hpp"

inline int execute(word_t *ram, int64_t *ac, word_t *pc, word_t *ir, sword_t *ar) {
    switch (*ir) {
    case 0x0:return -1;

    case 0x1:*ac += ram[*ar];break;
    case 0x2:*ac -= ram[*ar];break;
    case 0x3:*ac *= ram[*ar];break;
    case 0x4:
        try {
            *ac /= ram[*ar];
        } catch (const std::exception &ex) {
            return -1;
        }
        break;

    case 0x5:ram[*ar] = *ac;break;
    case 0x6:*ac = ram[*ar];break;

    case 0x7:
        if (*ar == 0) {
            cout << "-> ";
            cin >> *ac;
        }
        else if (*ar == 1) cout << *ac << endl;
        else if (*ar == 2) cout << (char)*ac << endl;
        break;

    case 0x8:if (*ac == 0) *pc = *ar - 1;break;
    case 0x9:if (*ac != 0) *pc = *ar - 1;break;
    case 0xa:*pc = *ar - 1;break;
    case 0xb:if (*ac > 0) *pc = *ar - 1;break;

    case 0xc:*ac >>= ram[*ar];break;
    case 0xd:*ac <<= ram[*ar];break;
    case 0xe:*ac &= ram[*ar];break;
    case 0xf:*ac |= ram[*ar];break;
    default:
        cout << "CPU ERROR: Unrecognised instruction at " << *pc << endl;
        return -1;
    }

    return 0;
}

#endif
