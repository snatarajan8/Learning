!Shyam Natarajan
!903047415
!A3

ADD $a0, $zero, $zero
ADDI $a1, $zero, 10
add:
ADDI $a0, $a0, 1
BNE $a0, $a1, add
ADD $a2, $zero, $zero
memadd:
ADDI $a2, $a2, 1
STR $a2, 0($zero)
LDR $s0, 0($zero)
BNE $s0, $a1, memadd
HALT
