addi 7       ;; r0 = 7  (somamos para construir 40)
addi 7       ;; r0 = 14
addi 7       ;; r0 = 21
addi 7       ;; r0 = 28
addi 7       ;; r0 = 35
addi 5       ;; r0 = 40
add r1, r0   ;; r1 = 40 (agora temos o endereço inicial)
sub r0, r0   ;; r0 = 0 (zera r0 para armazenar valores pares)

addi 1       ;; r0 = 1
add r3, r0   ;; r3 = 1 (r3 será sempre 1 para decrementar r2)
sub r0, r0   ;; r0 = 0

sub r2, r2   ;; r2 = 0 (inicializa contador)
addi 7       ;; r0 = 7
addi 3       ;; r0 = 10 (contador do loop)
add r2, r0   ;; r2 = 10
sub r0, r0   ;; r0 = 0 (zera r0 para os números pares)

loop:
st r0, r1    ;; Armazena r0 na posição de memória r1 - posiçaõ 40 = r0
addi 1       ;; r0 = 1 (usar r0 temporariamente)
add r1, r0   ;; r1 = r1 + 1 (avança para o próximo endereço)
sub r0, r0   ;; r0 = 0
addi 2       ;; r0 = r0 + 2 (incrementa corretamente o valor par)
add r0, r0   ;; Garante que o incremento seja acumulativo
sub r2, r3   ;; r2 = r2 - 1 (decrementa contador)
not r0, r2
brzr r0, r3  ;; Se r2 == 0, sai do loop
ji loop      ;; Volta para repetir o loop