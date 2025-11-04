// diagram.c
#include "simulator.h"

#define MAX_CYCLES_ESTIMATE 4096

/* Estrutura do diagrama:
   diagram[row][col] -> string curta ("IF","ID","EX","MEM","WB" ou ".")
*/
static char*** diagram = NULL;
static int diagram_rows = 0;
static int diagram_cols = 0;
static int bubble_count = 0;

static void ensure_cols(int required_cols) {
    if (required_cols <= diagram_cols) return;
    int new_cols = required_cols * 2;
    for (int i = 0; i < diagram_rows; ++i) {
        diagram[i] = (char**) realloc(diagram[i], sizeof(char*) * new_cols);
        for (int j = diagram_cols; j < new_cols; ++j) {
            diagram[i][j] = strdup(".");
        }
    }
    diagram_cols = new_cols;
}

void initialize_diagram(int num_instructions) {
    int est_cols = num_instructions + 16;
    diagram_rows = num_instructions;
    diagram_cols = est_cols;
    diagram = (char***) malloc(sizeof(char**) * diagram_rows);
    for (int i = 0; i < diagram_rows; ++i) {
        diagram[i] = (char**) malloc(sizeof(char*) * diagram_cols);
        for (int j = 0; j < diagram_cols; ++j) {
            diagram[i][j] = strdup(".");
        }
    }
    bubble_count = 0;
}

static void set_cell(int inst_index, int cycle, const char* stage) {
    if (inst_index < 0 || inst_index >= diagram_rows) return;
    if (cycle < 1) return; // usamos ciclos começando em 1
    if (cycle > diagram_cols) ensure_cols(cycle);
    int col = cycle - 1;
    free(diagram[inst_index][col]);
    diagram[inst_index][col] = strdup(stage);
}

static bool inst_uses_register(const Instruction* inst, int reg) {
    if (inst == NULL || inst->format == NONE) return false;
    if (inst->rs == reg) return true;
    if (inst->rt == reg) return true;
    return false;
}

/* Retorna -1 se a instrução não escreve registrador, senão o índice do registrador escrito */
static int inst_write_register(const Instruction* inst) {
    if (!inst) return -1;
    if (inst->format == R_TYPE) {
        // add, sub -> escrevem em rd
        if (inst->mnemonic && (strcmp(inst->mnemonic, "add") == 0 || strcmp(inst->mnemonic, "sub") == 0))
            return inst->rd;
    } else if (inst->format == I_TYPE) {
        // lw escreve em rt; sw não escreve; beq não escreve
        if (inst->mnemonic && strcmp(inst->mnemonic, "lw") == 0) return inst->rt;
    }
    return -1;
}

static const char* stage_name_for_offset(int offset) {
    switch(offset) {
        case 0: return "IF";
        case 1: return "ID";
        case 2: return "EX";
        case 3: return "MEM";
        case 4: return "WB";
        default: return "??";
    }
}

/*
  Agenda das regras (resumo):
  - IF_i = ciclo livre atual (tentativa).
  - Para cada produtor j < i que escreve em reg R usado por i:
      * se producer é LW:
          -> consumer precisa começar IF_i >= IF_j + 2   (insere 1 stall quando for uso imediato)
      * se producer é ALU (R-type):
          -> se forwarding_enabled == true: não precisa de stall (forwarding resolve)
          -> se forwarding_enabled == false: exigir IF_i >= IF_j + 3 (mais conservador)
  - Para branch (beq) aplicamos regra conservadora: a próxima instrução inicia com +1 stall
*/


void print_final_report(int total_cycles, int bubbles) {
    printf("------------------------------------------------------------\n");
    printf("RELATÓRIO FINAL\n");
    printf("Ciclos totais executados : %d\n", total_cycles);
    printf("Bolhas (stalls) inseridas : %d\n", bubbles);
    printf("Eficiência do pipeline   : %.2f%%\n",
           (total_cycles > 0) ? (100.0 * (total_cycles - bubbles) / total_cycles) : 0.0);
    printf("------------------------------------------------------------\n");
}


