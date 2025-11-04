// simulator.c (VERSÃO CORRIGIDA E COMPLETA)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "simulator.h"

// --- Funções Auxiliares de Hazard ---

/* Retorna o registrador de destino se a instrução escreve em um.
   Retorna -1 caso contrário. */
static int get_destination_reg(const Instruction* inst) {
    if (!inst || !inst->mnemonic) return -1;

    if (strcmp(inst->mnemonic, "add") == 0 || strcmp(inst->mnemonic, "sub") == 0 ||
        strcmp(inst->mnemonic, "and") == 0 || strcmp(inst->mnemonic, "or") == 0) {
        return inst->rd;
    }
    if (strcmp(inst->mnemonic, "lw") == 0) {
        return inst->rt;
    }
    return -1; // sw, beq, etc. não escrevem em registradores.
}

// --- Lógica Principal da Simulação ---

void run_simulation(Instruction* instructions, int num_instructions) {
    // Matriz para guardar o diagrama final
    StageType diagram[MAX_INSTRUCTIONS][MAX_CYCLES];
    // Vetor que rastreia o estágio atual de cada instrução (1=IF, 2=ID, ...)
    int current_stage_num[MAX_INSTRUCTIONS] = {0};

    // Inicializa o diagrama com "vazio"
    for (int i = 0; i < num_instructions; i++) {
        for (int j = 0; j < MAX_CYCLES; j++) {
            diagram[i][j] = ST_NONE;
        }
    }

    int cycles = 0;
    int instructions_completed = 0;
    int bubble_count = 0;

    // Loop de simulação principal
    while (instructions_completed < num_instructions) {
        bool pipeline_stalled = false;

        // FASE 1: DETECÇÃO DE HAZARDS (só precisa ser feita uma vez por ciclo)
        for (int i = 0; i < num_instructions; i++) {
            // Um stall de load-use só é causado por uma instrução no estágio ID.
            if (current_stage_num[i] != 2) continue;

            Instruction* consumer = &instructions[i]; // A instrução em ID

            // Checa contra a instrução anterior (i-1) que está em EX.
            if (i > 0 && current_stage_num[i-1] == 3) {
                Instruction* producer = &instructions[i-1]; // A instrução em EX
                
                if (strcmp(producer->mnemonic, "lw") == 0) {
                    int dest_reg = get_destination_reg(producer);
                    if (dest_reg != -1 && (consumer->rs == dest_reg || consumer->rt == dest_reg)) {
                        pipeline_stalled = true;
                        bubble_count++;
                        break; // Stall detectado, pode parar de procurar.
                    }
                }
            }
        }

        // FASE 2: ATUALIZAÇÃO DOS ESTÁGIOS
        for (int i = num_instructions - 1; i >= 0; i--) {
            if (current_stage_num[i] == 0 || current_stage_num[i] > 5) continue;
            
            // ================== A LÓGICA DE CORREÇÃO ESTÁ AQUI ==================
            // SE O PIPELINE ESTIVER TRAVADO, CONGELE AS INSTRUÇÕES NOS ESTÁGIOS ID e IF.
            if (pipeline_stalled && (current_stage_num[i] == 2 || current_stage_num[i] == 1)) {
                // Não faz nada. O número do estágio não é incrementado, "congelando" a instrução.
            } else {
                current_stage_num[i]++; // Avança a instrução para o próximo estágio.
            }
        }

        // FASE 3: BUSCA DE NOVA INSTRUÇÃO
        if (!pipeline_stalled) {
            int inst_to_fetch = -1;
            for (int i = 0; i < num_instructions; i++) {
                if (current_stage_num[i] == 0) {
                    inst_to_fetch = i;
                    break;
                }
            }
            if (inst_to_fetch != -1) {
                current_stage_num[inst_to_fetch] = 1; // Coloca em IF
            }
        }

        // FASE 4: REGISTRO NO DIAGRAMA
        for (int i = 0; i < num_instructions; i++) {
            if (current_stage_num[i] > 0) {
                 if (pipeline_stalled && current_stage_num[i] == 2) {
                     diagram[i][cycles] = ST_STALL;
                 } else if (current_stage_num[i] <= 5) {
                     diagram[i][cycles] = (StageType)(current_stage_num[i] - 1);
                 }
            }
            
            if (current_stage_num[i] == 6) {
                instructions_completed++;
                current_stage_num[i]++;
            }
        }
        
        cycles++;
        if (cycles >= MAX_CYCLES) break;
    }

    // --- FASE 5: IMPRESSÃO DO RESULTADO ---
    const char* stage_names[] = {"IF", "ID", "EX", "MEM", "WB", "--", "  "};
    printf("\n================ DIAGRAMA DE EXECUCAO (por ciclo) ================\n\n");
    printf("%-20s", "Instrucao");
    for (int j = 0; j < cycles; j++) printf(" | C%-2d", j + 1);
    printf("\n");

    for (int i = 0; i < num_instructions; i++) {
        printf("%-20.20s", instructions[i].original_line);
        for (int j = 0; j < cycles; j++) {
            printf(" | %-3s", stage_names[diagram[i][j]]);
        }
        printf("  <-- [%02d]\n", i);
    }

    printf("\nTotal de ciclos: %d\n", cycles);
    printf("Total de bolhas inseridas (stalls): %d\n\n", bubble_count);

    // Relatório Final
    printf("====================== RELATORIO FINAL ======================\n");
    printf("Ciclos totais executados : %d\n", cycles);
    printf("Bolhas (stalls) inseridas : %d\n", bubble_count);
    double efficiency = (cycles > 0) ? (100.0 * (num_instructions * 5) / ((num_instructions * 5) + bubble_count)) : 0;
    printf("Eficiencia do pipeline   : %.2f%%\n", efficiency);
    printf("===========================================================\n");
}