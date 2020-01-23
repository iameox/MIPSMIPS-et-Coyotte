#include <stdio.h>
#include <stdint.h>
#include "functions.h"
#include "registers.h"
#include "memory.h"

#define ADRESS_ALIGNEMENT_MASK 0xfffffffc
#define LOWER_64_MASK 0xffffffff

/* Ce fichier reprend simplement les algorithmes donnés en annexe */

void exec_add(int32_t code) {
    int8_t rs, rt, rd, sa;
    int32_t rsValue, rtValue;

    getTypeRArgs(code, &rs, &rt, &rd, &sa);
    rsValue = readRegister(rs);
    rtValue = readRegister(rt);

    writeRegister(rd, rsValue + rtValue);
}

void exec_addi(int32_t code, int interactive) {
    int8_t rs, rt;
    int16_t immediate;
    int32_t rsValue;

    getTypeIArgs(code, &rs, &rt, &immediate);
    rsValue = readRegister(rs);

    writeRegister(rt, rsValue + immediate);
}

void exec_and(int32_t code) {
    int8_t rs, rt, rd, sa;
    int32_t rsValue, rtValue;

    getTypeRArgs(code, &rs, &rt, &rd, &sa);
    rsValue = readRegister(rs);
    rtValue = readRegister(rt);

    writeRegister(rd, rsValue & rtValue);
}

void exec_beq(int32_t code, int interactive) {
    int8_t rs, rt;
    int16_t offset;
    int32_t rsValue, rtValue;

    if (interactive) {
        printf("ERREUR : instruction inutilisable en mode interactif.\n");
        
    } else {
        getTypeIArgs(code, &rs, &rt, &offset);
        rsValue = readRegister(rs);
        rtValue = readRegister(rt);

        if (rsValue == rtValue) {
            PC += offset << 2; /* Il faut décaler de 2 */
        }
    }
}

void exec_bgtz(int32_t code, int interactive) {
    int8_t rs, rt;
    int16_t offset;
    int32_t rsValue;

    if (interactive) {
        printf("ERREUR : instruction inutilisable en mode interactif.\n");
        
    } else {
        getTypeIArgs(code, &rs, &rt, &offset);
        rsValue = readRegister(rs);
    
        if (rsValue > 0) {
            PC += offset << 2; /* Il faut décaler de 2 */
        }
    }
}   

void exec_blez(int32_t code, int interactive) {
    int8_t rs, rt;
    int16_t offset;
    int32_t rsValue;

    if (interactive) {
        printf("ERREUR : instruction inutilisable en mode interactif.\n");
        
    } else {
        getTypeIArgs(code, &rs, &rt, &offset);
        rsValue = readRegister(rs);
    
        if (rsValue <= 0) {
            PC += offset << 2; /* Il faut décaler de 2 */
        }
    }
}

void exec_bne(int32_t code, int interactive) {
    int8_t rs, rt;
    int16_t offset;
    int32_t rsValue, rtValue;

    if (interactive) {
        printf("ERREUR : instruction inutilisable en mode interactif.\n");
        
    } else {
        getTypeIArgs(code, &rs, &rt, &offset);
        rsValue = readRegister(rs);
        rtValue = readRegister(rt);
    
        if (rsValue != rtValue) {
            PC += offset << 2; /* Il faut décaler de 2 */
        }
    }
}

void exec_div(int32_t code) {
    int8_t rs, rt, rd, sa;
    int32_t rsValue, rtValue;

    getTypeRArgs(code, &rs, &rt, &rd, &sa);
    rsValue = readRegister(rs);
    rtValue = readRegister(rt);

    if (rtValue != 0) {
        HI = rsValue/rtValue;
        LO = rsValue%rtValue;

    } else {
        printf("ERREUR : DIVISION PAR 0\n");
    }
}

void exec_j(int32_t code, int interactive) {
    int32_t instr_index;

    if (interactive) {
        printf("ERREUR : instruction inutilisable en mode interactif.\n");
        
    } else {
        getTypeJArgs(code, &instr_index);
        PC = instr_index << 4; /* Il faut décaler de 4 */
    }
}

