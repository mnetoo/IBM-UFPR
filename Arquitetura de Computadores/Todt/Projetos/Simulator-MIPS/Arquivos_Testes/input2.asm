lw   $t0, 0($s0)     # carrega palavra da memória
add  $t1, $t0, $t2   # usa $t0 → HAZARD load-use → exige STALL
sub  $t3, $t1, $t4   # usa $t1 → HAZARD resolvido com FORWARDING (EX/MEM)
sw   $t3, 4($s0)     # store → depende de $t3 → FORWARDING para sw