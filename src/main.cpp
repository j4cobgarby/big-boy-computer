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

word_t ram[0xffff]; // Random access memory, video memory starts at 0xf000
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

void monitor_registers() {
    sf::RenderWindow win(sf::VideoMode(1500, 1500), "Register Monitor");
    Display disp(&win, ram + (0xffff - 0xfff));
    sf::Font fnt;
    fnt.loadFromFile("../assets/sansation/Sansation_Regular.ttf");

    sf::Text txt;
    txt.setFont(fnt);
    txt.setCharacterSize(30);
    txt.setFillColor(sf::Color::White);

    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
        }

        win.clear(sf::Color::Black);

        txt.setString("Accumulator: " + std::to_string(ac) +
            "\nProgram Counter: " + std::to_string(pc) +
            "\nInstruction Register: " + std::to_string(ir) +
            "\nAddress Register: " + std::to_string(ar) +
            "\nram[ffff]: " + std::to_string(ram[0xffff])
        );

        win.draw(txt);

        disp.draw();

        win.display();
    }
}

int main(int argc, char *argv[]) {
    //ram[0xff00] = 0xff00ff;
    //ram[0xffff] = 0x00ff00;
    std::thread mon_reg_thread(monitor_registers);

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

    word_t program[proglength / 4];

    cout << "Loading binary from: " << binfile_name << endl;
    cout << "The binary file is " << proglength << " bytes long." << endl;
    cout << "The binary file is " << proglength/4 << " words long." << endl;

    for (size_t i = 0; i < proglength; i++) {
        // Every four (8bit) characters in the file are one 32bit word
        if (i % sizeof(word_t) == 0) { // i = 0, 4, 8, ...
            char *tmp = new char[sizeof(word_t)];
            unsigned int pieces[4];

            pfile.seekg(i);
            pfile.read(tmp, sizeof(word_t));

            pieces[0] = (int)tmp[0] & 0xff;
            pieces[1] = (int)tmp[1] & 0xff;
            pieces[2] = (int)tmp[2] & 0xff;
            pieces[3] = (int)tmp[3] & 0xff;

            program[i/sizeof(word_t)] = (pieces[0] << 24) + (pieces[1] << 16) + (pieces[2] << 8) + (pieces[3]);
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
        sf::sleep(sf::milliseconds(100));
        ir = getopcode(ram[pc]);
        sf::sleep(sf::milliseconds(100));
        ar = getoperand(ram[pc]);

        // EXECUTE
        sf::sleep(sf::milliseconds(100));
        if (execute(ram, &ac, &pc, &ir, &ar) == -1) goto hlt;
    } while (++pc < sizeof(ram) / (sizeof(word_t)));
hlt:
    cout << "Done." << endl;

    mon_reg_thread.join();
}
