addi $t0, $zero, 2     # 0: Inicializa contador
addi $t1, $zero, 1     # 1: Decremento
add $t2, $zero, $zero  # 2: Acumulador
sub $t0, $t0, $t1      # 3: Decrementa
add $t2, $t2, $t0      # 4: Soma
beq $t0, $zero, 8      # 5: Se zero, PULA PRA FORA (Linha 8)
j 3                    # 6: Se não zero, VOLTA (Linha 3)
add $v0, $t2, $zero    # 7: (Ignorado/Flush)
sw $v0, 0($sp)         # 8: Salva e ACABA AQUI.