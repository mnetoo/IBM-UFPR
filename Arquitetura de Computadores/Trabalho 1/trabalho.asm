; r0 = 1
; r1 = endereço do fim do loop
; r2 = 19
; r3 = endereço de B[9] = 127

;   CARREGANDO FINAL DO VETOR B
addi 7
slr r0, r0
add r3, r0 ;r3 = 128
sub r0, r0
addi 1
sub r3, r0 ;r3 = 127
sub r0, r0

;   CARREGANDO ULTIMO VALOR DO VETOR B
addi 7
addi 3
addi 7
addi 2
add r2, r0  ; r2 = 19

;   CARREGANDO O FIM DO VETOR PARA SALTO APÓS LOOP
addi 3
add r1, r0  ; r1 = 22 endereço FIM_VETOR_B

;   AUXILIAR
sub r0, r0
addi 1

;   LOOP VETOR B
VETOR_B:
    st r2, r3   ; M[r3] = r2
    sub r2, r0  ; r2 - 1
    brzr r2, r1     ; if r2 = 0, goto r1 = fim do loop
    sub r2, r0  ; r2 - 1
    sub r3, r0  ; r3 -1
    ji VETOR_B

FIM_VETOR_B:
    sub r3, r0  ; r3 = (127 - 10) - 1 = 117 - CALCULAR O FIM DO VETOR A
    
    ;   CARREGANDO O ULTIMO VALOR DO VETOR A
    addi 7
    addi 3
    addi 7
    add r2, r0  ; r2 = 18

    ;   CARREGANDO O FIM DO VETOR PARA SALTO APÓS LOOP
    addi -3
    add r1, r0  ; r1 = 37 endereço FIM_VETOR_A

    sub r0, r0
    addi 1

;   LOOP VETOR A
VETOR_A:
    st r2, r3   ; M[r3] = r2
    sub r2, r0  ; r2 - 1
    sub r2, r0  ; r2 - 1
    brzr r2, r1     ; if r2 = 0, goto r1 = fim do loop
    sub r3, r0  ; r3 -1
    ji VETOR_A

FIM_VETOR_A:
    sub r0, r0

    ;   CARREGANDO O INICIO DE R
    addi 7
    slr r0, r0
    sub r3, r3
    add r3, r0
    sub r0, r0
    ;addi 1
    add r3, r0  ; r3 = 129

    sub r0, r0
    sub r1, r1
    sub r2, r2

    ;   CARREGANDO O DO INICIO DE A
    addi 7
    slr r0, r0
    add r1, r0
    sub r0, r0
    addi 7
    addi 3
    sub r1, r0  ; r1 = 118
    sub r1, r0  ; r1 = 108

VETOR_SOMA:
    ;   r0 = 10
    sub r0, r0
    addi 7
    addi 3

    ld r2, r1   ; A[i] - conteudo de A
    add r0, r1  ; add(B) - endereço de b
    ld r0, r0   ; B[i] - conteudo de B
    add r2, r0  ; A[i] + B[i] - soma
    st r2, r3   ; R[i] = soma

    sub r0, r0

    ;   ENDEREÇO +1
    addi 1
    add r1, r0
    add r3, r0

    ;   CARREGA PARA FAZER A VERIFICAÇÃO
    sub r0, r0
    addi 7
    addi 7
    addi 7
    addi 7
    addi 7
    addi 2  ; r0 = 37
    
    ;   FAZ A VERIFICAÇÃO DO BRZR
    sub r2, r0
    not r2, r2
    addi 3  
    addi 7
    addi 3;
    addi 5  ;r0 = 47 endereço para voltar
    brzr r2, r0
    
ebreak