void generate_execution_diagram(Instruction* instruction_memory, int num_instructions, bool forwarding_enabled) {
    if (num_instructions <= 0) return;

    initialize_diagram(num_instructions);

    int *IF_cycle = (int*) malloc(sizeof(int) * num_instructions);
    for (int i = 0; i < num_instructions; ++i) IF_cycle[i] = 0;

    int current_IF = 1;

    for (int i = 0; i < num_instructions; ++i) {
        Instruction* inst = &instruction_memory[i];
        int desired_IF = current_IF;

        // Stall após branch (regra simples)
        if (i > 0 && instruction_memory[i-1].mnemonic &&
            strcmp(instruction_memory[i-1].mnemonic, "beq") == 0) {
            if (desired_IF < IF_cycle[i-1] + 2)
                desired_IF = IF_cycle[i-1] + 2;
        }

        // Detecta dependências anteriores
        for (int j = 0; j < i; ++j) {
            int prod_reg = inst_write_register(&instruction_memory[j]);
            if (prod_reg == -1) continue;
            if (!inst_uses_register(inst, prod_reg)) continue;

            bool prod_is_lw = (instruction_memory[j].mnemonic &&
                               strcmp(instruction_memory[j].mnemonic, "lw") == 0);

            if (prod_is_lw) {
                // Hazard de load-use imediato -> 1 bolha
                int min_IF = IF_cycle[j] + 2;
                if (desired_IF < min_IF) desired_IF = min_IF;
            } else {
                // Produtor é instrução ALU (R-type)
                if (!forwarding_enabled) {
                    int min_IF = IF_cycle[j] + 3;
                    if (desired_IF < min_IF) desired_IF = min_IF;
                }
            }
        }

        // Conta bolhas (se houve atraso)
        if (desired_IF > current_IF)
            bubble_count += (desired_IF - current_IF);

        IF_cycle[i] = desired_IF;

        // 🔹 Preenche estágios IF..WB
        for (int offset = 0; offset < 5; ++offset) {
            int cyc = IF_cycle[i] + offset;
            set_cell(i, cyc, stage_name_for_offset(offset));
        }

        // 🔹 Marca bolhas graficamente (".") nas linhas intermediárias
        if (desired_IF > current_IF) {
            for (int stall = current_IF; stall < desired_IF; ++stall) {
                set_cell(i, stall, "-"); // indica bolha visualmente
            }
        }

        current_IF = IF_cycle[i] + 1;
    }

    // Calcula o último ciclo usado
    int max_cycle_used = 0;
    for (int i = 0; i < num_instructions; ++i) {
        int last = IF_cycle[i] + 4;
        if (last > max_cycle_used) max_cycle_used = last;
    }

    // Impressão do diagrama
    printf("\n================ DIAGRAMA DE EXECUÇÃO (por ciclo) ================\n\n");
    printf("%-5s", "Inst");
    for (int c = 1; c <= max_cycle_used; ++c) {
        printf(" | C%-3d", c);
    }
    printf("\n");

    int header_width = 5 + (max_cycle_used * 7);
    for (int i = 0; i < header_width; ++i) putchar('-');
    printf("\n");

    for (int i = 0; i < diagram_rows; ++i) {
        printf("[%02d] ", i);
        for (int c = 1; c <= max_cycle_used; ++c) {
            const char* cell = diagram[i][c-1];
            printf(" | %4s", cell);
        }
        printf("    <-- %s\n", instruction_memory[i].original_line ? instruction_memory[i].original_line : "");
    }

    printf("\nTotal de ciclos: %d\n", max_cycle_used);
    printf("Total de bolhas inseridas (stalls): %d\n", bubble_count);
    printf("=================================================================\n\n");

    print_final_report(max_cycle_used, bubble_count);

    free(IF_cycle);
}