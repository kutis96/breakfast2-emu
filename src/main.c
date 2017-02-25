#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "bf2emu/emutop.h"
#include "emuhelpers.h"

int main(int argc, char ** argv) {

    bf2emu_machine_t * machine = NULL;
    machine = bf2emu_createmachine();


    bf2emu_progword_t test_progmem[65535];
    machine->progmem = test_progmem;

    machine->intstate.regs[0] = 0xFFFF;
    machine->intstate.regs[1] = 0x0001;

    test_progmem[0] = (bf2emu_progword_t) ((bf2emu_progword_regreg_t) {
        .opcode = BF2OP_ALU,
        .mode = BF2ARG_ALU_ADD,
        .rega = 0x0, .regb = 0x1
    });
    
    test_progmem[1] = (bf2emu_progword_t) ((bf2emu_progword_longlit_t) {
        .opcode = BF2OP_JMPRC,
        .lit = 0xFFFF
    });

    for (int i = 0; i < 5; i++) {
        bf2emu_printintstate(machine);
        bf2emu_tick(machine);
    }

    bf2emu_destroymachine(machine);
}
