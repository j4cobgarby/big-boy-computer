# Big
![Boi](http://memes.ucoz.com/_nw/21/31079907.jpg)
# Computer

---

# Intro

A very simple CPU emulator written in c++, inspired by [LMC](https://peterhigginson.co.uk/LMC/) for me to learn how a cpu works in more detail.

Current features:
 - Fetch-decode-execute cycle
 - 32-bit architecture (256 CPU instructions, not all implemented)
 - A 16x16 pixels "monitor" with a 12-bit colour depth

# Building

Make sure you have:
 - g++
 - cmake
 - sfml (for pixel plotting)

```
$ git clone https://github.com/j4cobgarby/big-boy-computer.git
$ mkdir big-boy-computer/build && cd big-boy-computer/build
$ cmake ../src -G "<Insert your favourite Makefiles type here>"
$ make
```

# Overview of the registers
```
int64_t ac; // Accumulator - stores the result of the last calculation
word_t pc; // Program counter - store address of the next instruction
word_t ir; // Instruction register - stores top 8 bits of instruction
sword_t ar; // Address register - stores bottom 24 bits of instruction
```

# Writing a program in machine code

## Introduction

Currently, to write a program for the big boy computer (bbc), you need to edit an
array in `main.cpp` called `program`, which holds the instructions. Because of this,
every change in the machine code program will mean you need to recompile bbc.

## Starting

Have a look at `INSTRUCTIONS` (file) for a comprehensive list of all the CPU
instructions along with a synopsis of an instruction.

A program must start with (i.e. the first word of a program in ram must be) a
number representing how many pieces of data you want to initialise. The CPU
then skips ahead this amount of instructions, assuming that they're pieces of data.

### Example

Say you wanted to be able to access a memory address with the value of 10 (an ASCII
newline), your program may look like this (base 2, note the padding zeroes are of course optional):

```
0000000000000000000000000000001
0000000000000000000000000001010
... (rest of program) ...
0000000000000000000000000000000
```

Or equally (base 16)

```
00000001
0000000a
... (rest of program) ...
00000000
```

And, annotated:

```
00000001    # Tell the processor that the next 1 word is data, not an instruction
0000000a    # This address in RAM is now 10
... (rest of program) ...
00000000    # And all programs must end with 0, which is the halt instruction
```
