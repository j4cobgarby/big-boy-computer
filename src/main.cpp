#include <iostream> // cout, endl, cin
#include <string>   // string(int, char)
#include <thread> // thread
#include <SFML/Graphics.hpp> // sf

#include "execute.hpp"  // execute()
#include "types.hpp"    // word_t, sword_t
#include "pixplot.hpp"

using std::cout;
using std::endl;
using std::cin;

const word_t PROGRAM_OFFSET = 0; // How far into the memory the program begins

word_t ram[8192]; // Random access memory
int64_t ac; // Accumulator - stores the result of the last calculation
word_t pc; // Program counter - store address of the next instruction
word_t ir; // Instruction register - stores top 8 bits of instruction
sword_t ar; // Address register - stores bottom 24 bits of instruction

inline word_t getopcode(word_t i) { return i >> 24; }
inline sword_t getoperand(word_t i) { return i & 0x00ffffff; }
inline void printram(uint16_t start, uint16_t length) {
    cout << "offset\tvalue\n" << std::string(23, '=') << '\n';
    for (size_t i = start; i < start + length; i++) {
        cout <<
            "0x" << std::hex << i << ": \t" <<
            "0x" << std::hex << ram[i] << '\t' << endl;
    }
}

word_t program[] = {
    0x00000000,

    0x0d00f003,
    0x0d01e003,
    0x0d02d003,
    0x0d03c003,
    0x0d04b003,
    0x0d05a003,
    0x0d069003,
    0x0d078003,
    0x0d087003,
    0x0d096003,
    0x0d0a5003,
    0x0d0b4003,
    0x0d0c3003,
    0x0d0d2003,
    0x0d0e1003,
    0x0d0f0003,

    0x0d100f03,
    0x0d110e03,
    0x0d120d03,
    0x0d130c03,
    0x0d140b03,
    0x0d150a03,
    0x0d160903,
    0x0d170803,
    0x0d180703,
    0x0d190603,
    0x0d1a0503,
    0x0d1b0403,
    0x0d1c0303,
    0x0d1d0203,
    0x0d1e0103,
    0x0d1f0003,

    0x0d2000f3,
    0x0d2100e3,
    0x0d2200d3,
    0x0d2300c3,
    0x0d2400b3,
    0x0d2500a3,
    0x0d260093,
    0x0d270083,
    0x0d280073,
    0x0d290063,
    0x0d2a0053,
    0x0d2b0043,
    0x0d2c0033,
    0x0d2d0023,
    0x0d2e0013,
    0x0d2f0003,

    0x00000000, // HLT
};

void drawvid(Display *disp) {
    while (true) {
        disp->draw();
    }
}

int main() {
    sf::RenderWindow monitor(sf::VideoMode(16 * PIXEL_SIZE, 16 * PIXEL_SIZE), "Monitor");
    monitor.setActive(false);
    Display display(&monitor, ram + (sizeof(ram)/sizeof(word_t)) - 256);

    // Constantly draw the video memory in the background
    std::thread drawthread(drawvid, &display);

    pc = PROGRAM_OFFSET + program[0] + 1; // set pc to the first instruction after data

    // Load the program into the ram
    for (size_t i = 0; i < sizeof(program) / (sizeof(word_t)); i++) { // Divided by 2 cause 2 bytes per 16 bit word
        ram[i + PROGRAM_OFFSET] = program[i];
    }

    do {
        // FETCH/DECODE
        ir = getopcode(ram[pc]);
        ar = getoperand(ram[pc]);

        // EXECUTE
        if (execute(ram, &ac, &pc, &ir, &ar) == -1) goto hlt;
    } while (++pc < sizeof(ram) / (sizeof(word_t)));

hlt:
    system("pause");

    drawthread.join();
}
