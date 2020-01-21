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

void exec_add(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

    writeRegister(rd, rsValue + rtValue);
}

void exec_addi(int32_t code) {
    int8_t rs, rt;
    int16_t immediate;
    getTypeIArgs(code, &rs, &rt, &immediate);

    int32_t rsValue = readRegister(rs);

    printf("ADDI %d %d %d\n", rs, rt, immediate);

    writeRegister(rt, rsValue + immediate);
}

void exec_and(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

    writeRegister(rd, rsValue & rtValue);
}

void exec_beq(int32_t code) {
    int8_t rs, rt;
    int16_t offset;
    getTypeIArgs(code, &rs, &rt, &offset);

    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

    if (rsValue == rtValue) {
        PC += offset << 2; /* Il faut décaler de 2 */
    }
}

void exec_bgtz(int32_t code) {
    int8_t rs, rt;
    int16_t offset;
    getTypeIArgs(code, &rs, &rt, &offset);

    int32_t rsValue = readRegister(rs);

    if (rsValue > 0) {
        PC += offset << 2; /* Il faut décaler de 2 */
    }
}

void exec_blez(int32_t code) {
    int8_t rs, rt;
    int16_t offset;
    getTypeIArgs(code, &rs, &rt, &offset);

    int32_t rsValue = readRegister(rs);

    if (rsValue <= 0) {
        PC += offset << 2; /* Il faut décaler de 2 */
    }
}

void exec_bne(int32_t code) {
    int8_t rs, rt;
    int16_t offset;
    getTypeIArgs(code, &rs, &rt, &offset);
    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);


    if (rsValue != rtValue) {
        PC += offset << 2; /* Il faut décaler de 2 */
    }
}

void exec_div(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

    if(rtValue != 0){
        HI = rsValue/rtValue;
        LO = rsValue%rtValue;
    } else {
        printf("ERREUR : DIVISION PAR 0\n");
    }
}

void exec_j(int32_t code) {
    int32_t instr_index;
    getTypeJArgs(code, &instr_index);
    
    PC = instr_index << 4; /* Il faut décaler de 4 */
}

void exec_jal(int32_t code) {
    int32_t instr_index;
    getTypeJArgs(code, &instr_index);

    int32_t returnAdressLink = PC + 4;
    PC = instr_index << 2; /* Il faut décaler de 2 */

    writeRegister(31, returnAdressLink);
}

void exec_jr(int32_t code) {
    int8_t rs, rt, rd, hint;
    getTypeRArgs(code, &rs, &rt, &rd, &hint);

    int32_t rsValue = readRegister(rs);

    rsValue = rsValue & ADRESS_ALIGNEMENT_MASK; /* On force les 2 LSB à 0 pour que l'adresse soit alignée */
    
    PC = rsValue;
}

void exec_lui(int32_t code) {
    int8_t rs, rt;
    int16_t immediate;
    getTypeIArgs(code, &rs, &rt, &immediate);

    writeRegister(rt, immediate << 16); /* Que les 2 octets de poids fort */
}

void exec_lw(int32_t code) {
    int8_t base, rt;
    int16_t offset;
    getTypeIArgs(code, &base, &rt, &offset);

    int32_t registerAddress = readRegister(base);
    int32_t value = readMemory(&DATA_MEMORY, registerAddress + offset);

    /* IL FAUT CHECK L'ALIGNEMENT */

    writeRegister(rt, value);
}

void exec_mfhi(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    writeRegister(rd, HI);
}

void exec_mflo(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    writeRegister(rd, LO);
}

void exec_mult(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);
    int64_t result = rsValue * rtValue;

    HI = result>>32;
    LO = result & LOWER_64_MASK; 
}

void exec_or(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

    writeRegister(rd, rsValue | rtValue);
}

void exec_rotr(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    int32_t rtValue = readRegister(rt);

    writeRegister(rd, (rtValue >> sa) + (rtValue << (32-sa)));
}

void exec_sll(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    int32_t rtValue = readRegister(rt);

    writeRegister(rd, rtValue << sa);
}

void exec_slt(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

    writeRegister(rd, rsValue < rtValue);
}

void exec_srl(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    int32_t rtValue = readRegister(rt);

    writeRegister(rd, rtValue >> sa);
}

void exec_sub(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

    writeRegister(rd, rsValue - rtValue);
}

void exec_sw(int32_t code) {
    int8_t base, rt;
    int16_t offset;
    getTypeIArgs(code, &base, &rt, &offset);

    int32_t registerAddress = readRegister(base),
            rtValue = readRegister(rt);

    /* IL FAUT CHECK L'ALIGNEMENT */

    writeMemory(&DATA_MEMORY, registerAddress + offset, rtValue);
}

void exec_xor(int32_t code) {
    int8_t rs, rt, rd, sa;
    getTypeRArgs(code, &rs, &rt, &rd, &sa);

    int32_t rsValue = readRegister(rs),
            rtValue = readRegister(rt);

    writeRegister(rd, rsValue ^ rtValue);
}