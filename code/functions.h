#include <stdint.h>

#define SIZE 8
#define ASCII_TO_HEX_OFFSET 87
#define ASCII_TO_DEC_OFFSET 48
#define INS_SPECIAL_MASK 0xfc000000
#define INS_FUNCTION_MASK 0x0000003f
#define INS_R_MASK 0x00200000

int32_t MIPStoHex(char *ins, int n);

int getTypeRWord(int opcode, int rs, int rt, int rd, int sa, int function);
int getTypeIWord(int opcode, int rs, int rt, int immediate);
int getTypeJWord(int opcode, int target);

void getTypeRArgs(int32_t code, int8_t *rs, int8_t *rt, int8_t *rd, int8_t *sa);
void getTypeIArgs(int32_t code, int8_t *rs, int8_t *rt, int16_t *immediate);
void getTypeJArgs(int32_t code, int32_t *instr_index);

void initProcessor(void);
int executeLine(int32_t instruction);
int executeProgram(void);