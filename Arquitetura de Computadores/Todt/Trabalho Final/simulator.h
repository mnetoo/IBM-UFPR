#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdint.h> // Para usar tipos de inteiros com tamanho fixo, como uint32_t.
#include <stdbool.h> // Para usar o tipo bool (true/false) para os sinais de controle.
#include <stdlib.h> // Para funções de alocação de memória.
#include <string.h> // Para manipulação de strings.
#include <stdio.h>  // Para entrada e saída padrão (printf, fprintf, etc.).
#include <ctype.h> // Para funções de manipulação de caracteres (isspace, etc.).

// ============================================================================
// 1. CONSTANTES DA ARQUITETURA
// ============================================================================

#define NUM_REGISTERS 32      // MIPS tem 32 registradores de propósito geral.
#define MEM_SIZE 1024         // Tamanho da nossa memória de dados (em palavras de 32 bits).
#define MAX_INSTRUCTIONS 256  // Número máximo de instruções que nosso programa pode ter.


// ============================================================================
// 2. ESTRUTURAS DE DADOS FUNDAMENTAIS
// ============================================================================

// Enumeração para identificar o formato da instrução MIPS.
typedef enum {
    R_TYPE,
    I_TYPE,
    J_TYPE,
    NONE // Para representar um estado vazio ou nop.
} InstFormat;

// Estrutura para representar uma única instrução MIPS após ser decodificada.
// Contém todos os campos possíveis para os formatos R, I e J.
typedef struct {
    char* original_line;  // A linha de texto original da instrução, para impressão.
    InstFormat format;    // O formato da instrução (R, I ou J).
    char* mnemonic;       // O nome da instrução (ex: "add", "lw").

    // Campos dos formatos de instrução
    int rs, rt, rd;       // Registradores fonte (rs, rt) e destino (rd).
    int shamt;            // Quantidade de deslocamento (shift amount).
    int funct;            // Campo de função para instruções R-Type.
    int16_t imm;          // Imediato de 16 bits para I-Type (pode ser negativo).
    uint32_t address;     // Endereço de 26 bits para J-Type.
} Instruction;


// ============================================================================
// 3. ESTRUTURAS DOS REGISTRADORES DE PIPELINE
// ============================================================================
// Essas estruturas armazenam os dados que fluem de um estágio para o próximo.

// --- Estágio IF para ID ---
typedef struct {
    Instruction inst; // A instrução que foi buscada.
    uint32_t npc;     // Endereço da próxima instrução (PC + 4).
} IF_ID_Register;

// --- Estágio ID para EX ---
typedef struct {
    Instruction inst;
    uint32_t npc;
    uint32_t read_data1; // Valor lido do registrador rs.
    uint32_t read_data2; // Valor lido do registrador rt.
    int32_t imm_ext;     // Imediato de 16 bits estendido para 32 bits.

    // SINAIS DE CONTROLE GERADOS EM ID (propagados para os próximos estágios)
    bool RegDst;    // MUX para selecionar o registrador de escrita (rd ou rt).
    bool ALUSrc;    // MUX para selecionar a 2ª entrada da ULA (rt ou imediato).
    bool MemtoReg;  // MUX para selecionar o que escrever no registrador (ULA ou memória).
    bool RegWrite;  // Habilita a escrita no banco de registradores.
    bool MemRead;   // Habilita a leitura da memória de dados.
    bool MemWrite;  // Habilita a escrita na memória de dados.
    bool Branch;    // Sinaliza que a instrução é um desvio.
    uint8_t ALUOp;  // Define a operação principal da ULA (ex: 00=lw/sw, 01=beq, 10=R-type).
} ID_EX_Register;

// --- Estágio EX para MEM ---
typedef struct {
    Instruction inst;
    uint32_t alu_result;    // Resultado da operação na ULA.
    uint32_t write_data;    // Dado a ser escrito na memória (vindo de rt).
    int write_reg_addr;     // Endereço do registrador de destino já definido pelo MUX RegDst.

    // Sinais de controle que precisam ser propagados
    bool MemtoReg;
    bool RegWrite;
    bool MemRead;
    bool MemWrite;
    bool Branch;
    bool Zero;              // Flag da ULA que indica se o resultado foi zero (usado pelo beq).
} EX_MEM_Register;

// --- Estágio MEM para WB ---
typedef struct {
    Instruction inst;
    uint32_t read_data;      // Dado lido da memória.
    uint32_t alu_result;     // Resultado da ULA (propagado do estágio anterior).
    int write_reg_addr;      // Endereço do registrador de destino.

    // Sinais de controle finais para o último estágio
    bool MemtoReg;
    bool RegWrite;
} MEM_WB_Register;


// ============================================================================
// 4. PROTÓTIPOS DE FUNÇÕES GLOBAIS
// ============================================================================
// Declarações das funções que serão implementadas nos arquivos .c
// para que possam ser chamadas de qualquer lugar do projeto.

// --- Funções do Módulo `parser.c` ---
int load_instructions_from_file(const char* filename, Instruction* instruction_memory);


// --- Funções do Módulo `output.c` / diagram.c ---
void initialize_diagram(int num_instructions);
void update_diagram(int inst_index, int cycle);
void print_final_report(int total_cycles, int bubbles);

// Função principal para gerar e imprimir o diagrama a partir da memória de instruções.
// forwarding_enabled: true -> insere forwarding (minimiza stalls), false -> sem forwarding (mais stalls).
void generate_execution_diagram(Instruction* instruction_memory, int num_instructions, bool forwarding_enabled);


// --- Funções do Módulo Principal `mips_simulator.c` ---
void initialize_processor_state();



#endif // Fim do MIPS_SIMULATOR_H