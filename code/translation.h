#include <stdint.h>

#define INS_NAMES {"ADD", "ADDI", "AND", "BEQ", "BGTZ", "BLEZ", "BNE", "DIV", "J", "JAL", "JR", "LUI", "LW", "MFHI", "MFLO", "MULT", "NOP", "OR", "ROTR", "SLL", "SLT", "SRL", "SUB", "SW", "XOR"}
#define INS_POINTERS {&translate_add, &translate_addi, &translate_and, &translate_beq, &translate_bgtz, &translate_blez, &translate_bne, &translate_div, &translate_j, &translate_jal, &translate_jr, &translate_lui, &translate_lw, &translate_mfhi, &translate_mflo, &translate_mult, &translate_sll, &translate_or, &translate_rotr, &translate_sll, &translate_slt, &translate_srl, &translate_sub, &translate_sw, &translate_xor}
#define INS_NUMBER 25

int translate_add(int arg1, int arg2, int arg3);
int translate_addi(int arg1, int arg2, int arg3);
int translate_and(int arg1, int arg2, int arg3);
int translate_beq(int arg1, int arg2, int arg3);
int translate_bgtz(int arg1, int arg2, int arg3);
int translate_blez(int arg1, int arg2, int arg3);
int translate_bne(int arg1, int arg2, int arg3);
int translate_div(int arg1, int arg2, int arg3);
int translate_j(int arg1, int arg2, int arg3);
int translate_jal(int arg1, int arg2, int arg3);
int translate_jr(int arg1, int arg2, int arg3);
int translate_lui(int arg1, int arg2, int arg3);
int translate_lw(int arg1, int arg2, int arg3);
int translate_mfhi(int arg1, int arg2, int arg3);
int translate_mflo(int arg1, int arg2, int arg3);
int translate_mult(int arg1, int arg2, int arg3);
int translate_or(int arg1, int arg2, int arg3);
int translate_rotr(int arg1, int arg2, int arg3);
int translate_sll(int arg1, int arg2, int arg3);
int translate_slt(int arg1, int arg2, int arg3);
int translate_srl(int arg1, int arg2, int arg3);
int translate_sub(int arg1, int arg2, int arg3);
int translate_sw(int arg1, int arg2, int arg3);
int translate_xor(int arg1, int arg2, int arg3);