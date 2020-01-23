#include <stdint.h>

#define INS_SPECIAL {0x8, 0x4, 0x7, 0x6, 0x5, 0x2, 0x3, 0xF, 0x23, 0x2B}
#define INS_SPECIAL_POINTERS {&exec_addi, &exec_beq, &exec_bgtz, &exec_blez, &exec_bne, &exec_j, &exec_jal, &exec_lui, &exec_lw, &exec_sw}
#define INS_SPECIAL_NUMBER 10

#define INS_FUNCTION {0x20, 0x24, 0x1A, 0x8, 0x10, 0x12, 0x18, 0, 0x25, 0, 0x2A, 0x22, 0x26}
#define INS_FUNCTION_POINTERS {&exec_add, &exec_and, &exec_div, &exec_jr, &exec_mfhi, &exec_mflo, &exec_mult, &exec_sll, &exec_or, &exec_sll, &exec_slt, &exec_sub, &exec_xor}
#define INS_FUNCTION_NUMBER 13

void exec_add(int32_t code, int interactive);
void exec_addi(int32_t code, int interactive);
void exec_and(int32_t code, int interactive);
void exec_beq(int32_t code, int interactive);
void exec_bgtz(int32_t code, int interactive);
void exec_blez(int32_t code, int interactive);
void exec_bne(int32_t code, int interactive);
void exec_div(int32_t code, int interactive);
void exec_j(int32_t code, int interactive);
void exec_jal(int32_t code, int interactive);
void exec_jr(int32_t code, int interactive);
void exec_lui(int32_t code, int interactive);
void exec_lw(int32_t code, int interactive);
void exec_mfhi(int32_t code, int interactive);
void exec_mflo(int32_t code, int interactive);
void exec_mult(int32_t code, int interactive);
void exec_or(int32_t code, int interactive);
void exec_rotr(int32_t code, int interactive);
void exec_sll(int32_t code, int interactive);
void exec_slt(int32_t code, int interactive);
void exec_srl(int32_t code, int interactive);
void exec_sub(int32_t code, int interactive);
void exec_sw(int32_t code, int interactive);
void exec_xor(int32_t code, int interactive);