#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lib65816/cpu.h>
#include <lib65816/cpuevent.h>

#include "mem.h"

/**
 * @brief Represents whether tracing is enabled or not
 *
 * This variable is used to determine whether tracing is enabled or not.
 * If tracing is enabled, it means that the program will output debug information
 * during execution.
 */
int trace;

#define CODE_START 0x200

/**
 * @brief Handles the WDM opcode in the emulation
 *
 * This function handles the WDM opcode in the emulation and
 * updates the hardware based on the provided opcode and timestamp.
 *
 * @param opcode The opcode representing the WDM operation
 * @param timestamp The timestamp representing the current time
 */
void EMUL_handleWDM(byte opcode, word32 timestamp)
{
}

/**
 * @brief Updates the hardware in the emulation
 *
 * This function updates the hardware in the emulation based on the provided timestamp.
 *
 * @param timestamp The timestamp representing the current time
 */
void EMUL_hardwareUpdate(word32 timestamp)
{
}

/**
 * @brief Loads a program from a file into memory
 *
 * This function loads a program from a file into the memory starting from the specified code start address.
 *
 * @param filename The name of the file containing the program
 * @param code_start The starting address in memory for the program to be loaded
 * @return 1 if the program was loaded successfully, 0 otherwise
 */
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

/**
 * @brief Executes the run method of the program.
 *
 * This method executes the main functionality of the program. It performs the following steps:
 * - Retrieves the base address of the memory using MEM_base() function.
 * - Initializes the no_io variable to 0.
 * - Resets the CPU using the CPU_reset() function.
 * - Sets the start address of the code in the memory using the CODE_START constant.
 * - Runs the CPU using the CPU_run() function.
 *
 * @note This method assumes that the load_program function has already been called to load the program into memory.
 */
void run(void)
{
    byte *mem_base = MEM_base();;

    no_io = 0;
    CPU_reset();
    mem_base[0xfffc] = CODE_START & 0xFF;
    mem_base[0xfffd] = (CODE_START >> 8) & 0xFF;
    CPU_run();
}

/**
 * @brief The main entry point of the program
 *
 * This function is the main entry point of the program. It takes command line arguments
 * and executes the appropriate actions based on the arguments.
 *
 * @param argc The number of command line arguments
 * @param argv An array of strings containing the command line arguments
 * @return Returns 0 on successful execution, or an error code on failure
 */
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
