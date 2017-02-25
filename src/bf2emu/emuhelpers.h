#ifndef EMUHELPERS_H
#define EMUHELPERS_H

#include <stdlib.h>
#include <stdio.h>
#include "common-types.h"
#include "emutop.h"


/* Allocates program memory for the emulator and loads
 * a BF2 binary file's contents into it.
 * 
 */
sc_error_t bf2emu_createprogmem_fromfile(FILE * f, bf2emu_progword_t * progmem);
        
void bf2emu_printintstate(bf2emu_machine_t * machine);

#endif /* EMUHELPERS_H */

