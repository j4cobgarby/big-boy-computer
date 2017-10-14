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
~~~~~~~~ <- opcode (8 bits)
00000000000000000000000000000000 - 32 bits wide total
        ~~~~~~~~~~~~~~~~~~~~~~~~ <- operand (24 bits)

notes:
    0:  if ar == 0
            ac = prompt input
        if ar == 1
            output ac

Opcode  Description
-------------------------------------------
0x00    HLT: stop program execution
0x01    ADD: ac += ram[ar]
0x02    SUB: ac -= ram[ar]
0x03    MUL: ac *= ram[ar]
0x04    DIV: ac /= ram[ar]
0x05    RSH: ac >>= ram[ar]
0x06    LSH: ac <<= ram[ar]
0x07    NOT: ac = ~ac
0x08    AND: ac &= ram[ar]
0x09    OR:  ac |= ram[ar]
0x0a    XOR: ac ^= ram[ar]
0x0b    STA: ram[ar] = ac
0x0c    LDA: ac = ram[ar]
0x0d    INP/OUT: notes(0)
0x0e    JMP: transfers flow of execution to ar

    -- 0x0f-0xff ommitted, because they're not implemented yet
```
