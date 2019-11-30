#define SIZE 8
#define INS_NAMES {"ADD", "ADDI", "AND", "BEQ", "BGTZ", "BLEZ", "BNE", "DIV", "J", "JAL", "JR", "LUI", "LW", "MFHI", "MFLO", "MULT", "NOP", "OR", "ROTR", "SLL", "SLT", "SRL", "SUB", "SW", "XOR"}
#define INS_POINTERS {&mips_add, &mips_addi, &mips_and, &mips_beq, &mips_bgtz, &mips_blez, &mips_bne, &mips_div, &mips_j, &mips_jal, &mips_jr, &mips_lui, &mips_lw, &mips_mfhi, &mips_mflo, &mips_mult, &mips_nop, &mips_or, &mips_rotr, &mips_sll, &mips_slt, &mips_srl, &mips_sub, &mips_sw, &mips_xor}
#define INS_NUMBER 25
#define ASCII_TO_HEX_OFFSET 87
#define ASCII_TO_DEC_OFFSET 48

int MIPStoHex(char *ins, int n, char hex[SIZE]);

int papattesdechatTypeR(int opcode, int rs, int rt, int rd, int sa, int function);
int papattesdechatTypeI(int opcode, int rs, int rt, int immediate);
int papattesdechatTypeJ(int opcode, int target);