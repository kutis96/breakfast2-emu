#include "emuhelpers.h"


void bf2emu_printintstate(bf2emu_machine_t * machine) {
    printf("====== CPU STATES ======\n");
    printf("CYC: %ld\n", machine->cyclecount);
    printf("PC:  0x%04x  JSP: 0x%04x\n", machine->intstate.pc, machine->intstate.jsp);
    printf("INT:%d  C:%d  Z:%d  E:%d\n", 
            machine->intstate.f_inten ? 1 : 0,
            machine->intstate.f_carry ? 1 : 0,
            machine->intstate.f_zero ? 1 : 0,
            machine->intstate.f_ext ? 1 : 0
            );
    printf("========================\n");
    for(int i = 0; i < 8; i++){
    printf("R%01d: 0x%04x  R%01d: 0x%04x\n", i, machine->intstate.regs[i], i+8, machine->intstate.regs[i+8]);
    };
    printf("========================\n");
}