void exec_jal(int32_t code, int interactive) {
    int32_t instr_index;

    if (interactive) {
        printf("ERREUR : instruction inutilisable en mode interactif.\n");
        
    } else {
        getTypeJArgs(code, &instr_index);
        PC = instr_index << 2; /* Il faut décaler de 2 */

        writeRegister(31, PC + 4);
    }
}

void exec_jr(int32_t code, int interactive) {
    int8_t rs, rt, rd, hint;
    int32_t rsValue;

    if (interactive) {
        printf("ERREUR : instruction inutilisable en mode interactif.\n");

    } else {
        getTypeRArgs(code, &rs, &rt, &rd, &hint);
        rsValue = readRegister(rs) & ADRESS_ALIGNEMENT_MASK; /* On force les 2 LSB à 0 pour que l'adresse soit alignée */
    
        PC = rsValue;
    }
}

void exec_lui(int32_t code, int interactive) {
    int8_t rs, rt;
    int16_t immediate;

    getTypeIArgs(code, &rs, &rt, &immediate);

    writeRegister(rt, immediate << 16); /* Que les 2 octets de poids fort */
}

void exec_lw(int32_t code, int interactive) {
    int8_t base, rt;
    int16_t offset;
    int32_t registerAddress, value;

    getTypeIArgs(code, &base, &rt, &offset);
    registerAddress = readRegister(base);
    value = readMemory(&DATA_MEMORY, registerAddress + offset);

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
    int32_t rsValue, rtValue;
    int64_t result;

    getTypeRArgs(code, &rs, &rt, &rd, &sa);
    rsValue = readRegister(rs);
    rtValue = readRegister(rt);
    result = rsValue * rtValue;

    HI = result>>32;
    LO = result & LOWER_64_MASK; 
}

void exec_or(int32_t code) {
    int8_t rs, rt, rd, sa;
    int32_t rsValue, rtValue;

    getTypeRArgs(code, &rs, &rt, &rd, &sa);
    rsValue = readRegister(rs);
    rtValue = readRegister(rt);

    writeRegister(rd, rsValue | rtValue);
}

void exec_rotr(int32_t code) {
    int8_t rs, rt, rd, sa;
    int32_t rtValue;

    getTypeRArgs(code, &rs, &rt, &rd, &sa);
    rtValue = readRegister(rt);

    writeRegister(rd, (rtValue >> sa) + (rtValue << (32-sa)));
}

void exec_sll(int32_t code) {
    int8_t rs, rt, rd, sa;
    int32_t rtValue;

    getTypeRArgs(code, &rs, &rt, &rd, &sa);
    rtValue = readRegister(rt);

    writeRegister(rd, rtValue << sa);
}

void exec_slt(int32_t code) {
    int8_t rs, rt, rd, sa;
    int32_t rsValue, rtValue;

    getTypeRArgs(code, &rs, &rt, &rd, &sa);
    rsValue = readRegister(rs);
    rtValue = readRegister(rt);

    writeRegister(rd, rsValue < rtValue);
}

void exec_srl(int32_t code) {
    int8_t rs, rt, rd, sa;
    int32_t rtValue;

    getTypeRArgs(code, &rs, &rt, &rd, &sa);
    rtValue = readRegister(rt);

    writeRegister(rd, rtValue >> sa);
}

void exec_sub(int32_t code) {
    int8_t rs, rt, rd, sa;
    int32_t rsValue, rtValue;

    getTypeRArgs(code, &rs, &rt, &rd, &sa);
    rsValue = readRegister(rs);
    rtValue = readRegister(rt);

    writeRegister(rd, rsValue - rtValue);
}

void exec_sw(int32_t code, int interactive) {
    int8_t base, rt;
    int16_t offset;
    int32_t registerAddress, rtValue;

    getTypeIArgs(code, &base, &rt, &offset);
    registerAddress = readRegister(base);
    rtValue = readRegister(rt);

    writeMemory(&DATA_MEMORY, registerAddress + offset, rtValue);
}

void exec_xor(int32_t code) {
    int8_t rs, rt, rd, sa;
    int32_t rsValue, rtValue;

    getTypeRArgs(code, &rs, &rt, &rd, &sa);
    rsValue = readRegister(rs),
    rtValue = readRegister(rt);

    writeRegister(rd, rsValue ^ rtValue);
}