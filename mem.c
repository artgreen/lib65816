#include "mem.h"

byte addressSpace[MEM_MAX];
int no_io;

byte BlockingRead(void)
{
    return (byte)(getchar());
}

byte NonBlockingRead(void)
{
    return 0x00;
}

void Emit(byte b)
{
    putchar((int)b);
    fflush(stdout);
}

byte *MEM_base(void)
{
    return &addressSpace[0];
}
byte MEM_readMem(word32 address, word32 timestamp, word32 emulFlags)
{
    address &= 0xFFFFFF;

    if (address > MEM_MAX)
    {
        return 0;
    }

    if (address == 0x000001 && !no_io) return BlockingRead();

    return addressSpace[address];
}

void MEM_writeMem(word32 address, byte b, word32 timestamp)
{
    if (address == 0x000000)
    {
        if (b == 0)
            exit(0);
        Emit(b);
        return;
    }

    addressSpace[address] = b;
}