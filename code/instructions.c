#include "functions.h"
#include "registers.h"

int mips_add(int arg1, int arg2, int arg3) {
    int rs = arg2,
        rt = arg3,
        rd = arg1,
        rsValue = readRegister(rs),
        rtValue = readRegister(rt);
    writeRegister(rd, rsValue + rtValue);
    return getTypeRWord(0, rs, rt, rd, 0, 0x20);
}

int mips_addi(int arg1, int arg2, int arg3) {
    int rs = arg2,
        rt = arg1,
        immediate = arg3;

    return getTypeIWord(0x8, rs, rt, immediate);
}

int mips_and(int arg1, int arg2, int arg3) {
    int rs = arg2,
        rt = arg3,
        rd = arg1;

    return getTypeRWord(0, rs, rt, rd, 0, 0x24);
}

int mips_beq(int arg1, int arg2, int arg3) {
    int rs = arg1,
        rt = arg2,
        offset = arg3;

    return getTypeIWord(0x4, rs, rt, offset);
}

int mips_bgtz(int arg1, int arg2, int arg3) {
    int rs = arg1,
        offset = arg2;

    return getTypeIWord(0x7, rs, 0, offset);
}

int mips_blez(int arg1, int arg2, int arg3) {
    int rs = arg1,
        offset = arg2;

    return getTypeIWord(0x6, rs, 0, offset);
}

int mips_bne(int arg1, int arg2, int arg3) {
    int rs = arg1,
        rt = arg2,
        offset = arg3;

    return getTypeIWord(0x5, rs, rt, offset);
}

int mips_div(int arg1, int arg2, int arg3) {
    int rs = arg1,
        rt = arg2;

    return getTypeRWord(0, rs, rt, 0, 0, 0x1A);
}

int mips_j(int arg1, int arg2, int arg3) {
    int instr_index = arg1;

    return getTypeJWord(0x2, instr_index);
}

int mips_jal(int arg1, int arg2, int arg3) {
    int instr_index = arg1;

    return getTypeJWord(0x3, instr_index);
}

int mips_jr(int arg1, int arg2, int arg3) {
    int rs = arg1;

    // on considère le hint à 0 (comportement par défaut)
    return getTypeRWord(0, rs, 0, 0, 0, 0x8);
}

int mips_lui(int arg1, int arg2, int arg3) {
    int rt = arg1,
        immediate = arg2;

    return getTypeIWord(0xF, 0, rt, immediate);
}

int mips_lw(int arg1, int arg2, int arg3) {
    int base = arg3,
        rt = arg1,
        offset = arg2;

    return getTypeIWord(0x23, base, rt, offset);
}

int mips_mfhi(int arg1, int arg2, int arg3) {
    int rd = arg1;

    return getTypeRWord(0, 0, 0, rd, 0, 0x10);
}

int mips_mflo(int arg1, int arg2, int arg3) {
    int rd = arg1;

    return getTypeRWord(0, 0, 0, rd, 0, 0x12);
}

int mips_mult(int arg1, int arg2, int arg3) {
    int rs = arg1,
        rt = arg2;

    return getTypeRWord(0, rs, rt, 0, 0, 0x18);
}

int mips_nop(int arg1, int arg2, int arg3) {
    return getTypeRWord(0, 0, 0, 0, 0, 0);
}

int mips_or(int arg1, int arg2, int arg3) {
    int rs = arg2,
        rt = arg3,
        rd = arg1;

    return getTypeRWord(0, rs, rt, rd, 0, 0x25);
}

int mips_rotr(int arg1, int arg2, int arg3) {
    int rt = arg2,
        rd = arg1,
        sa = arg3;

    return getTypeRWord(0, 0x1, rt, rd, sa, 0x2);
}

int mips_sll(int arg1, int arg2, int arg3) {
    int rt = arg2,
        rd = arg1,
        sa = arg3;

    return getTypeRWord(0, 0, rt, rd, sa, 0x0);
}

int mips_slt(int arg1, int arg2, int arg3) {
    int rs = arg2,
        rt = arg3,
        rd = arg1;

    return getTypeRWord(0, rs, rt, rd, 0, 0x2A);
}

int mips_srl(int arg1, int arg2, int arg3) {
    int rt = arg2,
        rd = arg1,
        sa = arg3;

    return getTypeRWord(0, 0, rt, rd, sa, 0x2);
}

int mips_sub(int arg1, int arg2, int arg3) {
    int rs = arg2,
        rt = arg3,
        rd = arg1;

    return getTypeRWord(0, rs, rt, rd, 0, 0x22);
}

int mips_sw(int arg1, int arg2, int arg3) {
    int base = arg3,
        rt = arg1,
        offset = arg2;

    return getTypeIWord(0x2B, base, rt, offset);
}

int mips_xor(int arg1, int arg2, int arg3) {
    int rs = arg2,
        rt = arg3,
        rd = arg1;

    return getTypeRWord(0, rs, rt, rd, 0, 0x26);
}