ADDI $1,$0,0
ADDI $2,$0,3
ADDI $5,$0,0x1f

#Boucle
ADD $1,$1,$2
BNE $1,$5,-2
ADDI $3,$0,1 #Terminé