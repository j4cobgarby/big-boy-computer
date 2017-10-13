# Big
![](http://memes.ucoz.com/_nw/21/31079907.jpg)
# Computer

---

# Intro

A very simple CPU emulator written in c++, for me to learn how a cpu works in more detail.

Current features:
 - Fetch-decode-execute cycle
 - 16 machine code instructions (10 actually implemented)

# Building

Make sure you have g++ installed

```
$ git clone https://github.com/j4cobgarby/big-boy-computer.git
$ cd big-boy-computer
$ g++ main.cpp
$ ./a.out # This command may vary depending on your machine. Just run the executable.
```

# `INSTRUCTIONS`

```
~~~~             - Opcode
0000000000000000 - 16 bits long
    ~~~~~~~~~~~~ - Operand

ac = Accumulator
ar = Address register

|	Opcode	|	Description
 d  b     h

 0	0000  0	|	HLT: ends program execution
 1	0001  1	|	ADD: ac = ac + ar
 2	0010  2	|	SUB: ac = ac - ar
 3	0011  3	|	MUL: ac = ac * ar
 4	0100  4	|	DIV: ac = ac / ar
 5	0101  5	|	STA: copy ac to the memory address pointed to by ar
 6	0110  6	|	LDA: loads memory address pointed to by ar into ac
 7	0111  7	|	INP/OUT: Input to ac if ar = 0, otherwise display contents of ac
 8	1000  8	|	JMZ: jumps to address pointed to by ar if ac = 0
 9	1001  9	|	JNZ: same as JMZ, except only if ac != 0
 10	1010  a	|	JMP: jump to the address pointed to by ar
 11	1011  b	|
 12	1100  c	|
 13	1101  d	|
 14	1110  e	|
 15	1111  f	|
```
