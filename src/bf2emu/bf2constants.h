/* This file only contains constants to be used as BF2 progword constants
 */

/* Default on-reset values of various internal states */
#define BF2_RESET_JSP           0x8000
#define BF2_RESET_PC            0x0000
#define BF2_REVISION            0x0004
#define BF2_BUS_JSTACK          0

/* OPcode definitions */
#define BF2OP_ALU               0x0
#define BF2OP_JMP               0x1
#define BF2OP_CALL              0x2
#define BF2OP_MISC              0x3
#define BF2OP_JMPR              0x4
#define BF2OP_JMPRE             0x5
#define BF2OP_JMPRZ             0x6
#define BF2OP_JMPRC             0x7

#define BF2OP_ANDI              0x8
#define BF2OP_IORI              0x9
#define BF2OP_ADDI              0xA
#define BF2OP_SUBI              0xB
#define BF2OP_XORI              0xC
#define BF2OP_SUBRI             0xD
#define BF2OP_MVLI              0xE
#define BF2OP_MVHI              0xF

/* ALU OP arguments (modes) */
#define BF2ARG_ALU_AND          0x0
#define BF2ARG_ALU_IOR          0x1
#define BF2ARG_ALU_ADD          0x2
#define BF2ARG_ALU_SUB          0x3
#define BF2ARG_ALU_XOR          0x4
#define BF2ARG_ALU_SUBR         0x5
#define BF2ARG_ALU_MVL          0x6
#define BF2ARG_ALU_MVH          0x7
#define BF2ARG_ALU_REVISION     0x8
#define BF2ARG_ALU_MOV          0xA
#define BF2ARG_ALU_BSEL         0xC
#define BF2ARG_ALU_BSR          0xE
#define BF2ARG_ALU_BSL          0xF

/* MISC OP arguments */
#define BF2ARG_MISC_RD0         0x0
#define BF2ARG_MISC_RD1         0x1
#define BF2ARG_MISC_RD2         0x2
#define BF2ARG_MISC_RD3         0x3
#define BF2ARG_MISC_WR0         0x4
#define BF2ARG_MISC_WR1         0x5
#define BF2ARG_MISC_WR2         0x6
#define BF2ARG_MISC_WR3         0x7

#define BF2ARG_MISC_RETURN      0xC
#define BF2ARG_MISC_RETIE       0xD
#define BF2ARG_MISC_INTDIS      0xE
#define BF2ARG_MISC_EXTENDED    0xF

#define BF2ARG_MISCEX_CALLREG   0x0
#define BF2ARG_MISCEX_JMPREG    0x1


