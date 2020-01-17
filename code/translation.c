#include <stdio.h>
#include <stdint.h>
#include "functions.h"
#include "registers.h"
#include "memory.h"

#define ADRESS_ALIGNEMENT_MASK 0xfffffffc
#define LOWER_64_MASK 0xffffffff

/* EXCEPTIONS A GERER (Trap) */
/* REGISTRES SPECIAUX A IMPLEMENTER : PC HI LO */
/* GERER LA DIVISION PAR 0 */

int translate_add(int arg1, int arg2, int arg3) {
    int8_t rs = arg2,
           rt = arg3,
           rd = arg1;

    return getTypeRWord(0, rs, rt, rd, 0, 0x20);
}

int translate_addi(int arg1, int arg2, int arg3) {
    int8_t rs = arg2,
           rt = arg1;
    int16_t immediate = arg3;

    return getTypeIWord(0x8, rs, rt, immediate);
}

int translate_and(int arg1, int arg2, int arg3) {
    int8_t rs = arg2,
           rt = arg3,
           rd = arg1;

    return getTypeRWord(0, rs, rt, rd, 0, 0x24);
}

int translate_beq(int arg1, int arg2, int arg3) {
    int8_t rs = arg1,
           rt = arg2;
    int16_t offset = arg3; 

    return getTypeIWord(0x4, rs, rt, offset);
}

int translate_bgtz(int arg1, int arg2, int arg3) {
    int8_t rs = arg1;
    int16_t offset = arg2; 

    return getTypeIWord(0x7, rs, 0, offset);
}

int translate_blez(int arg1, int arg2, int arg3) {
    int8_t rs = arg1;
    int16_t offset = arg2;

    return getTypeIWord(0x6, rs, 0, offset);
}

int translate_bne(int arg1, int arg2, int arg3) {
    int8_t rs = arg1,
           rt = arg2;
    int16_t offset = arg3;

    return getTypeIWord(0x5, rs, rt, offset);
}

int translate_div(int arg1, int arg2, int arg3) {
    int8_t rs = arg1,
           rt = arg2;

    return getTypeRWord(0, rs, rt, 0, 0, 0x1A);
}

int translate_j(int arg1, int arg2, int arg3) {
    int32_t instr_index = arg1;

    return getTypeJWord(0x2, instr_index);
}

int translate_jal(int arg1, int arg2, int arg3) {
    int32_t instr_index = arg1;

    return getTypeJWord(0x3, instr_index);
}

int translate_jr(int arg1, int arg2, int arg3) {
    int8_t rs = arg1;

    // on considère le hint à 0 (comportement par défaut)
    return getTypeRWord(0, rs, 0, 0, 0, 0x8);
}

int translate_lui(int arg1, int arg2, int arg3) {
    int8_t rt = arg1;
    int16_t immediate = arg2;

    return getTypeIWord(0xF, 0, rt, immediate);
}

int translate_lw(int arg1, int arg2, int arg3) {
    int8_t base = arg3,
           rt = arg1;
    int16_t offset = arg2;

    return getTypeIWord(0x23, base, rt, offset);
}

int translate_mfhi(int arg1, int arg2, int arg3) {
    int8_t rd = arg1;

    return getTypeRWord(0, 0, 0, rd, 0, 0x10);
}

int translate_mflo(int arg1, int arg2, int arg3) {
    int8_t rd = arg1;

    return getTypeRWord(0, 0, 0, rd, 0, 0x12);
}

int translate_mult(int arg1, int arg2, int arg3) {
    int8_t rs = arg1,
           rt = arg2;

    return getTypeRWord(0, rs, rt, 0, 0, 0x18);
}

int translate_or(int arg1, int arg2, int arg3) {
    int8_t rs = arg2,
           rt = arg3,
           rd = arg1;

    writeRegister(rd, rsValue | rtValue);

    return getTypeRWord(0, rs, rt, rd, 0, 0x25);
}

int translate_rotr(int arg1, int arg2, int arg3) {
    int8_t rt = arg2,
           rd = arg1,
           sa = arg3;

    return getTypeRWord(0, 0x1, rt, rd, sa, 0x2);
}

int translate_sll(int arg1, int arg2, int arg3) {
    int8_t rt = arg2,
           rd = arg1,
           sa = arg3;

    return getTypeRWord(0, 0, rt, rd, sa, 0x0);
}

int translate_slt(int arg1, int arg2, int arg3) {
    int8_t rs = arg2,
           rt = arg3,
           rd = arg1;

    return getTypeRWord(0, rs, rt, rd, 0, 0x2A);
}

int translate_srl(int arg1, int arg2, int arg3) {
    int8_t rt = arg2,
           rd = arg1,
           sa = arg3;

    return getTypeRWord(0, 0, rt, rd, sa, 0x2);
}

int translate_sub(int arg1, int arg2, int arg3) {
    int8_t rs = arg2,
           rt = arg3,
           rd = arg1;

    return getTypeRWord(0, rs, rt, rd, 0, 0x22);
}

int translate_sw(int arg1, int arg2, int arg3) {
    int8_t base = arg3,
           rt = arg1;
    int16_t offset = arg2;

    return getTypeIWord(0x2B, base, rt, offset);
}

int translate_xor(int arg1, int arg2, int arg3) {
    int8_t rs = arg2,
           rt = arg3,
           rd = arg1;

    return getTypeRWord(0, rs, rt, rd, 0, 0x26);
}