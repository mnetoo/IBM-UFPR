#include "simulator.h"

/* (imprima a função print_parsed_instruction tal como você tinha) */
void print_parsed_instruction(const Instruction* inst) {
    printf("\tOriginal: \"%s\"\n", inst->original_line);
    printf("\tMnemônico: %s\n", inst->mnemonic);

    switch (inst->format) {
        case R_TYPE:
            printf("\tFormato: R-Type\n");
            printf("\tRegistradores: rd=%d, rs=%d, rt=%d\n", inst->rd, inst->rs, inst->rt);
            break;
        case I_TYPE:
            printf("\tFormato: I-Type\n");
            if (strcmp(inst->mnemonic, "lw") == 0 || strcmp(inst->mnemonic, "sw") == 0) {
                 printf("\tRegistradores: rt=%d, rs=%d, Imediato=%d\n", inst->rt, inst->rs, inst->imm);
            } else { // beq
                 printf("\tRegistradores: rs=%d, rt=%d\n", inst->rs, inst->rt);
            }
            break;
        case J_TYPE:
            printf("\tFormato: J-Type\n");
            printf("\tEndereço: %u\n", inst->address);
            break;
        case NONE:
            printf("\tFormato: Nenhum/Inválido\n");
            break;
    }
    printf("--------------------------------------------------\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso incorreto!\n");
        fprintf(stderr, "Execute como: %s <caminho_para_o_arquivo.asm>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    printf("Iniciando simulador (apenas parser + diagrama)...\n");
    printf("Lendo instruções do arquivo: %s\n", filename);
    printf("==================================================\n\n");

    Instruction instruction_memory[MAX_INSTRUCTIONS];
    int num_instructions = load_instructions_from_file(filename, instruction_memory);

    if (num_instructions == 0) {
        printf("Nenhuma instrução válida foi carregada. Verifique o arquivo de entrada.\n");
        return EXIT_SUCCESS;
    }

    printf("Arquivo lido e decodificado com sucesso! %d instruções carregadas.\n", num_instructions);
    printf("----------- Conteúdo da Memória de Instruções -----------\n");
    for (int i = 0; i < num_instructions; i++) {
        printf("Instrução [%d]:\n", i);
        print_parsed_instruction(&instruction_memory[i]);
    }

    // === Gerar e imprimir o diagrama de execução por ciclo ===
    // Ativa forwarding por padrão (true). Troque para false para desabilitar o forwarding.
    bool forwarding_enabled = true;
    generate_execution_diagram(instruction_memory, num_instructions, forwarding_enabled);


    printf("\nFim do programa.\n");
    return EXIT_SUCCESS;
}