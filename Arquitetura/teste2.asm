addi 7       ;; r0 = 7  (somamos para construir 40)
addi 7       ;; r0 = 14
addi 7       ;; r0 = 21
addi 7       ;; r0 = 28
addi 7       ;; r0 = 35
addi 5       ;; r0 = 40
add r1, r0   ;; r1 = 40 (agora temos o endereço inicial)
sub r0, r0   ;; r0 = 0 
addi 5
addi 5
add r3, r0       
sub r0, r0
add r2, r0       
loop:
    st r2, r1 
    sub r0, r0       
    addi 1       
    add r1, r0
    addi 1
    add r2, r0       
    sub r0, r0
    addi 1
    sub r3, r0       
    brzr r3, end     
    ji loop        
end:
    ji end