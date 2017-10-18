#include <iostream> // cout, endl, cin
#include <string>   // string(int, char)
#include <thread> // thread
#include <SFML/Graphics.hpp> // sf
#include <fstream> // ifstream, ofstream

#include "execute.hpp"  // execute()
#include "types.hpp"    // word_t, sword_t
#include "pixplot.hpp"

using std::cout;
using std::endl;
using std::cin;

const word_t PROGRAM_OFFSET = 0; // How far into the memory the program begins

word_t ram[16777216]; // Random access memory - 16 mega-words
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

bool running = true;

void drawvid(Display *disp) {
    while (running) {
        disp->draw();
    }
}

int main(int argc, char *argv[]) {
    std::string binfile_name;

    if (argc <= 1) {
        cout << "Local path to the binary file to load: ";
        cin >> binfile_name;
    } else {
        // Command-line arg given
        binfile_name = argv[1];
    }
    std::ifstream pfile(binfile_name, std::ios::binary | std::ios::ate);

    std::size_t proglength = pfile.tellg();
    pfile.seekg(0, std::ios::beg);

    word_t program[11];

    cout << "Loading binary from: " << binfile_name << endl;
    cout << "The binary file is " << proglength << " bytes long." << endl;

    for (size_t i = 0; i < proglength; i++) {
        // Every four (8bit) characters in the file are one 32bit word
        if (i % sizeof(word_t) == 0) { // i = 0, 4, 8, ...
            char *tmp = new char[sizeof(word_t)];
            word_t inst = 0;

            pfile.seekg(i);
            pfile.read(tmp, sizeof(word_t));

            for (size_t c = 0; c < sizeof(word_t); c++) {
                inst += tmp[c] << ((3-c) * (sizeof(word_t) * 2));
            }
            program[i/sizeof(word_t)] = inst;
        }
    }
    cout << "Done." << endl;

    pc = PROGRAM_OFFSET + program[0] + 1; // set pc to the first instruction after data

    // Load the program into the ram
    cout << "Loading program into RAM" << endl;
    for (size_t i = 0; i < sizeof(program) / (sizeof(word_t)); i++) { // Divided by 2 cause 2 bytes per 16 bit word
        ram[i + PROGRAM_OFFSET] = program[i];
    }
    cout << "Done." << "\nEmulating program...\n" << endl;

    do {
        // FETCH/DECODE
        ir = getopcode(ram[pc]);
        ar = getoperand(ram[pc]);

        // EXECUTE
        if (execute(ram, &ac, &pc, &ir, &ar) == -1) goto hlt;
    } while (++pc < sizeof(ram) / (sizeof(word_t)));
hlt:
    cout << "Done." << endl;
}
