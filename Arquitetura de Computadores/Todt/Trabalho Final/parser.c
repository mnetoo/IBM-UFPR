#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "simulator.h"

// Converte nomes de registradores para índice numérico
static int register_name_to_index(const char* reg_name) {
    if (strcmp(reg_name, "$0") == 0 || strcmp(reg_name, "$zero") == 0) return 0;
    if (strcmp(reg_name, "$1") == 0 || strcmp(reg_name, "$at") == 0) return 1;
    if (strcmp(reg_name, "$2") == 0 || strcmp(reg_name, "$v0") == 0) return 2;
    if (strcmp(reg_name, "$3") == 0 || strcmp(reg_name, "$v1") == 0) return 3;
    if (strcmp(reg_name, "$4") == 0 || strcmp(reg_name, "$a0") == 0) return 4;
    if (strcmp(reg_name, "$5") == 0 || strcmp(reg_name, "$a1") == 0) return 5;
    if (strcmp(reg_name, "$6") == 0 || strcmp(reg_name, "$a2") == 0) return 6;
    if (strcmp(reg_name, "$7") == 0 || strcmp(reg_name, "$a3") == 0) return 7;
    if (strcmp(reg_name, "$8") == 0 || strcmp(reg_name, "$t0") == 0) return 8;
    if (strcmp(reg_name, "$9") == 0 || strcmp(reg_name, "$t1") == 0) return 9;
    if (strcmp(reg_name, "$10") == 0 || strcmp(reg_name, "$t2") == 0) return 10;
    if (strcmp(reg_name, "$11") == 0 || strcmp(reg_name, "$t3") == 0) return 11;
    if (strcmp(reg_name, "$12") == 0 || strcmp(reg_name, "$t4") == 0) return 12;
    if (strcmp(reg_name, "$13") == 0 || strcmp(reg_name, "$t5") == 0) return 13;
    if (strcmp(reg_name, "$14") == 0 || strcmp(reg_name, "$t6") == 0) return 14;
    if (strcmp(reg_name, "$15") == 0 || strcmp(reg_name, "$t7") == 0) return 15;
    if (strcmp(reg_name, "$16") == 0 || strcmp(reg_name, "$s0") == 0) return 16;
    if (strcmp(reg_name, "$17") == 0 || strcmp(reg_name, "$s1") == 0) return 17;
    if (strcmp(reg_name, "$18") == 0 || strcmp(reg_name, "$s2") == 0) return 18;
    if (strcmp(reg_name, "$19") == 0 || strcmp(reg_name, "$s3") == 0) return 19;
    if (strcmp(reg_name, "$20") == 0 || strcmp(reg_name, "$s4") == 0) return 20;
    if (strcmp(reg_name, "$21") == 0 || strcmp(reg_name, "$s5") == 0) return 21;
    if (strcmp(reg_name, "$22") == 0 || strcmp(reg_name, "$s6") == 0) return 22;
    if (strcmp(reg_name, "$23") == 0 || strcmp(reg_name, "$s7") == 0) return 23;
    if (strcmp(reg_name, "$24") == 0 || strcmp(reg_name, "$t8") == 0) return 24;
    if (strcmp(reg_name, "$25") == 0 || strcmp(reg_name, "$t9") == 0) return 25;
    if (strcmp(reg_name, "$26") == 0 || strcmp(reg_name, "$k0") == 0) return 26;
    if (strcmp(reg_name, "$27") == 0 || strcmp(reg_name, "$k1") == 0) return 27;
    if (strcmp(reg_name, "$28") == 0 || strcmp(reg_name, "$gp") == 0) return 28;
    if (strcmp(reg_name, "$29") == 0 || strcmp(reg_name, "$sp") == 0) return 29;
    if (strcmp(reg_name, "$30") == 0 || strcmp(reg_name, "$fp") == 0 || strcmp(reg_name, "$s8") == 0) return 30;
    if (strcmp(reg_name, "$31") == 0 || strcmp(reg_name, "$ra") == 0) return 31;
    return -1;
}

// Faz o parsing de uma única instrução
static void parse_single_instruction(char* line, Instruction* inst) {
    inst->original_line = strdup(line);
    inst->rs = inst->rt = inst->rd = -1;
    inst->imm = 0;
    inst->format = NONE;

    const char* delimiters = " \t,()";
    char* token = strtok(line, delimiters);
    if (token == NULL) return;

    inst->mnemonic = strdup(token);

    // Tipo R: add, sub, and, or
    if (strcmp(inst->mnemonic, "add") == 0 || strcmp(inst->mnemonic, "sub") == 0 ||
        strcmp(inst->mnemonic, "and") == 0 || strcmp(inst->mnemonic, "or") == 0) 
    {
        inst->format = R_TYPE;
        inst->rd = register_name_to_index(strtok(NULL, delimiters));
        inst->rs = register_name_to_index(strtok(NULL, delimiters));
        inst->rt = register_name_to_index(strtok(NULL, delimiters));
    }

    // Tipo I: lw, sw
    else if (strcmp(inst->mnemonic, "lw") == 0 || strcmp(inst->mnemonic, "sw") == 0) {
        inst->format = I_TYPE;
        inst->rt = register_name_to_index(strtok(NULL, delimiters));  // destino
        char* imm_str = strtok(NULL, delimiters);                     // imediato
        inst->imm = imm_str ? atoi(imm_str) : 0;
        inst->rs = register_name_to_index(strtok(NULL, delimiters));  // base
    }

    // Tipo I: beq
    else if (strcmp(inst->mnemonic, "beq") == 0) {
        inst->format = I_TYPE;
        inst->rs = register_name_to_index(strtok(NULL, delimiters));
        inst->rt = register_name_to_index(strtok(NULL, delimiters));
        char* imm_str = strtok(NULL, delimiters);
        inst->imm = imm_str ? atoi(imm_str) : 0;
    }

    else {
        fprintf(stderr, "ERRO: Instrução não reconhecida -> %s\n", inst->mnemonic);
        inst->format = NONE;
    }
}

// Carrega todas as instruções do arquivo
int load_instructions_from_file(const char* filename, Instruction* instruction_memory) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("ERRO: Não foi possível abrir o arquivo de instruções");
        exit(EXIT_FAILURE);
    }

    char line_buffer[256];
    int instruction_count = 0;

    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL && instruction_count < MAX_INSTRUCTIONS) {
        line_buffer[strcspn(line_buffer, "\n")] = 0;

        // ignora espaços iniciais e linhas vazias/comentários
        char* first_char = line_buffer;
        while (*first_char && isspace(*first_char)) first_char++;

        if (first_char[0] == '#' || first_char[0] == '\0')
            continue;

        parse_single_instruction(line_buffer, &instruction_memory[instruction_count]);

        if (instruction_memory[instruction_count].mnemonic != NULL)
            instruction_count++;
    }

    if (instruction_count >= MAX_INSTRUCTIONS)
        fprintf(stderr, "AVISO: Número máximo de instruções (%d) atingido.\n", MAX_INSTRUCTIONS);

    fclose(file);
    return instruction_count;
}
