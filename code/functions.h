#define SIZE 8
#define ASCII_TO_HEX_OFFSET 87
#define ASCII_TO_DEC_OFFSET 48
#define INS_SPECIAL_MASK 0xfc000000
#define INS_FUNCTION_MASK 0x0000003f
#define INS_R_MASK 0x00200000

int MIPStoHex(char *ins, int n, char hex[SIZE]);

int getTypeRWord(int opcode, int rs, int rt, int rd, int sa, int function);
int getTypeIWord(int opcode, int rs, int rt, int immediate);
int getTypeJWord(int opcode, int target);