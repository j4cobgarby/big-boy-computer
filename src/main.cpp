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

word_t program[] {
    0x00000001,
    0x00ff0000,

    0x0c000001,
    0x0b001fff,

    0x00000000,
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
