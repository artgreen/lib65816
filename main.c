#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lib65816/cpu.h>
#include <lib65816/cpuevent.h>

#include "mem.h"

int trace;

#define CODE_START 0x200

void EMUL_handleWDM(byte opcode, word32 timestamp)
{
}

void EMUL_hardwareUpdate(word32 timestamp)
{
}

int main(int argc, char** argv)
{
    FILE* f = 0;

    CPUEvent_initialize(); // now needed

    if (argc >= 2)
        f = fopen(argv[1], "r");

    if (!f)
    {
        fprintf(stderr, "Could not open <%s>\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    fread(&addressSpace[CODE_START], sizeof(addressSpace), 1, f);
    fclose(f);

    no_io = 0;
    CPU_reset();
    addressSpace[0xfffc] = CODE_START & 0xFF;
    addressSpace[0xfffd] = (CODE_START >> 8) & 0xFF;

    if (argc >= 3 && !strcmp("dbg", argv[2]))
        CPU_setTrace(1);
    if (argc >= 3 && !strcmp("trace", argv[2]))
    {
        CPU_setTrace(1);
        trace = 1;
    }
    CPU_run();

    return 0;
}
