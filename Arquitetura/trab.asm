addi 5
addi 5 ;; r0 = 10
add r3, r0 ;; r3 = 10
addi 5
addi 5 ;; r0 = 20
add r2, r0 ;; r2 = 20
addi 5
addi 5
addi 5
addi 5 ;; r0 = 40 
add r1, r0 ;; r1 = 40
sub r0, r0 ;; r0 = 0
addi 1 ;; r0 = 1
;; loop que carrega um "vetor" de 10 posições com o número 1 em cada posição
st r0, r1 ;; na posicao 40 guardou 1
add r1, r0 ;; r1 41
sub r3, r0 ;; 10 - 1 = 9
brzr r3, r2 ;; se r3 = 0 sai do loop
ji -4 ;; volta 4 instruções