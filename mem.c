#include "mem.h"

/**
 * @brief The memory address space.
 *
 * This variable represents the memory address space. It is an array of bytes
 * with a size of MEM_MAX. The memory address space is where data can be read
 * from and written to during program execution.
 *
 * @note The memory address space is defined in mem.h and has a size of MEM_MAX.
 *       MEM_MAX is calculated as (4 * 1024 * 1024) - 1.
 *
 * @see mem.h
 */
byte addressSpace[MEM_MAX];

/**
 * @brief Indicates if I/O operations are enabled.
 *
 * The variable "no_io" is an integer that indicates whether I/O operations are enabled or disabled.
 * When "no_io" is set to 0, I/O operations are enabled. When "no_io" is set to a non-zero value,
 * I/O operations are disabled.
 *
 * @note The variable "no_io" is initially set to 0 in the "debugger.c" file but can be changed in other parts of the program.
 *
 * @see debugger.c
 */
int no_io;

/**
 * @brief Reads a byte from standard input in a blocking manner.
 *
 * This function reads a byte from standard input and returns it as a byte value.
 * It uses the getchar() function to read the byte.
 *
 * @return The byte read from standard input.
 *
 * @note This function assumes that the byte read is within the range of valid byte values.
 *       If the reading operation encounters an error, the behavior is dependent on the
 *       implementation of the getchar() function.
 */
byte BlockingRead(void)
{
    return (byte)(getchar());
}

/**
 * @brief Writes a byte to the standard output.
 *
 * This function writes a byte to the standard output. It takes a byte as
 * input and prints it to the standard output using the putchar function. The
 * function then immediately flushes the standard output using fflush.
 *
 * @param b The byte to be written to the standard output.
 *
 * @see putchar
 * @see fflush
 */
void Emit(byte b)
{
    putchar((int)b);
    fflush(stdout);
}

/**
 * @brief Returns a pointer to the base of the memory address space.
 *
 * This function returns a pointer to the base of the memory address space by
 * returning the address of the first element of the "addressSpace" array.
 *
 * @return A pointer to the base of the memory address space.
 *
 * @see addressSpace[]
 */
byte *MEM_base(void)
{
    return &addressSpace[0];
}

/**
 * @brief Reads a byte from memory at the given address.
 *
 * This function reads a byte from memory at the specified address.
 * The address is first masked to ensure it is within the valid memory range.
 *
 * @param address The address to read from.
 * @param timestamp The timestamp value.
 * @param emulFlags The emulation flags.
 * @return The byte value at the specified address.
 *
 * @note The address is masked to ensure it is within the valid memory range.
 *       If the address is greater than MEM_MAX, 0 is returned.
 *
 * @note If the address is 0x000001 and the no_io flag is not set, it returns the result of the BlockingRead function.
 *
 * @see BlockingRead()
 */
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

/**
 * @brief Writes a byte to memory at the given address.
 *
 * This function writes a byte to memory at the specified address.
 *
 * @param address The address to write to.
 * @param b The byte value to write.
 * @param timestamp The timestamp value.
 *
 * @note If the address is 0x000000, the function exits if the byte value is 0. Otherwise, it calls the Emit function.
 *
 * @see Emit()
 */
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