#define INS_NAMES {"ADD", "ADDI", "AND", "BEQ", "BGTZ", "BLEZ", "BNE", "DIV", "J", "JAL", "JR", "LUI", "LW", "MFHI", "MFLO", "MULT", "NOP", "OR", "ROTR", "SLL", "SLT", "SRL", "SUB", "SW", "XOR"}
#define INS_POINTERS {&mips_add, &mips_addi, &mips_and, &mips_beq, &mips_bgtz, &mips_blez, &mips_bne, &mips_div, &mips_j, &mips_jal, &mips_jr, &mips_lui, &mips_lw, &mips_mfhi, &mips_mflo, &mips_mult, &mips_nop, &mips_or, &mips_rotr, &mips_sll, &mips_slt, &mips_srl, &mips_sub, &mips_sw, &mips_xor}
#define INS_NUMBER 25

int mips_add(int arg1, int arg2, int arg3);
int mips_addi(int arg1, int arg2, int arg3);
int mips_and(int arg1, int arg2, int arg3);
int mips_beq(int arg1, int arg2, int arg3);
int mips_bgtz(int arg1, int arg2, int arg3);
int mips_blez(int arg1, int arg2, int arg3);
int mips_bne(int arg1, int arg2, int arg3);
int mips_div(int arg1, int arg2, int arg3);
int mips_j(int arg1, int arg2, int arg3);
int mips_jal(int arg1, int arg2, int arg3);
int mips_jr(int arg1, int arg2, int arg3);
int mips_lui(int arg1, int arg2, int arg3);
int mips_lw(int arg1, int arg2, int arg3);
int mips_mfhi(int arg1, int arg2, int arg3);
int mips_mflo(int arg1, int arg2, int arg3);
int mips_mult(int arg1, int arg2, int arg3);
int mips_nop(int arg1, int arg2, int arg3);
int mips_or(int arg1, int arg2, int arg3);
int mips_rotr(int arg1, int arg2, int arg3);
int mips_sll(int arg1, int arg2, int arg3);
int mips_slt(int arg1, int arg2, int arg3);
int mips_srl(int arg1, int arg2, int arg3);
int mips_sub(int arg1, int arg2, int arg3);
int mips_sw(int arg1, int arg2, int arg3);
int mips_xor(int arg1, int arg2, int arg3);