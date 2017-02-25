#ifndef bf2_emutop
#define bf2_emutop

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "common-types.h"
#include "bf2constants.h"

/* Program word structure, Register-Register type */
typedef struct {
    uint16_t opcode : 4;
    uint16_t rega : 4;
    uint16_t regb : 4;
    uint16_t mode : 4;
} bf2emu_progword_regreg_t;

/* Program word structure, Register-Literal type */
typedef struct {
    uint16_t opcode : 4;
    uint16_t rega : 4;
    uint16_t lit : 8;
} bf2emu_progword_reglit_t;

/* Program word structure, Long literal type */
typedef struct {
    uint16_t opcode : 4;
    uint16_t lit : 12;
} bf2emu_progword_longlit_t;

typedef union {
    uint16_t word;
    bf2emu_progword_regreg_t regreg;
    bf2emu_progword_reglit_t reglit;
    bf2emu_progword_longlit_t longlit;
} bf2emu_progword_t;

/* A struct containing all the BF2 CPU's internal states.
 * 
 * This includes the whole register file, program counter, and flags.
 */
typedef struct {
    uint16_t regs[16]; /* register file */

    uint16_t pc; /* program counter */

    uint16_t jsp; /* jump stack pointer */

    bool_t f_inten : 1; /* interrupts-enabled flag */
    bool_t f_carry : 1; /* carry flag */
    bool_t f_zero : 1; /* zero flag  */
    bool_t f_ext : 1; /* external flag register  */
    
    uint16_t intmask;   /* Interrupt mask */
} bf2emu_intstate_t;

/* A struct containing all of the BF2 machine's states.
 *
 * 
 */
typedef struct bf2emu_machine_t {
    /* A number of machine cycles elapsed since the start of the machine.
     * Possibly useful for debugging and code optimization.
     */
    uint64_t cyclecount;

    /* Struct holding the BF2 CPU's internal state */
    bf2emu_intstate_t intstate;

    /* A pointer to the program memory.
       That should simply be an array of bf2emu_progword_t */
    bf2emu_progword_t * progmem;

    
    
    /* A method called when the CPU requests an IO write.
     * bus:   0 typically shared with program RAM  0-3, 
     * address: 16-bit address
     * data:    data to write
     */
    void (*io_write) (struct bf2emu_machine_t * machine, uint8_t bus, uint16_t address, uint16_t data);

    /* A function called when the CPU requests an IO read 
     * bus:   0 typically shared with program RAM  0-3, 
     * address: 16-bit address
     */
    uint16_t(*io_read) (struct bf2emu_machine_t * machine, uint8_t bus, uint16_t address);

    /* A function called every cycle intended to update some IO state periodically.
     * Interrupts and 
     */
    void (*io_update) (struct bf2emu_machine_t * machine);
    
} bf2emu_machine_t;



void bf2emu_default_iowrite (bf2emu_machine_t * machine, uint8_t bus, uint16_t address, uint16_t data);

uint16_t bf2emu_default_ioread (bf2emu_machine_t * machine, uint8_t bus, uint16_t address);

void bf2emu_default_ioupdate (bf2emu_machine_t * machine);




bf2emu_machine_t * bf2emu_createmachine(void);

bool_t bf2emu_destroymachine(bf2emu_machine_t * machine);


void bf2emu_resetmachine(bf2emu_machine_t * machine);


/* Simulates a single `machine cycle' of the provided machine. */
bool_t bf2emu_tick(bf2emu_machine_t * machine);

#endif