;;==================================== INICIALIZA VETOR A ====================================

addi 7
slr r0, r0
add r1, r0  ;; memoria 128
sub r0, r0

addi 7
addi 3
add r2, r0  ;; contador 10
sub r0, r0

addi 1
add r3, r0
sub r0, r0  ;; 1 para iterações

loop_A:
    st r0, r1          ;;M[r1] = valor atual (par)
    addi 2             ;;próximo número par
    add r1, r3         ;;próximo endereço de memória
    sub r2, r3         ;;decrementa o contador
    brzr r2, zerar       ;;se contador == 0, fim
    ji loop_A              ;;volta para o início do loop

zerar:
    sub r0, r0
    sub r1, r1
    sub r2, r2
    sub r3, r3

;;==================================== INICIALIZA VETOR B ====================================