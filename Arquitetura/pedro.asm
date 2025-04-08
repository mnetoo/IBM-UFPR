; end -1(ff | 255)  = end A
; end -2(fe | 254) = end B
; end -3(fd | 253) = end R
; end -4(fc | 252) = loop
; end -5(fb | 251) = fim_loop
; end -6(fa | 250) = A[9]
; end -15(f1 | 241) = A[0]
; end -16(f0 | 240) = B[9]
; end -25(e7 | 231)= B[0]
; end -26(e6 | 230) = R[9]
; end -35(dd | 221) = R[0]

        addi 7
        addi 7
        addi 4
        add r3, r0 ; r3 = 18
        sub r0, r0

        addi 7
        addi 7
        addi 7
        addi 3
        add r2, r0 ; r2 = fim_A = 24
        sub r0, r0

        addi -6 ; r0 = adr(A[9])
        add r1, r0 ; r1 = adr(A[9])
        sub r0, r0
        addi -1 ; r0 = -1(ff)
        st r1, r0 ; end (r0) = adr (A[9]) ||||||||||
        sub r0, r0

        addi 1; r0 = 1

;r3 = 18
;r2 = fim_A(6)
;r1 = adr(A[9])
;r0 = 1

A:      
        st r3, r1 ; M(adr(A[9])) = 18
        brzr r3, r2 ; se 18 = 0 pula pra fim_A
        sub r3, r0
        sub r3, r0 ; r3 = 18 - 2 = 16
        sub r1, r0 ; r1 = adr(A[8])
        ji A
fim_A:
        ebreak
        ;r3 = 0
        ;r2 = 24
        ;r1 = f1
        ;r0 = 1

        sub r1, r0 ; r1 tinha f1 ... r1 = f0(adr(B[9]))
        addi -3 ; r0 = -2(fe)
        st r1, r0 ; end (r0) = adr (B[9]) ||||||||||

        addi 7
        addi 7
        addi 7
        add r3, r0 ; r3 = 19
        sub r0, r0

        ;r2 = 24
        addi 7
        addi 7
        addi 7 ;r0 = 21
        add r2, r0 ; r2 = 45


        sub r0, r0
        addi 1

        
;r3 = 19
;r2 = fim_B(6)
;r1 = adr(B[9])
;r0 = 1
B: 
        st r3, r1 ; M(adr(B[9])) = 19
        sub r3, r0 ; 19 - 1
        brzr r3, r2 ; se 18 = 0 pula pra fim_B
        sub r3, r0 ; r3 = 18 - 1 = 17
        sub r1, r0 ; r1 = adr(B[8])
        ji B
fim_B:
        ;r3 = 0
        ;r2 = 2d (45)
        ;r1 = e7
        ;r0 = 1
        ebreak

        sub r1, r0 ; r1 tinha e7 ... r1 = f0(adr(R[9]))
        addi -4 ; r0 = -3(fd)
        st r1, r0 ; end (r0) = adr (B[9]) ||||||||||

        addi 7
        addi 6; r0 = 9
        add r3, r0 ; r3 = 9

        ; r2 = 45

        addi 7; r0 = 16
        addi 2; r0 = 18
        add r2, r0 ; r2 = 45 + 18 = 64
        sub r0, r0; r0 = r0
        
        ebreak

;r3 = 9
;r2 = fim_R
;r1 = adr(R[9])
;r0 = 0
R: 
        st r0, r1 ; M(adr(R[9])) = 0
        brzr r3, r2 ; se 9 = 0 pula pra fim_R
        addi 1 ; r0 = 1
        sub r1, r0; r1 = adr(R[8])
        sub r3, r0; r3 = 9 - 1 = 8
        sub r0, r0 ; r0 = 0
        ji R
fim_R:
        ebreak
        ; r3 = 0
        ; r2 = 40(64)
        ; r1 = dd
        ; r0 = 0

        addi 7
        addi 7
        addi 2
        add r2, r0 ; 64 + 16
        sub r0, r0 ; r0 = 0
        addi -4
        st r2, r0 ; M[-4] = 80(loop) 

        addi 7
        addi 7
        addi 7 ; r0 = 17
        addi 5 ; r0 = 22
        ;addi 1 ; r0 = 24
        add r2, r0 ; 80 + 22 = fim_loop

        addi -8 ; r0 = 13
        addi -3
        add r3, r0 ; r3 = 10

; r3 = 10
; r2 = fim_loop
; r1 = adr(A[9])
; r0 = -2
loop:   
        sub r0, r0
        addi -1
        add r3, r0 ; 10 + -1 = 9
        ld r1, r0 ; r1 = adr(A[9])
        addi -1 ; r0 = -2
        ebreak
;inicialização
        sub r1, r3; r1 = A[0]
        ld r1, r1 ; r1 = M(A[0])
        ld r0, r0 ; r0 = adr(B[9])
        sub r0, r3; r0 = adr(B[0])
        ld r0, r0 ; r0 = M[B[0]]
        add r1, r0 ; r1 = M[A[0]] + M[B[0]]
        sub r0, r0 ; r0 = 0
        addi -3 ; r0 = adr[R[9]]
        sub r0, r3 ; r0 = adr[R[0]]
        ld r1, r0 ; M[r0] = R[0] = M[A[0]] + M[B[0]]
        brzr r3, r2 ; Se r3 = 9 = 0 então sai do loop
        sub r0, r0
        addi -4 ; r0 = -4
        ld r0, r0 ; r0 = loop
        sub r1, r1 
        brzr r1, r0
; volta pra cima
; r1 = 0
; r0 = loop
fim_loop:
        ebreak
        
