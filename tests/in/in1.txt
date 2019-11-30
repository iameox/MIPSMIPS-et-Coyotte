SRL $0,$0,32 #Init le registre 0 à 0
ADDI $1,$0,12 #Init r1 a 12
ADDI $3,$0,5
SW $1,5($0) #Test d'écriture en immédiat dans la mémoire
ADDI $2,$0,1 #Init du pointeur mémoire


SW $1,10($2) #On store le contenu de r1 dans la mémoire a l'adresse 20 + (r2)
ADDI $1,$1,1
ADDI $2,$2,1
BNE $2, $3,-4
