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

int load_program(const char *filename, const word32 code_start)
{
    byte *mem_base = MEM_base();

    FILE* f = fopen(filename, "r");
    if (!f)
    {
        fprintf(stderr, "Could not open <%s>\n", filename);
        return 0;
    }
    fread(mem_base+code_start, MEM_MAX, 1, f);
    fclose(f);
    return 1;
}

void run(void)
{
    byte *mem_base = MEM_base();;

    no_io = 0;
    CPU_reset();
    mem_base[0xfffc] = CODE_START & 0xFF;
    mem_base[0xfffd] = (CODE_START >> 8) & 0xFF;
    CPU_run();
}

int main(int argc, char** argv)
{
    CPUEvent_initialize(); // now needed

    if (argc >= 2)
    {
        if (load_program(argv[1], CODE_START))
        {
            if (argc >= 3 && !strcmp("dbg", argv[2]))
                CPU_setTrace(1);
            if (argc >= 3 && !strcmp("trace", argv[2]))
            {
                CPU_setTrace(1);
                trace = 1;
            }
            run();
        }
    }
    else
    {
        fprintf(stderr, "Usage: %s <filename> [options]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}
