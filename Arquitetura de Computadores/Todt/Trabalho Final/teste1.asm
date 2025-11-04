# Exemplo 1: Dois hazards load-use independentes

    lw   $t0, 0($s0)      # 1. Carrega $t0
    add  $t1, $t0, $s1    # 2. Usa $t0 -> **HAZARD 1: Bolha**

    lw   $t2, 0($s2)      # 3. Carrega $t2
    sub  $t3, $t2, $s3    # 4. Usa $t2 -> **HAZARD 2: Bolha**
    
    sw   $t1, 0($s4)
    sw   $t3, 4($s4)