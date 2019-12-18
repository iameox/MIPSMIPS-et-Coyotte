#include <stdio.h>
#include "functions.h"
#include "registers.h"
#include "memory.h"

#define ADRESS_ALIGNEMENT_MASK 0xfffffffc
#define LOWER_64_MASK 0xffffffff

/* EXCEPTIONS A GERER (Trap) */
/* REGISTRES SPECIAUX A IMPLEMENTER : PC HI LO */
/* GERER LA DIVISION PAR 0 */

int mips_add(int arg1, int arg2, int arg3) {
    int8_t rs = arg2,
           rt = arg3,
           rd = arg1;
    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

    writeRegister(rd, rsValue + rtValue);
    return getTypeRWord(0, rs, rt, rd, 0, 0x20);
}

int mips_addi(int arg1, int arg2, int arg3) {
    int8_t rs = arg2,
           rt = arg1;
    int16_t immediate = arg3;
    int32_t rsValue = readRegister(rs);

    writeRegister(rt, rsValue + immediate);
    return getTypeIWord(0x8, rs, rt, immediate);
}

int mips_and(int arg1, int arg2, int arg3) {
    int8_t rs = arg2,
           rt = arg3,
           rd = arg1;
    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

    writeRegister(rd, rsValue & rtValue);
    return getTypeRWord(0, rs, rt, rd, 0, 0x24);
}

int mips_beq(int arg1, int arg2, int arg3) {
    int8_t rs = arg1,
           rt = arg2;
    int16_t offset = arg3; 
    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

        if(rsValue == rtValue) {
            PC += offset<<2; /* Il faut décaler de 2 */
        }

    return getTypeIWord(0x4, rs, rt, offset);
}

int mips_bgtz(int arg1, int arg2, int arg3) {
    int8_t rs = arg1;
    int16_t offset = arg2; 
    int32_t rsValue = readRegister(rs);

        if(rsValue > 0) {
            PC += offset<<2; /* Il faut décaler de 2 */
        }

    return getTypeIWord(0x7, rs, 0, offset);
}

/* JEN ETAIS LAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA */

int mips_blez(int arg1, int arg2, int arg3) {
    int rs = arg1,
        offset = arg2<<2; /* Il faut décaler de 2 */
    int32_t rsValue = readRegister(rs);

        if(rsValue <= 0) {
            PC += offset;
        }

    return getTypeIWord(0x6, rs, 0, offset);
}

int mips_bne(int arg1, int arg2, int arg3) {
    int rs = arg1,
        rt = arg2,
        offset = arg3<<2; /* Il faut décaler de 2 */
    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

        if(rsValue != rtValue) {
            PC += offset;
        }

    return getTypeIWord(0x5, rs, rt, offset);
}

int mips_div(int arg1, int arg2, int arg3) {
    int rs = arg1,
        rt = arg2;
    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

    if(rtValue != 0){
        HI = rsValue/rtValue;
        LO = rsValue%rtValue;
    } else {
        printf("ERREUR : DIVISION PAR 0\n");
    }

    return getTypeRWord(0, rs, rt, 0, 0, 0x1A);
}

int mips_j(int arg1, int arg2, int arg3) {
    int instr_index = arg1 << 2; /* Il faut décaler de 2 */
    
    PC = instr_index << 2;

    return getTypeJWord(0x2, instr_index);
}

int mips_jal(int arg1, int arg2, int arg3) {
    int instr_index = arg1 << 2, /* Il faut décaler de 2 */
    returnAdressLink; /* = PC + 4*/

    PC = instr_index;

    writeRegister(31, returnAdressLink);

    return getTypeJWord(0x3, instr_index);
}

int mips_jr(int arg1, int arg2, int arg3) {
    int rs = arg1,
    rsValue = readRegister(rs);

    rsValue = rsValue & ADRESS_ALIGNEMENT_MASK; /* On force les 2 LSB à 0 pour que l'adresse soit alignée */
    
    PC = rsValue;

    // on considère le hint à 0 (comportement par défaut)
    return getTypeRWord(0, rs, 0, 0, 0, 0x8);
}

