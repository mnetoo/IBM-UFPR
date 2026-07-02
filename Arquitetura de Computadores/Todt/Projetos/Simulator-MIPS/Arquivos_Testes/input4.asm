addi $t0, $zero, 5    # Inicializa $t0 com 5
addi $t1, $zero, 10   # Inicializa $t1 com 10
blt $t0, $t1, 2       # Se $t0 < $t1, pula 2 instruções à frente
addi $t2, $zero, 999  # $t2 = 999 (não deve executar)
j 3                   # Jump para fim (não deve executar)
addi $t3, $zero, 100  # $t3 = 100 (marca que branch foi taken)
addi $t0, $zero, 15   # $t0 = 15
addi $t1, $zero, 8    # $t1 = 8
blt $t0, $t1, 2       # Se $t0 < $t1, pula 2 instruções (não deve pular)
addi $t4, $zero, 200  # $t4 = 200 (marca que branch não foi taken)
addi $t5, $zero, 300  # $t5 = 300
addi $v0, $zero, 1    # Instrução final
