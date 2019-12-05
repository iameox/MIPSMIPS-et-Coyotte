#define SIZE 8
#define ASCII_TO_HEX_OFFSET 87
#define ASCII_TO_DEC_OFFSET 48

int MIPStoHex(char *ins, int n, char hex[SIZE]);

int getTypeRWord(int opcode, int rs, int rt, int rd, int sa, int function);
int getTypeIWord(int opcode, int rs, int rt, int immediate);
int getTypeJWord(int opcode, int target);