int mips_lui(int arg1, int arg2, int arg3) {
    int rt = arg1,
        immediate = arg2;

    immediate = immediate << 16;

    writeRegister(rt, immediate);

    return getTypeIWord(0xF, 0, rt, immediate);
}

int mips_lw(int arg1, int arg2, int arg3) {
    int base = arg3,
        rt = arg1,
        offset = arg2,
        registerAddress = readRegister(base);
        value = readMemory(registerAddress + offset);

    /* IL FAUT CHECK L'ALIGNEMENT */

    writeRegister(rt, value);

    return getTypeIWord(0x23, base, rt, offset);
}

int mips_mfhi(int arg1, int arg2, int arg3) {
    int rd = arg1;

    writeRegister(rd, HI);

    return getTypeRWord(0, 0, 0, rd, 0, 0x10);
}

int mips_mflo(int arg1, int arg2, int arg3) {
    int rd = arg1;

    writeRegister(rd, LO);

    return getTypeRWord(0, 0, 0, rd, 0, 0x12);
}

int mips_mult(int arg1, int arg2, int arg3) {
    int rs = arg1,
        rt = arg2,
        rsValue = readRegister(rs),
        rtValue = readRegister(rt),
        result = rsValue * rtValue;

    HI = result>>32;
    LO = result & LOWER_64_MASK; 

    return getTypeRWord(0, rs, rt, 0, 0, 0x18);
}

int mips_nop(int arg1, int arg2, int arg3) {
    return getTypeRWord(0, 0, 0, 0, 0, 0);
}

int mips_or(int arg1, int arg2, int arg3) {
    int rs = arg2,
        rt = arg3,
        rd = arg1,
        rsValue = readRegister(rs),
        rtValue = readRegister(rt);

    writeRegister(rd, rsValue | rtValue);

    return getTypeRWord(0, rs, rt, rd, 0, 0x25);
}

int mips_rotr(int arg1, int arg2, int arg3) {
    int rt = arg2,
        rd = arg1,
        sa = arg3,
        rtValue = readRegister(rt);

    writeRegister(rd, (rtValue >> sa) + (rtValue << 32-sa));

    return getTypeRWord(0, 0x1, rt, rd, sa, 0x2);
}

int mips_sll(int arg1, int arg2, int arg3) {
    int rt = arg2,
        rd = arg1,
        sa = arg3,
        rtValue = readRegister(rt);

    writeRegister(rd, rtValue << sa);

    return getTypeRWord(0, 0, rt, rd, sa, 0x0);
}

int mips_slt(int arg1, int arg2, int arg3) {
    int rs = arg2,
        rt = arg3,
        rd = arg1,
        rsValue = readRegister(rs),
        rtValue = readRegister(rt);

    writeRegister(rd, rsValue < rtValue);

    return getTypeRWord(0, rs, rt, rd, 0, 0x2A);
}

int mips_srl(int arg1, int arg2, int arg3) {
    int rt = arg2,
        rd = arg1,
        sa = arg3,
        rtValue = readRegister(rt);

    writeRegister(rd, rtValue >> sa)

    return getTypeRWord(0, 0, rt, rd, sa, 0x2);
}

int mips_sub(int arg1, int arg2, int arg3) {
    int rs = arg2,
        rt = arg3,
        rd = arg1,
        rsValue = readRegister(rs),
        rtValue = readRegister(rt);

    writeRegister(rd, rsValue - rtValue);

    return getTypeRWord(0, rs, rt, rd, 0, 0x22);
}

int mips_sw(int arg1, int arg2, int arg3) {
    int base = arg3,
        rt = arg1,
        offset = arg2,
        registerAddress = readRegister(base),
        rtValue = readRegister(rt);

    /* IL FAUT CHECK L'ALIGNEMENT */

    writeMemory(registerAddress + offset, rtValue);

    return getTypeIWord(0x2B, base, rt, offset);
}

int mips_xor(int arg1, int arg2, int arg3) {
    int rs = arg2,
        rt = arg3,
        rd = arg1,
        rsValue = readRegister(rs),
        rtValue = readRegister(rt);

    writeRegister(rd, rsValue ^ rtValue);

    return getTypeRWord(0, rs, rt, rd, 0, 0x26);
}