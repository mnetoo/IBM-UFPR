;; Programa Assembly rEDUX-V para somar vetores A e B, armazenando o resultado em r

;; Início do código
        addi    r0, 0      ;; Zera r0 (vai armazenar o índice i)
        addi    r1, 10     ;; r1 = 10 (limite do loop)
        addi    r2, A      ;; r2 aponta para A
        addi    r3, B      ;; r3 aponta para B
        addi    r4, r      ;; r4 aponta para r

loop:   brzr    r0, fim    ;; Se i >= 10, sai do loop
        ld      r5, r2     ;; r5 = A[i]
        ld      r6, r3     ;; r6 = B[i]
        add     r7, r5, r6 ;; r7 = A[i] + B[i]
        st      r7, r4     ;; r[i] = r7

        addi    r2, 1      ;; Avança ponteiro de A
        addi    r3, 1      ;; Avança ponteiro de B
        addi    r4, 1      ;; Avança ponteiro de r
        addi    r0, 1      ;; i++
        ji      loop       ;; Volta para o início do loop

fim:    ji      fim        ;; Loop infinito ao terminar

;; Dados (na memória, logo após o código)
A:      .byte   0, 2, 4, 6, 8, 10, 12, 14, 16, 18
B:      .byte   1, 3, 5, 7, 9, 11, 13, 15, 17, 19
r:      .byte   0, 0, 0, 0, 0, 0, 0, 0, 0, 0