# Exemplo com hazards, dependências e forwarding (sem labels)

    lw   $t0, 0($t1)      # 1. Load -> $t0
    add  $t2, $t0, $t3    # 2. Usa $t0 (load-use hazard) → precisa de bolha
    sub  $t4, $t2, $t5    # 3. Usa $t2 → forwarding
    and  $t6, $t4, $t7    # 4. Usa $t4 → forwarding
    or   $t8, $t6, $t9    # 5. Usa $t6 → forwarding
    sw   $t8, 4($t1)      # 6. Usa $t8 → forwarding
    add  $s0, $t2, $t4    # 7. Usa $t2 e $t4 → múltiplas dependências (forwarding)