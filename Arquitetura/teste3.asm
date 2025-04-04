;; ---- Inicialização do Endereço Base (r1 = 40) ----
addi 7       ;; r0 = 7
addi 7       ;; r0 = 14
addi 7       ;; r0 = 21
addi 7       ;; r0 = 28
addi 7       ;; r0 = 35
addi 5       ;; r0 = 40
add r1, r0   ;; r1 = 40 (endereço inicial)

;; ---- Contador (r3 = 10) ----
sub r0, r0   ;; r0 = 0
addi 5
addi 5
add r3, r0   ;; r3 = 10 (10 iterações)
sub r0, r0   ;; r0 = 0

addi -1
ld r2, r0
sub r0, r0

;; ---- Loop de Escrita ----
loop:
    st r2, r1   ;; M[r1] = r2 (armazena número par)
    
    ;; Incrementa endereço (r1 += 1)
    sub r0, r0  ;; r0 = 0
    addi 1      ;; r0 = 1
    add r1, r0  ;; r1 += 1
    
    ;; Incrementa valor par (r2 += 2)
    sub r0, r0  ;; r0 = 0
    addi 2      ;; r0 = 2
    add r2, r0  ;; r2 += 2
    
    ;; Decrementa contador (r3 -= 1)
    sub r0, r0  ;; r0 = 0
    addi 1      ;; r0 = 1
    sub r3, r0  ;; r3 -= 1
    
    ;; Verifica fim do loop
    brzr r3, end
    ji loop

;; ---- Fim do Programa ----
end:
    ji end      ;; Loop infinito (halt)