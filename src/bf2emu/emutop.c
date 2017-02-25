#include "emutop.h"

bf2emu_machine_t * bf2emu_createmachine(void) {
    bf2emu_machine_t * machine = (bf2emu_machine_t *) malloc(sizeof (bf2emu_machine_t));

    //Set internal states to default values
    machine->intstate.f_inten = false;
    machine->intstate.f_carry = false;
    machine->intstate.f_zero = false;
    machine->intstate.f_ext = false;

    //Reset registers to defaults
    for (int i = 0; i < 16; i++)
        machine->intstate.regs[i] = 0x0000;

    //Reset everything else
    bf2emu_resetmachine(machine);

    return machine;
}

bool_t bf2emu_destroymachine(bf2emu_machine_t * machine) {
    free(machine); //Free all the machines!
}

void bf2emu_resetmachine(bf2emu_machine_t * machine) {
    machine->cyclecount = 0;

    machine->intstate.f_inten = false;

    machine->intstate.pc = BF2_RESET_PC;
    machine->intstate.jsp = BF2_RESET_JSP;
}

static inline void bf2emu_x_generateflags(uint32_t temp, bf2emu_machine_t * machine) {
    bf2emu_intstate_t * intstate = &(machine->intstate);

    intstate->f_carry = (temp & 0x10000) ? true : false;
    intstate->f_zero = (temp & 0xFFFF) ? false : true;
}

static inline uint16_t bf2emu_x_signex_12(uint16_t num) {
    return ( (num & 0x0800) ? (num | 0xF000) : (num));
}

static inline uint16_t bf2emu_x_signex_8(uint16_t num) {
    return ( (num & 0x0080) ? (num | 0xFF00) : (num));
}

bool_t bf2emu_tick(bf2emu_machine_t * machine) {

    /* Fetch current progword */
    bf2emu_progword_t curword = machine->progmem[ machine->intstate.pc ];
    bf2emu_intstate_t * intstate = &(machine->intstate);

    switch (curword.regreg.opcode) {
        case BF2OP_JMP:
        {
            intstate->pc = curword.longlit.lit & 0x0FFF;
            break;
        }
        case BF2OP_JMPR:
        {
            intstate->pc += bf2emu_x_signex_12(curword.longlit.lit);
            break;
        }
        case BF2OP_JMPRC:
        {
            if (intstate->f_carry) {
                intstate->pc += bf2emu_x_signex_12(curword.longlit.lit);
            } else {
                intstate->pc++;
            }
            break;
        }
        case BF2OP_JMPRZ:
        {
            if (intstate->f_zero) {
                intstate->pc += bf2emu_x_signex_12(curword.longlit.lit);
            } else {
                intstate->pc++;
            }
            break;
        }
        case BF2OP_JMPRE:
        {
            if (intstate->f_ext) {
                intstate->pc += bf2emu_x_signex_12(curword.longlit.lit);
            } else {
                intstate->pc++;
            }
            break;
        }
        case BF2OP_CALL:
        {
            intstate->jsp++;
            machine->io_write(machine, BF2_BUS_JSTACK, intstate->jsp, intstate.pc);
            intstate->pc = curword.longlit.lit & 0x0FFF;
        }
        case BF2OP_MISC:
        {
            switch (curword.regreg.mode) {
                case BF2ARG_MISC_RD0 | BF2ARG_MISC_RD1 | BF2ARG_MISC_RD2 | BF2ARG_MISC_RD3:
                {
                    uint16_t address = intstate->regs[curword.regreg.regb];
                    uint8_t bus = curword.regreg.mode & 0x3;

                    uint16_t read = machine->io_read(machine, bus, address);
                    intstate->regs[curword.regreg.regb] = read;

                    intstate->pc++;
                }
                case BF2ARG_MISC_WR0 | BF2ARG_MISC_WR1 | BF2ARG_MISC_WR2 | BF2ARG_MISC_WR3:
                {
                    uint16_t address = intstate->regs[curword.regreg.regb];
                    uint16_t data = intstate->regs[curword.regreg.rega];
                    uint8_t bus = curword.regreg.mode & 0x3;

                    machine->io_write(machine, bus, address, data);

                    intstate->pc++;
                }
                case BF2ARG_MISC_RETURN:
                {
                    intstate->pc = machine->io_read(machine, BF2_BUS_JSTACK, intstate->jsp);
                    intstate->jsp--;
                }
                case BF2ARG_MISC_RETIE:
                {
                    intstate->pc = machine->io_read(machine, BF2_BUS_JSTACK, intstate->jsp);
                    intstate->jsp--;
                    intstate->f_inten = true;
                }
                case BF2ARG_MISC_INTDIS:
                {
                    intstate->f_inten = false;
                    intstate->pc++;
                }
                case BF2ARG_MISC_EXTENDED:
                {
                    //TODO
                }
                
                default:
                    return false;
            }
        }
        case BF2OP_ALU:
        {
            uint32_t temp;
            uint32_t ina = (uint32_t) (intstate->regs[curword.regreg.rega]);
            uint32_t inb = (uint32_t) (intstate->regs[curword.regreg.regb]);

            switch (curword.regreg.mode) {
                case BF2ARG_ALU_AND:
                {
                    temp = ina & inb;
                    break;
                }
                case BF2ARG_ALU_IOR:
                {
                    temp = ina | inb;
                    break;
                }
                case BF2ARG_ALU_ADD:
                {
                    temp = ina + inb;
                    break;
                }
                case BF2ARG_ALU_SUB:
                {
                    temp = ina - inb;
                    break;
                }
                case BF2ARG_ALU_XOR:
                {
                    temp = ina ^ inb;
                    break;
                }
                case BF2ARG_ALU_SUBR:
                {
                    temp = inb - ina;
                    break;
                }
                case BF2ARG_ALU_MVL:
                {
                    temp = (ina & 0xFF00) |
                            (inb & 0x00FF);
                    break;
                }
                case BF2ARG_ALU_MVH:
                {
                    temp = ((inb & 0x00FF) << 8) |
                            (ina & 0x00FF);
                    break;
                }
                case BF2ARG_ALU_MOV:
                {
                    temp = inb;
                    break;
                }
                case BF2ARG_ALU_BSEL:
                {
                    temp = (ina >> inb) & 0x0001;
                    break;
                }
                case BF2ARG_ALU_BSR:
                {
                    temp = (ina >> inb);
                    break;
                }
                case BF2ARG_ALU_BSL:
                {
                    temp = (ina << inb);
                    break;
                }
                case BF2ARG_ALU_REVISION:
                {
                    temp = (uint32_t) BF2_REVISION;
                }
                default:
                    return false;
            }

            bf2emu_x_generateflags(temp, machine);
            intstate->regs[curword.regreg.rega] = (temp & 0xFFFF);
            intstate->pc++;

            break;
        } //END BF2OP_ALU
        default:
            return false;
    }

    machine->io_update(machine);
    machine->cyclecount++;

    return true;
}