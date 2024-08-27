#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lib65816/cpu.h>
#include <lib65816/cpuevent.h>

#define MEM_MAX ((4*1024*1024)-1)

typedef unsigned char byte;
typedef unsigned int word32;

// Function prototypes
byte MEM_readMem(word32 address, word32 timestamp, word32 emulFlags);
void MEM_writeMem(word32 address, byte b, word32 timestamp);

extern byte addressSpace[MEM_MAX];
extern int no_io;
#endif // MEM_H