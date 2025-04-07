addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
addi 7
add r1, r0
sub r0, r0

addi 7
addi 3
add r2, r0
sub r0, r0

addi 7
add r3, r0
sub r0, r0

loop:
    st   r3, r1        ;; M[r1] = r3
    addi 1             ;; r0 = r0 + 1
    add r1, r0         ;; r1 = r1 + 1 (próxima posição da memória)
    sub  r2, r0        ;; r2 = r2 - 1 (contador)
    addi 1             ;; r0 = r0 + 1 (incrementa par)
    add r3, r0         ;; incrementar de dois em dois
    sub r0, r0         ;; zera o r0 para a proxima iteração
    brzr r2, end       ;; Se r2 == 0, vai pra label fim
    ji -8              ;; Pula de volta para o início do loop (ajustar com base na posição real)

end: 
    ji end